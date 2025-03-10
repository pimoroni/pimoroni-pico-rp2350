import plasma
from plasma import plasma2040
from pimoroni_i2c import PimoroniI2C
from breakout_trackball import BreakoutTrackball

# SDA and SCL pins for the Tiny 2350 QW/ST connector
PINS_PLASMA_2350 = {"sda": 20, "scl": 21, "baudrate": 100000}

# Create an I2C instance and setup the trackball breakout
i2c = PimoroniI2C(**PINS_PLASMA_2350)
trackball = BreakoutTrackball(i2c)

# Set how many LEDs you have
NUM_LEDS = 100

# APA102 / DotStar™ LEDs
# led_strip = plasma.APA102(NUM_LEDS, 0, 0, plasma2040.DAT, plasma2040.CLK)

# WS2812 / NeoPixel™ LEDs
led_strip = plasma.WS2812(NUM_LEDS, 0, 0, plasma2040.DAT, rgbw=True)

# Start updating the LED strip
led_strip.start()

# Clear any previously lit LEDs
led_strip.clear()

position = 0
sensitivity = 1
hue = 0.0

while True:

    # Read the trackball data
    state = trackball.read()

    # Increase/Decrease the number of LEDs lit when moving the trackball Up/Down
    if state[BreakoutTrackball.UP] > sensitivity:
        if position < NUM_LEDS:
            position += 1
    if state[BreakoutTrackball.DOWN] > sensitivity:
        if position > 0:
            position -= 1

    # Change the hue when moving the trackball Left/Right
    if state[BreakoutTrackball.LEFT] > sensitivity:
        hue += 0.02
    if state[BreakoutTrackball.RIGHT] > sensitivity:
        hue -= 0.02

    # Set the LEDs
    for i in range(position):
        led_strip.set_hsv(i, hue, 1.0, 1.0)

    # Clear the LEDs we're not using at the moment
    for i in range(position, NUM_LEDS):
        led_strip.set_rgb(i, 0, 0, 0)
