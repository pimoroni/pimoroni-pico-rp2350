require("bundle-networking")

# Bluetooth
require("aioble")

include("$(PORT_DIR)/boards/manifest.py")

include("../manifest_pico2.py")

freeze("$(BOARD_DIR)/../../modules_py", "lte.py")