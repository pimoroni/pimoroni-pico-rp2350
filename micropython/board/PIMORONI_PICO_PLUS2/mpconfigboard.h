// Board and hardware specific configuration
#ifndef MICROPY_HW_BOARD_NAME
// Might be defined by mpconfigvariant.cmake
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Pico Plus 2"
#endif
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

#define MICROPY_HW_PSRAM_CS_PIN                 PIMORONI_PICO_PLUS2_PSRAM_CS_PIN

// Might be defined in mpconfigvariant_PSRAM.cmake
// or mpconfigvariant_PPP.cmake
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

#endif

// Might be defined in mpconfigvariant_PPP.cmake
// This is not checked by mpconfigport.h so we must set up networking below
#if defined(MICROPY_PY_NETWORK_PPP_LWIP)

// Nothing to do here?

#endif