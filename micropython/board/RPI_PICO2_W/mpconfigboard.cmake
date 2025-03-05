# cmake file for Raspberry Pi Pico 2 W
set(PICO_BOARD "pico2_w")

# To change the gpio count for QFN-80
# set(PICO_NUM_GPIOS 48)

# Links micropy_lib_lwip and sets MICROPY_PY_LWIP = 1
# Picked up and expanded upon in mpconfigboard.h
set(MICROPY_PY_LWIP ON)

include(enable_cyw43.cmake)

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)