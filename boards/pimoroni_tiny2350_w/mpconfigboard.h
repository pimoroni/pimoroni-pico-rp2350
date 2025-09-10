// Board and hardware specific configuration
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Tiny 2350"
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

// I2C0 (non-default)
#define MICROPY_HW_I2C0_SCL  (4)
#define MICROPY_HW_I2C0_SDA  (5)

#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "Tiny2040"

// Enable WiFi & PPP
#define MICROPY_PY_NETWORK_PPP_LWIP             (1)

#if MICROPY_PY_NETWORK_CYW43
#include "enable_cyw43.h"

// Enable the ability to pass cyw43 pins into WiFi, Bluetooth and Pin constructors
#define CYW43_PIN_WL_DYNAMIC 1
#define CYW43_PIO_CLOCK_DIV_DYNAMIC 1

// Set the default pins to gpios 2-5
#define CYW43_DEFAULT_PIN_WL_REG_ON 1
#define CYW43_DEFAULT_PIN_WL_CS 2
#define CYW43_DEFAULT_PIN_WL_DATA_OUT 3
#define CYW43_DEFAULT_PIN_WL_DATA_IN 3
#define CYW43_DEFAULT_PIN_WL_HOST_WAKE 3
#define CYW43_DEFAULT_PIN_WL_CLOCK 4

// Default pio clock
#define CYW43_PIO_CLOCK_DIV_INT 3
#endif