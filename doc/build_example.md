# Build the example

This example will run an example application on an "STMicroelectronics 
NUCLEO-F303K8" device. The application will print "Hello world!" on the UART 
interface and the user LED will blink continuously.

## Prerequisite

The example assumes that the host computer is an debian based system and
following packages are installed:

* gcc-arm-none-eabi
* openocd
* gdb-multiarch

The example is for an "STMicroelectronics NUCLEO-F303K8" device.
```shell
mkdir -p build
cd build
cmake .. -DMCU_REV_LONG=f303x8 -DBUILD_EXAMPLE=1
make -j$(nproc)
```

## Flash the example

Start OpenOCD in seperate terminal:
```shell
openocd -f /usr/share/openocd/scripts/board/st_nucleo_f3.cfg
```
Use GDB for flashing binary:
```shell
cat << EOF > gdb_commands.txt
set arm abi AAPCS
target remote localhost:3333
monitor reset init
monitor flash write_image erase ${PWD}/example/hello_world.bin 0x08000000
monitor reset run
detach
quit
EOF

/usr/bin/gdb-multiarch --command=gdb_commands.txt
```

## Debug application

The following example will use GDB to attach to OpenOCD, halt the MCU and show
the current position in the code.

Start GDB:
```shell
gdb-multiarch example/hello_world
```
Connect to the OpenOCD server:
```shell
set arm abi AAPCS 
target remote localhost:3333
```
GDB will show you the current position in the application and halt the device.
The LED will stop blinking.
The command 'continue' will continue running the application. The LED should
blink again.

