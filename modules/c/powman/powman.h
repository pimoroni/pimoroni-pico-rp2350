

#include <stdio.h>
#include <inttypes.h>
#include "pico/stdio.h"
#include "pico/sync.h"
#include "hardware/gpio.h"
#include "hardware/powman.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "hardware/adc.h"
#include "hardware/structs/usb.h"
#include "hardware/structs/xosc.h"
#include "hardware/vreg.h"
#include "hardware/flash.h"
#include "hardware/structs/qmi.h"

#define POWMAN_WAKE_PWRUP0_CH 0
#define POWMAN_WAKE_PWRUP1_CH 1
#define POWMAN_WAKE_PWRUP2_CH 2

#define POWMAN_WAKE_RESET  0b00000001
#define POWMAN_WAKE_PWRUP0 0b00000010
#define POWMAN_WAKE_PWRUP1 0b00000100
#define POWMAN_WAKE_PWRUP2 0b00001000
#define POWMAN_WAKE_PWRUP3 0b00010000
#define POWMAN_WAKE_CORESI 0b00100000
#define POWMAN_WAKE_ALARM  0b01000000

int powman_off_until_gpio_high(int gpio, bool edge, bool high, uint64_t timeout_ms);
int powman_off_until_time(uint64_t absolute_time_ms);
int powman_off_for_ms(uint64_t duration_ms);
uint8_t powman_get_wake_reason(void);

void powman_init();
int powman_setup_gpio_wakeup(int hw_wakeup, int gpio, bool edge, bool high, uint64_t timeout_ms);
int powman_off(void);