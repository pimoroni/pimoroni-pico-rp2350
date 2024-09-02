require("bundle-networking")

include("manifest.py")

freeze("$(BOARD_DIR)/../../modules_py", "lte.py")