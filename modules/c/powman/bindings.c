#include <time.h>
#include <sys/time.h>

#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "powman.h"

#include "mphalport.h"
#include "py/runtime.h"
#include "shared/timeutils/timeutils.h"

#define GPIO_I2C_POWER 2
#define GPIO_WAKE 3
#define GPIO_EXT_CLK 12
#define GPIO_LED_A 10

enum {
    WAKE_BUTTON_A = 0x00,
    WAKE_BUTTON_B,
    WAKE_BUTTON_C,
    WAKE_TIMER = 0xf0,
    WAKE_UNKNOWN = 0xff,
};

mp_obj_t _sleep_get_wake_reason(void) {
    uint8_t wake_reason = powman_get_wake_reason();
    if(wake_reason & POWMAN_WAKE_ALARM) {
        return MP_ROM_INT(WAKE_TIMER);
    }
    if(wake_reason & POWMAN_WAKE_PWRUP0) return MP_ROM_INT(WAKE_BUTTON_A);
    if(wake_reason & POWMAN_WAKE_PWRUP1) return MP_ROM_INT(WAKE_BUTTON_B);
    if(wake_reason & POWMAN_WAKE_PWRUP2) return MP_ROM_INT(WAKE_BUTTON_C);
    return MP_ROM_INT(WAKE_UNKNOWN);
}
static MP_DEFINE_CONST_FUN_OBJ_0(_sleep_get_wake_reason_obj, _sleep_get_wake_reason);

/*! \brief Send system to sleep until the specified GPIO changes
 *
 * \param gpio_pin The pin to provide the wake up
 * \param edge true for leading edge, false for trailing edge
 * \param high true for active high, false for active low
 * \param timeout wakeup after timeout milliseconds if no edge occurs
 */
mp_obj_t _sleep_goto_dormant_until_pin(size_t n_args, const mp_obj_t *args) {
    enum { ARG_pin, ARG_edge, ARG_high, ARG_timeout };

    uint pin = UINT16_MAX;
    if(args[ARG_pin] != mp_const_none) {
        pin = mp_hal_get_pin_obj(args[ARG_pin]);
    }
    bool edge = mp_obj_is_true(args[ARG_edge]);
    bool high = mp_obj_is_true(args[ARG_high]);
    uint64_t timeout_ms = 0;

    if (n_args == 4) {
        timeout_ms = (uint64_t)mp_obj_get_float(args[ARG_timeout]) * 1000;
    }

    powman_init();

    if (pin != UINT16_MAX) {
        powman_setup_gpio_wakeup(POWMAN_WAKE_PWRUP0_CH, pin, edge, high, 1000);
    } else {
        int err = 0;
        err = powman_setup_gpio_wakeup(POWMAN_WAKE_PWRUP0_CH, 12, edge, high, 1000); // Tufty Button A
        if (err == -1) {mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Timeout waiting for Button A"));}
        err = powman_setup_gpio_wakeup(POWMAN_WAKE_PWRUP1_CH, 13, edge, high, 1000); // Tufty Button B
        if (err == -1) {mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Timeout waiting for Button B"));}
        err = powman_setup_gpio_wakeup(POWMAN_WAKE_PWRUP2_CH, 14, edge, high, 1000); // Tufty Button C
        if (err == -1) {mp_raise_msg(&mp_type_RuntimeError, MP_ERROR_TEXT("Timeout waiting for Button C"));}
    }

    // power off
    int rc = 0;
    if (timeout_ms > 0) {
        absolute_time_t timeout = make_timeout_time_ms(timeout_ms);
        rc = powman_off_until_time(timeout);
    } else {
        rc = powman_off();
    }
    hard_assert(rc == PICO_OK);
    hard_assert(false); // should never get here!

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(_sleep_goto_dormant_until_pin_obj, 3, 4, _sleep_goto_dormant_until_pin);

/*! \brief Send system to dormant until the specified time, note for RP2040 the RTC must be driven by an external clock
 *
 * \param ts The time to wake up
 * \param callback Function to call on wakeup.
 */
mp_obj_t _sleep_goto_dormant_until(mp_obj_t absolute_time_in) {
    // Borrowed from https://github.com/micropython/micropython/blob/master/ports/rp2/machine_rtc.c#L83C1-L96
    mp_obj_t *items;
    mp_obj_get_array_fixed_n(absolute_time_in, 8, &items);
    timeutils_struct_time_t tm = {
        .tm_year = mp_obj_get_int(items[0]),
        .tm_mon = mp_obj_get_int(items[1]),
        .tm_mday = mp_obj_get_int(items[2]),
        .tm_hour = mp_obj_get_int(items[4]),
        .tm_min = mp_obj_get_int(items[5]),
        .tm_sec = mp_obj_get_int(items[6]),
    };
    struct timespec ts = { 0, 0 };
    ts.tv_sec = timeutils_seconds_since_epoch(tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    int rc = powman_off_until_time(timespec_to_ms(&ts));
    hard_assert(rc == PICO_OK);
    hard_assert(false); // should never get here!

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(_sleep_goto_dormant_until_obj, _sleep_goto_dormant_until);

/*! \brief Send system to dormant until the specified time, note for RP2040 the RTC must be driven by an external clock
 *
 * \param ts The time to wake up
 * \param callback Function to call on wakeup.
 */
mp_obj_t _sleep_goto_dormant_for(mp_obj_t time_seconds_in) {
    uint64_t ms = (uint64_t)(mp_obj_get_float(time_seconds_in) * 1000);
    int rc = powman_off_for_ms(ms);
    hard_assert(rc == PICO_OK);
    hard_assert(false); // should never get here!
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(_sleep_goto_dormant_for_obj, _sleep_goto_dormant_for);

static const mp_map_elem_t sleep_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_powman) },
    { MP_ROM_QSTR(MP_QSTR_goto_dormant_until_pin), MP_ROM_PTR(&_sleep_goto_dormant_until_pin_obj) },
    { MP_ROM_QSTR(MP_QSTR_goto_dormant_until), MP_ROM_PTR(&_sleep_goto_dormant_until_obj) },
    { MP_ROM_QSTR(MP_QSTR_goto_dormant_for), MP_ROM_PTR(&_sleep_goto_dormant_for_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_wake_reason), MP_ROM_PTR(&_sleep_get_wake_reason_obj) },

    { MP_ROM_QSTR(MP_QSTR_WAKE_BUTTON_A), MP_ROM_INT(WAKE_BUTTON_A) },
    { MP_ROM_QSTR(MP_QSTR_WAKE_BUTTON_B), MP_ROM_INT(WAKE_BUTTON_B) },
    { MP_ROM_QSTR(MP_QSTR_WAKE_BUTTON_C), MP_ROM_INT(WAKE_BUTTON_C) },
    { MP_ROM_QSTR(MP_QSTR_WAKE_TIMER),    MP_ROM_INT(WAKE_TIMER)    }, // TODO: Rename to ALARM?
    { MP_ROM_QSTR(MP_QSTR_WAKE_UNKNOWN),  MP_ROM_INT(WAKE_UNKNOWN)  },
};
static MP_DEFINE_CONST_DICT(mp_module_sleep_globals, sleep_globals_table);

const mp_obj_module_t sleep_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_sleep_globals,
};

MP_REGISTER_MODULE(MP_QSTR_powman, sleep_user_cmodule);