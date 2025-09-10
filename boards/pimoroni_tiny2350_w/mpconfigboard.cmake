# cmake file for Raspberry Pi Pico
set(PICO_BOARD "pimoroni_tiny2350")
set(PICO_PLATFORM "rp2350")

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)

# Links micropy_lib_lwip and sets MICROPY_PY_LWIP = 1
# Picked up and expanded upon in mpconfigboard.h
set(MICROPY_PY_LWIP ON)

include(enable_cyw43.cmake)

set(MICROPY_C_HEAP_SIZE 4096)

include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)
