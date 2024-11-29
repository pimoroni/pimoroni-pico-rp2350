'''
An example that uses the buttons to control the colour and brightness of the attached LED strip.

Button A - Change the hue
BOOT/User button - Cycle through brightness. 10 levels of brightness available.

'''
import time

import machine
import plasma
from plasma import plasma2040

# Set how many LEDs you have
NUM_LEDS = 66

# Setup for the button pins
user_button = machine.Pin(22, machine.Pin.IN)
a_button = machine.Pin(12, machine.Pin.IN, machine.Pin.PULL_UP)

# WS2812 / NeoPixel™ LEDs
led_strip = plasma.WS2812(NUM_LEDS, 0, 0, plasma2040.DAT, color_order=plasma.COLOR_ORDER_BGR)

# Start updating the LED strip
led_strip.start()

hue = 0.0
brightness = 1.0

while True:

    if a_button.value() == 0:
        hue += float(10) / 2000.0
        time.sleep(0.02)

    if user_button.value() == 0:
        if brightness >= 0.0 and brightness < 1.0:
            brightness += 0.1
        else:
            brightness = 0.0

        # Wait until the user releases the button
        while user_button.value() == 0:
            pass

    # Set each LED in the strip to the colour we want
    for i in range(NUM_LEDS):
        led_strip.set_hsv(i, hue, 1.0, brightness)
