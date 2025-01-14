export TERM=${TERM:="xterm-256color"}

function log_success {
	echo -e "$(tput setaf 2)$1$(tput sgr0)"
}

function log_inform {
	echo -e "$(tput setaf 6)$1$(tput sgr0)"
}

function log_warning {
	echo -e "$(tput setaf 1)$1$(tput sgr0)"
}

function micropython_clone {
    log_inform "Using MicroPython $MICROPYTHON_VERSION"
    git clone https://github.com/$MICROPYTHON_FLAVOUR/micropython
    cd micropython
    git checkout $MICROPYTHON_VERSION
    git submodule update --init lib/pico-sdk
    git submodule update --init lib/cyw43-driver
    git submodule update --init lib/lwip
    git submodule update --init lib/mbedtls
    git submodule update --init lib/micropython-lib
    git submodule update --init lib/tinyusb
    git submodule update --init lib/btstack
    cd ../
}

function micropython_build_mpy_cross {
    cd micropython/mpy-cross
    ccache --zero-stats || true
    CROSS_COMPILE="ccache " USER_C_MODULES= make
    ccache --show-stats || true
    cd ../../
}

function apt_install_build_deps {
    sudo apt update && sudo apt install ccache
}

function micropython_version {
    echo "MICROPY_GIT_TAG=$MICROPYTHON_VERSION, $BOARD_NAME $TAG_OR_SHA" >> $GITHUB_ENV
    echo "MICROPY_GIT_HASH=$MICROPYTHON_VERSION-$TAG_OR_SHA" >> $GITHUB_ENV
}

function cmake_configure {
    cmake -S micropython/ports/rp2 -B build-$BOARD_NAME \
    -DPICO_BUILD_DOCS=0 \
    -DPICO_NO_COPRO_DIS=1 \
    -DUSER_C_MODULES=$USER_C_MODULES \
    -DMICROPY_BOARD_DIR=$MICROPY_BOARD_DIR \
    -DMICROPY_BOARD=$MICROPY_BOARD \
    -DMICROPY_BOARD_VARIANT=$MICROPY_BOARD_VARIANT \
    -DCMAKE_C_COMPILER_LAUNCHER=ccache \
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
}

function cmake_build {
    ccache --zero-stats || true
    cmake --build build-$BOARD_NAME -j 2
    ccache --show-stats || true
    cd build-$BOARD_NAME
    cp firmware.uf2 $RELEASE_FILE.uf2
}
