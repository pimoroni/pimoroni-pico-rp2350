MODULES_PY = "../../../pimoroni-pico/micropython/modules_py"

# SD Card
require("sdcard")

freeze(MODULES_PY, "gfx_pack.py")
freeze(MODULES_PY, "inventor.py")

freeze(MODULES_PY, "pimoroni.py")
freeze(MODULES_PY, "boot.py")
