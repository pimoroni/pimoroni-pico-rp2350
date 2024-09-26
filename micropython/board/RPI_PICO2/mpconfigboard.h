// Board and hardware specific configuration
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

// Set up networking.
#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "Pico2"

#if defined(MICROPY_PY_NETWORK_CYW43)

// CYW43 driver configuration.
#define CYW43_USE_SPI                           (1)
#define CYW43_LWIP                              (1)
#define CYW43_GPIO                              (1)
#define CYW43_SPI_PIO                           (1)

#define MICROPY_HW_PIN_EXT_COUNT                CYW43_WL_GPIO_COUNT

#if defined(CYW43_PIN_WL_DYNAMIC)

#define CYW43_PIO_CLOCK_DIV_DYNAMIC             (1)

// CYW43 default pin configuration
#define CYW43_DEFAULT_PIN_WL_HOST_WAKE          24u
#define CYW43_DEFAULT_PIN_WL_REG_ON             23u
#define CYW43_DEFAULT_PIN_WL_DATA_OUT           CYW43_DEFAULT_PIN_WL_HOST_WAKE
#define CYW43_DEFAULT_PIN_WL_DATA_IN            CYW43_DEFAULT_PIN_WL_HOST_WAKE
#define CYW43_DEFAULT_PIN_WL_CLOCK              29u
#define CYW43_DEFAULT_PIN_WL_CS                 25u

// Slow down the wireless clock, since we'll be running
// comms through wiring spaghetti!
#define CYW43_PIO_CLOCK_DIV_INT                 50
#define CYW43_PIO_CLOCK_DIV_FRAC                0
#define CYW43_SPI_PROGRAM_NAME                  spi_gap0_sample1

#endif

#endif

// Might be defined in mpconfigvariant_PPP.cmake
// This is not checked by mpconfigport.h so we must set up networking below
#if defined(MICROPY_PY_NETWORK_PPP_LWIP)

// Nothing to do here?

#endif

// If a variant is not used, define a fallback board name
#ifndef MICROPY_HW_BOARD_NAME

#define MICROPY_HW_BOARD_NAME                   "Raspberry Pi Pico 2"

#endif