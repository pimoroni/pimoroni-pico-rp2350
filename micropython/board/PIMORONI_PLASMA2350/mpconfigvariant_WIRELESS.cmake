# Override the MicroPython board name
# And set basic options which are expanded upon in mpconfigboard.h
list(APPEND MICROPY_DEF_BOARD
    "MICROPY_HW_BOARD_NAME=\"Pimoroni Plasma 2350 (Wireless)\""
    "MICROPY_PY_NETWORK=1"
)

# Board and platform
set(PICO_BOARD "pimoroni_plasma2350w")
set(PICO_PLATFORM "rp2350")

# Links micropy_lib_lwip and sets MICROPY_PY_LWIP = 1
# Picked up and expanded upon in mpconfigboard.h
set(MICROPY_PY_LWIP ON)

# Links cyw43-driver and sets:
# MICROPY_PY_NETWORK_CYW43 = 1,
# MICROPY_PY_SOCKET_DEFAULT_TIMEOUT_MS = 30000
set(MICROPY_PY_NETWORK_CYW43 ON)

# Adds mpbthciport.c
# And sets:
# MICROPY_PY_BLUETOOTH = 1,
# MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS = 1,
# MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE = 1
set(MICROPY_PY_BLUETOOTH ON)

# Links pico_btstack_hci_transport_cyw43
# And sets:
# MICROPY_BLUETOOTH_BTSTACK = 1,
# MICROPY_BLUETOOTH_BTSTACK_CONFIG_FILE =
set(MICROPY_BLUETOOTH_BTSTACK ON)

# Sets:
# CYW43_ENABLE_BLUETOOTH = 1,
# MICROPY_PY_BLUETOOTH_CYW43 = 1
set(MICROPY_PY_BLUETOOTH_CYW43 ON)

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest-wireless.py)

set(MICROPY_C_HEAP_SIZE 4096)

set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR})