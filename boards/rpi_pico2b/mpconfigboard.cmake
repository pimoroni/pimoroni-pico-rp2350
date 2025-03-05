# cmake file for Raspberry Pi Pico
set(PICO_BOARD "pico2b")
set(PICO_PLATFORM "rp2350")

set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR})

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)

set(MICROPY_C_HEAP_SIZE 4096)

set(PICO_NUM_GPIOS 48)
