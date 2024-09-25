// Board and hardware specific configuration
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

#define MICROPY_HW_PSRAM_CS_PIN                 PIMORONI_PICO_PLUS2_PSRAM_CS_PIN

// Might be defined in mpconfigvariant_PSRAM.cmake
// or mpconfigvariant_WIRELESS.cmake
#if defined(MICROPY_HW_ENABLE_PSRAM)

#define MICROPY_GC_SPLIT_HEAP                   (1)

#endif

// Set up networking.
#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "PPP2"

#if defined(MICROPY_PY_NETWORK_CYW43)

// CYW43 driver configuration.
#define CYW43_USE_SPI                           (1)
#define CYW43_LWIP                              (1)
#define CYW43_GPIO                              (1)
#define CYW43_SPI_PIO                           (1)

#define MICROPY_HW_PIN_EXT_COUNT                CYW43_WL_GPIO_COUNT

#if defined(CYW43_PIN_WL_DYNAMIC)

#define CYW43_PIO_CLOCK_DIV_DYNAMIC             (1)

// Defined by pimoroni_pico_plus2w_rp2350.h
//#define CYW43_DEFAULT_PIN_WL_HOST_WAKE          SPICE_RESET_MOSI_PIN
//#define CYW43_DEFAULT_PIN_WL_REG_ON             SPICE_TX_MISO_PIN
#define CYW43_DEFAULT_PIN_WL_DATA_OUT           CYW43_DEFAULT_PIN_WL_HOST_WAKE
#define CYW43_DEFAULT_PIN_WL_DATA_IN            CYW43_DEFAULT_PIN_WL_HOST_WAKE
#define CYW43_DEFAULT_PIN_WL_CLOCK              29u
#define CYW43_DEFAULT_PIN_WL_CS                 25u

/* SPICE alternative 
#define CYW43_DEFAULT_PIN_WL_HOST_WAKE          SPICE_RESET_MOSI_PIN
#define CYW43_DEFAULT_PIN_WL_REG_ON             SPICE_TX_MISO_PIN
#define CYW43_DEFAULT_PIN_WL_DATA_OUT           SPICE_RESET_MOSI_PIN
#define CYW43_DEFAULT_PIN_WL_DATA_IN            SPICE_RESET_MOSI_PIN
#define CYW43_DEFAULT_PIN_WL_CLOCK              SPICE_NETLIGHT_SCK_PIN
#define CYW43_DEFAULT_PIN_WL_CS                 SPICE_RX_CS_PIN
*/

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

#define MICROPY_HW_BOARD_NAME                   "Pimoroni Pico Plus 2"

#endif