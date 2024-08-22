// Board and hardware specific configuration
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Plasma 2350"
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

// I2C0 (non-default)
#define MICROPY_HW_I2C0_SCL  (PLASMA2350_SDA_PIN)
#define MICROPY_HW_I2C0_SDA  (PLASMA2350_SCL_PIN)