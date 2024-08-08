// Board and hardware specific configuration
#ifndef MICROPY_HW_BOARD_NAME
// Might be defined by mpconfigvariant.cmake
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Pico Plus 2"
#endif
#define MICROPY_HW_FLASH_STORAGE_BYTES          (1024 * 1024 * 15)

#define MICROPY_HW_PSRAM_CS_PIN                 PIMORONI_PICO_PLUS2_PSRAM_CS_PIN
