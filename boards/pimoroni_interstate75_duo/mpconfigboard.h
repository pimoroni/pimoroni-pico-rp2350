// Board and hardware specific configuration
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

// Set up networking.
#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "Interstate75Duo"

#define MICROPY_HW_BOARD_NAME                   "Pimoroni Interstate 75 Duo"

// Enable WiFi & PPP
#define MICROPY_PY_NETWORK                      (1)

// CYW43 driver configuration.
#define CYW43_USE_SPI                           (1)
#define CYW43_LWIP                              (1)
#define CYW43_GPIO                              (0)
#define CYW43_SPI_PIO                           (1)

int mp_hal_is_pin_reserved(int n);
#define MICROPY_HW_PIN_RESERVED(i) mp_hal_is_pin_reserved(i)
