# micropython/ports/rp2/../../../
MODULES_PY = "$(PORT_DIR)/../../../pimoroni-pico/micropython/modules_py"

# SD Card
require("sdcard")

freeze(MODULES_PY, "gfx_pack.py")

freeze(MODULES_PY, "pimoroni.py")
freeze(MODULES_PY, "boot.py")

freeze(MODULES_PY, "lte.py")
