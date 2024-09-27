require("bundle-networking")

# Bluetooth
require("aioble")

include("manifest.py")

freeze("$(BOARD_DIR)/../../modules_py", "lte.py")