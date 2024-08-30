// Board and hardware specific configuration
#ifndef MICROPY_HW_BOARD_NAME
// Might be defined by mpconfigvariant.cmake
#define MICROPY_HW_BOARD_NAME                   "Pimoroni Pico Plus 2"
#endif
#define MICROPY_HW_FLASH_STORAGE_BYTES          (PICO_FLASH_SIZE_BYTES - (2 * 1024 * 1024))

#define MICROPY_HW_PSRAM_CS_PIN                 PIMORONI_PICO_PLUS2_PSRAM_CS_PIN

#ifdef PPP_ENABLE_PPP

// Enable networking.
#define MICROPY_PY_NETWORK                      1
#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT     "Pico"

#define MICROPY_PY_NETWORK_PPP_LWIP             1

#define MICROPY_HW_NIC_PPP                      { MP_ROM_QSTR(MP_QSTR_PINT), MP_ROM_PTR(&mp_network_ppp_lwip_type) },

#define MICROPY_BOARD_NETWORK_INTERFACES \
    MICROPY_HW_NIC_PPP

#define MICROPY_PY_SOCKET_EXTENDED_STATE        1

#endif