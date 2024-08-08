// Board and hardware specific configuration
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Tiny 2350"
#define MICROPY_HW_FLASH_STORAGE_BYTES          (1024 * 1024 * 7)

// I2C0 (non-default)
#define MICROPY_HW_I2C0_SCL  (4)
#define MICROPY_HW_I2C0_SDA  (5)