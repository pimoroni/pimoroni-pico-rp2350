'''
A simple web example that allows you to set the LED Strip colour using a colour picker.
You will need to install Phew for this example to work
In Thonny select Tools > Manage Packages and search for "micropython-phew"
'''

import network
from pimoroni import RGBLED
from phew import server, connect_to_wifi, is_connected_to_wifi
from phew.template import render_template
import plasma

# Check and import the SSID and Password from secrets.py
try:
    from secrets import WIFI_SSID, WIFI_PASSWORD
    if WIFI_SSID == "":
        raise ValueError("WIFI_SSID in 'secrets.py' is empty!")
    if WIFI_PASSWORD == "":
        raise ValueError("WIFI_PASSWORD in 'secrets.py' is empty!")
except ImportError:
    raise ImportError("'secrets.py' is missing from your Plasma 2350 W!")
except ValueError as e:
    print(e)

# Total number of LEDs on our LED strip
NUM_LEDS = 66

# APA102 / DotStar™ LEDs
# led_strip = plasma.APA102(NUM_LEDS, 0, 0, plasma2040.DAT, plasma2040.CLK)

# WS2812 / NeoPixel™ LEDs
led_strip = plasma.WS2812(NUM_LEDS, 0, 0, plasma.plasma2040.DAT, color_order=plasma.COLOR_ORDER_BGR)

# Setup the RGB Led
led = RGBLED(16, 17, 18)

last_hex = 0

# Connect our Tiny FX W to the network
connect_to_wifi(WIFI_SSID, WIFI_PASSWORD)

# If we're connected to the network, print out the IP address in the terminal
if is_connected_to_wifi():
    print("Connected")
    print(network.WLAN(network.STA_IF).ifconfig()[0])

# Start updating the LED strip
led_strip.start()


# Convert our hex value to RGB
# https://www.30secondsofcode.org/python/s/hex-to-rgb/
def hex_to_rgb(hex):
    return tuple(int(hex[i:i + 2], 16) for i in (0, 2, 4))


# We've only got one page in the root so we setup the routing for that request
# and return the index.html
@server.route("/", methods=["GET", "POST"])
def index(request):
    global last_hex
    # If a GET request is made, return the page
    if request.method == 'GET':
        return render_template("html/index.html")

    # If a POST request is made we need to process the information
    # and use that to update the LED colour
    if request.method == 'POST':
        last_hex = request.form["rgbled"]
        value = hex_to_rgb(last_hex[1:])
        led.set_rgb(value[0], value[1], value[2])
        for i in range(NUM_LEDS):
            led_strip.set_rgb(i, value[0], value[1], value[2])
        return render_template("html/index.html")


# catchall
@server.catchall()
def catchall(request):
    return "Not found", 404


# Run the server!
server.run()
