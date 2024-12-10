import plasma
from plasma import plasma2040
import time

# Set how many LEDs you have
NUM_LEDS = 66

# APA102 / DotStar™ LEDs
# led_strip = plasma.APA102(NUM_LEDS, 0, 0, plasma2040.DAT, plasma2040.CLK)

# WS2812 / NeoPixel™ LEDs
led_strip = plasma.WS2812(NUM_LEDS, 0, 0, plasma2040.DAT, color_order=plasma.COLOR_ORDER_BGR)

# Start updating the LED strip
led_strip.start()

offset = 0.0

while True:

    offset += float(10) / 2000.0

    for i in range(NUM_LEDS):
        hue = float(i) / NUM_LEDS
        led_strip.set_hsv(i, hue+offset, 1.0, 1.0)

    time.sleep(1.0 / 60)
