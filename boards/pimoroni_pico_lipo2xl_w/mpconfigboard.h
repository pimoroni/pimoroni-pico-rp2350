// Board and hardware specific configuration
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Pico LiPo 2XL W"
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - 1024 * 1024 * 2)

#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "PicoLiPo2XLW"

// Enable PPP
#define MICROPY_PY_NETWORK_PPP_LWIP             (1)

#include "enable_cyw43.h"

// PSRAM Settings
#define MICROPY_HW_ENABLE_PSRAM                 (1)
#define MICROPY_HW_PSRAM_CS_PIN                 PIMORONI_PICO_LIPO2_PSRAM_CS_PIN
#define MICROPY_GC_SPLIT_HEAP                   (1)