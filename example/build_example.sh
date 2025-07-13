#!/bin/bash

set -e -u

cd ..
S=$PWD
target=example/hello_world

rm -rf build
mkdir -p build
cd build
rm -f ${target}
rm -f ${target}.bin

export CC=arm-linux-gnueabihf-gcc-14
export CXX=arm-linux-gnueabihf-g++-14
export OBJCOPY=arm-linux-gnueabihf-objcopy
export CM_CFLAGS="-march=armv7e-m -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -mabi=aapcs -save-temps -fno-exceptions -fno-stack-protector -ffreestanding -ffunction-sections -fdata-sections"
export CM_CFLAGS="$CM_CFLAGS -flto"

export CM_LDFLAGS="-Wl,-nostdlib -Wl,-L${S}/example/scripts -Wl,-T,${S}/example/scripts/stm32f303x8.ld -Wl,--build-id=none -Wl,--gc-sections -nostdlib"
export CM_LDFLAGS="$CM_LDFLAGS -flto"


cmake .. -DMCU_REV_LONG=f303x8 \
	-DCMAKE_C_COMPILER=$CC \
	-DCMAKE_CXX_COMPILER=$CXX \
	-DCMAKE_C_FLAGS="$CM_CFLAGS" \
	-DCMAKE_CXX_FLAGS="$CM_CFLAGS" \
	-DCMAKE_EXE_LINKER_FLAGS="$CM_LDFLAGS" \
	-DCMAKE_SYSTEM_PROCESSOR=arm \
	-DCMAKE_CROSSCOMPILING=1 \
	-DCMAKE_SYSTEM_NAME=Generic \
	-DCMAKE_C_COMPILER_WORKS=1 \
	-DCMAKE_CXX_COMPILER_WORKS=1 \
	-DCMAKE_BUILD_TYPE=Debug \
	-DBUILD_EXAMPLE=1

make -j$(nproc)
# VERBOSE=0

${OBJCOPY} -S -O ihex ${target} ${target}.hex
${OBJCOPY} -S --strip-unneeded --strip-debug -O binary ${target} ${target}.bin

ls -l ${target}.bin ..


#--- fin ----------------------------------------------------------------------
