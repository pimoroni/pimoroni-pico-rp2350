import plasma
from plasma import plasma2040

# Set how many LEDs you have
NUM_LEDS = 50

# APA102 / DotStar™ LEDs
# led_strip = plasma.APA102(NUM_LEDS, 0, 0, plasma2040.DAT, plasma2040.CLK)

# WS2812 / NeoPixel™ LEDs
led_strip = plasma.WS2812(NUM_LEDS, 0, 0, plasma2040.DAT)

# Start updating the LED strip
led_strip.start()

# Set each LED in the strip
for i in range(NUM_LEDS):
    led_strip.set_rgb(i, 100, 0, 100)

# We've told the LEDs which colour to display and now we just want to keep the program running!
while True:
    pass
