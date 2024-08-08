# cmake file for Raspberry Pi Pico
set(PICO_BOARD "pimoroni_pico_plus2_rp2350")
set(PICO_PLATFORM "rp2350")
set(PICO_NUM_GPIOS 48)

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)

set(MICROPY_C_HEAP_SIZE 4096)
