"""
Get a cat fact from t'internet!
You will need to add your wireless SSID and password to secrets.py (and save this file to your Plasma)
"""

import network
import requests
from secrets import WIFI_SSID, WIFI_PASSWORD
from time import sleep

# Specify the pins that that wireless module is connected to
# The pins below are for a Plasma 2350 with a RM2 breakout connected via SP/CE
wlan = network.WLAN(network.STA_IF, pin_on=8, pin_out=11, pin_in=11, pin_wake=11, pin_clock=10, pin_cs=9)

# connect to wifi
wlan.active(True)
wlan.connect(WIFI_SSID, WIFI_PASSWORD)
while wlan.isconnected() is False:
    print('Waiting for connection...')
    sleep(1)

request = requests.get('http://catfact.ninja/fact').json()
fact = request['fact']
print('Cat fact!')
print(fact)
