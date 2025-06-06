
#include "powman.h"

static powman_power_state off_state;
static powman_power_state on_state;

//#define DEBUG

uint8_t powman_get_wake_reason(void) {
    // 0 = chip reset, for the source of the last reset see POWMAN_CHIP_RESET
    // 1 = pwrup0 (GPIO interrupt 0)
    // 2 = pwrup1 (GPIO interrupt 1)
    // 3 = pwrup2 (GPIO interrupt 2)
    // 4 = pwrup3 (GPIO interrupt 3)
    // 5 = coresight_pwrup
    // 6 = alarm_pwrup (timeout or alarm wakeup)
    return powman_hw->last_swcore_pwrup & 0x7f;
}

void powman_init() {
    uint64_t abs_time_ms = 1746057600000; // 2025/05/01 - Milliseconds since epoch

    // Run everything from pll_usb pll and stop pll_sys
    set_sys_clock_48mhz();

    // Use the 32768 Hz clockout from the RTC to keep time accurately
    //clock_configure_gpin(clk_ref, 12, 32.768f * KHZ, 32.768f * KHZ);
    //clock_configure_gpin(clk_sys, 12, 32.768f * KHZ, 32.768f * KHZ);
    //clock_configure_undivided(clk_peri, 0, CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS, 32.768f * KHZ);
    //powman_timer_set_1khz_tick_source_lposc_with_hz(32768);

    powman_timer_set_1khz_tick_source_lposc();
    pll_deinit(pll_sys);

    // Set all pins to input (as far as SIO is concerned)
    gpio_set_dir_all_bits(0);
    for (int i = 0; i < NUM_BANK0_GPIOS; ++i) {
        gpio_set_function(i, GPIO_FUNC_SIO);
        if (i > NUM_BANK0_GPIOS - NUM_ADC_CHANNELS) {
            gpio_disable_pulls(i);
            gpio_set_input_enabled(i, false);
        }
    }

    // Unlock the VREG control interface
    hw_set_bits(&powman_hw->vreg_ctrl, POWMAN_PASSWORD_BITS | POWMAN_VREG_CTRL_UNLOCK_BITS);

    // Turn off USB PHY and apply pull downs on DP & DM
    usb_hw->phy_direct = USB_USBPHY_DIRECT_TX_PD_BITS | USB_USBPHY_DIRECT_RX_PD_BITS | USB_USBPHY_DIRECT_DM_PULLDN_EN_BITS | USB_USBPHY_DIRECT_DP_PULLDN_EN_BITS;
    
    usb_hw->phy_direct_override = USB_USBPHY_DIRECT_RX_DM_BITS | USB_USBPHY_DIRECT_RX_DP_BITS |          USB_USBPHY_DIRECT_RX_DD_BITS |
        USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_BITS |
        USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_BITS |
        USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_BITS |
        USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_BITS |
        USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_BITS | USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_BITS;

    // start powman and set the time
    powman_timer_start();
    powman_timer_set_ms(abs_time_ms);

    // Allow power down when debugger connected
    powman_set_debug_power_request_ignored(true);

    // Power states
    powman_power_state P1_7 = POWMAN_POWER_STATE_NONE;

    powman_power_state P0_3 = POWMAN_POWER_STATE_NONE;
    P0_3 = powman_power_state_with_domain_on(P0_3, POWMAN_POWER_DOMAIN_SWITCHED_CORE);
    P0_3 = powman_power_state_with_domain_on(P0_3, POWMAN_POWER_DOMAIN_XIP_CACHE);

    off_state = P1_7;
    on_state = P0_3;
}

// Initiate power off
int __no_inline_not_in_flash_func(powman_off)(void) {
    // Set power states
    bool valid_state = powman_configure_wakeup_state(off_state, on_state);
    if (!valid_state) {
        return PICO_ERROR_INVALID_STATE;
    }

    // reboot to main
    powman_hw->boot[0] = 0;
    powman_hw->boot[1] = 0;
    powman_hw->boot[2] = 0;
    powman_hw->boot[3] = 0;

    // Switch to required power state
    int rc = powman_set_power_state(off_state);
    if (rc != PICO_OK) {
        return rc;
    }

    // Power down
    while (true) __wfi();
}

int powman_setup_gpio_wakeup(int hw_wakeup, int gpio, bool edge, bool high, uint64_t timeout_ms) {
    gpio_init(gpio);
    gpio_set_dir(gpio, false);
    gpio_set_input_enabled(gpio, true);

    // Must set pulls here, or our pin may never go into its idle state
    gpio_set_pulls(gpio, !high, high);
    
    // If the pin is currently in a triggered state, wait for idle
    absolute_time_t timeout = make_timeout_time_ms(timeout_ms);
    if (gpio_get(gpio) == high) {
        while(gpio_get(gpio) == high) {
            sleep_ms(10);
            if(time_reached(timeout)) return -1;
        }
    }
    powman_enable_gpio_wakeup(hw_wakeup, gpio, edge, high);

    return 0;
}

// Power off until a gpio goes high
int powman_off_until_gpio_high(int gpio, bool edge, bool high, uint64_t timeout_ms) {
    powman_init();

    powman_setup_gpio_wakeup(POWMAN_WAKE_PWRUP0_CH, gpio, edge, high, 1000);

    if (timeout_ms > 0) {
        uint64_t ms = powman_timer_get_ms();
        return powman_off_until_time(ms + timeout_ms);
    } else {
        return powman_off();
    }
}

// Power off until an absolute time
int powman_off_until_time(uint64_t absolute_time_ms) {
    powman_init();

    // Start powman timer and turn off
    powman_enable_alarm_wakeup_at_ms(absolute_time_ms);
    return powman_off();
}

// Power off for a number of milliseconds
int powman_off_for_ms(uint64_t duration_ms) {
    powman_init();

    uint64_t ms = powman_timer_get_ms();
    return powman_off_until_time(ms + duration_ms);
}