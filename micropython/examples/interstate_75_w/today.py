import time

import machine
import network
import ntptime
from interstate75 import DISPLAY_INTERSTATE75_128X128, Interstate75

SHADOW_OFFSET = 1

# Check and import the Network SSID and Password from secrets.py
try:
    from secrets import WIFI_PASSWORD, WIFI_SSID
    if WIFI_SSID == "":
        raise ValueError("WIFI_SSID in 'secrets.py' is empty!")
    if WIFI_PASSWORD == "":
        raise ValueError("WIFI_PASSWORD in 'secrets.py' is empty!")
except ImportError:
    raise ImportError("'secrets.py' is missing from your Plasma 2350 W!")
except ValueError as e:
    print(e)

rtc = machine.RTC()

DAYS = ["Mon", "Tue", "Wed", "Thur", "Fri", "Sat", "Sun"]

# Enable the Wireless
wlan = network.WLAN(network.STA_IF)
wlan.active(True)


def network_connect(SSID, PSK):

    # Number of attempts to make before timeout
    max_wait = 5

    # Sets the Wireless LED pulsing and attempts to connect to your local network.
    print("connecting...")
    wlan.config(pm=0xa11140)  # Turn WiFi power saving off for some slow APs
    wlan.connect(SSID, PSK)

    while max_wait > 0:
        if wlan.status() < 0 or wlan.status() >= 3:
            break
        max_wait -= 1
        print('waiting for connection...')
        time.sleep(1)

    # Handle connection error. Switches the Warn LED on.
    if wlan.status() != 3:
        print("Unable to connect. Attempting connection again")


# Function to sync the Pico RTC using NTP
def sync_time():

    try:
        network_connect(WIFI_SSID, WIFI_PASSWORD)
    except NameError:
        print("Create secrets.py with your WiFi credentials")

    if wlan.status() < 0 or wlan.status() >= 3:
        try:
            ntptime.settime()
        except OSError:
            print("Unable to sync with NTP server. Check network and try again.")


# Setup for the display
i75 = Interstate75(
    display=DISPLAY_INTERSTATE75_128X128, stb_invert=False, panel_type=Interstate75.PANEL_GENERIC)
display = i75.display

WIDTH, HEIGHT = display.get_bounds()

# Pens
RED = display.create_pen(120, 0, 0)
WHITE = display.create_pen(255, 255, 255)
BLACK = display.create_pen(0, 0, 0)

sync_time()

while True:

    current_t = rtc.datetime()

    # Set the pen to Red and clear the screen.
    display.set_pen(WHITE)
    display.clear()

    # Measures the length of the text to help us with centring later.
    day_length = display.measure_text(DAYS[current_t[3]], 4)
    date_length = display.measure_text(str(current_t[2]), 7)

    # Red banner
    display.set_pen(RED)
    display.rectangle(0, 0, WIDTH, 30)

    # Drop Shadow
    display.set_font("bitmap6")
    display.set_pen(BLACK)

    display.text(DAYS[current_t[3]], (WIDTH // 2) - (day_length // 2) + SHADOW_OFFSET, 2 + SHADOW_OFFSET, WIDTH, 4)

    display.set_font("bitmap8")
    display.text(str(current_t[2]), (WIDTH // 2) - (date_length // 2) + SHADOW_OFFSET + 4, 55 + SHADOW_OFFSET, WIDTH, 7)

    # Main Text
    display.set_font("bitmap6")
    display.set_pen(WHITE)
    display.text(DAYS[current_t[3]], (WIDTH // 2) - (day_length // 2), 2, WIDTH, 4)

    display.set_pen(RED)
    display.set_font("bitmap8")
    display.text(str(current_t[2]), (WIDTH // 2) - (date_length // 2) + 4, 55, WIDTH, 7)

    display.set_pen(display.create_pen(0, 0, 0))

    i75.update()
