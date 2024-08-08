# Override the MicroPython board name
list(APPEND MICROPY_DEF_BOARD
    "MICROPY_HW_ENABLE_PSRAM=1"
    "MICROPY_HW_BOARD_NAME=\"Pimoroni Pico Plus 2 (PSRAM)\""
)
