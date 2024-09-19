// Board and hardware specific configuration
#ifndef MICROPY_HW_BOARD_NAME
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Plasma 2350"
#endif
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

// I2C0 (non-default)
#define MICROPY_HW_I2C0_SCL  (PLASMA2350_SDA_PIN)
#define MICROPY_HW_I2C0_SDA  (PLASMA2350_SCL_PIN)

// Set up networking.

#if defined(MICROPY_PY_NETWORK_CYW43)

#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "Plasma2350"

// CYW43 driver configuration.
#define CYW43_USE_SPI                           (1)
#define CYW43_LWIP                              (1)
#define CYW43_GPIO                              (1)
#define CYW43_SPI_PIO                           (1)

#define MICROPY_HW_PIN_EXT_COUNT                CYW43_WL_GPIO_COUNT

#endif