"""

Simple example to display cover art.

Album art should be saved in 128 x 128 resolution PNG format
and placed in a folder called 'covers' in the root.

"""

import time
from interstate75 import Interstate75, DISPLAY_INTERSTATE75_128X128
import pngdec
import os
from random import choice

# Time between covers
INTERVAL = 10

# Setup for the display
i75 = Interstate75(display=DISPLAY_INTERSTATE75_128X128, stb_invert=False, panel_type=Interstate75.PANEL_GENERIC)
display = i75.display
WIDTH, HEIGHT = display.get_bounds()

p = pngdec.PNG(display)


while True:

    # Select a PNG image from our 'covers' folder at random
    file = choice(os.listdir("covers"))
    img = f"covers/{file}"

    p.open_file(img)

    # Decode our PNG file and set the X and Y
    p.decode(0, 0)

    i75.update()
    time.sleep(INTERVAL)
