# Override the MicroPython board name
# And set basic options which are expanded upon in mpconfigboard.h
list(APPEND MICROPY_DEF_BOARD
    "MICROPY_HW_BOARD_NAME=\"Pimoroni Pico Plus 2 (PSRAM)\""
    "MICROPY_HW_ENABLE_PSRAM=1"
)
