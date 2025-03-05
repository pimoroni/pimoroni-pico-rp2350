import time
import machine

# Setup for the button pins
user_button = machine.Pin(22, machine.Pin.IN)
a_button = machine.Pin(12, machine.Pin.IN, machine.Pin.PULL_UP)

while True:

    if user_button.value() == 0:
        print("USER BUTTON PRESSED!")

    if a_button.value() == 0:
        print("A BUTTON PRESSED!")

    time.sleep(0.2)
