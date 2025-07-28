# LibHALWrapper

LibHALWrapper provides the HAL libraries from ST for STM32 along with CMSIS 
code and supplementary code. It is the first step to detach application 
source code from actual used MCU model.

This repository does not contain any HAL source files. The sources are 
automatically obtained from ST repositories. No source files of the downloaded
code should be changed because changes are not tracked in this repository and
may get overwritten automatically.

LibHALWrapper helps to develop application which are not determined for a 
specific MCU model. Generic code can be written and at compile time (more exact:
when running cmake) a specific MCU model gan be specified.

![chart](doc/chart.png)

LibHALWrapper is used by the libraries "libbiwak" and "libarena". They provide 
further abstraction. This way the same application can be compiled for 
different MCU models or PCB layouts.

## Build Standalone

The library should be used as subdirectory in a cmake project. But it can also 
be build standalone.

**Warning:**
It is not recommended to compile the library as standalone and to 
install it to the target sysroot. The startup code depends on the specific MCU
revision.

### Prerequisite

An toolchain for stm32 controllers has to be installed on the host and the system
must be configured to use the toolchain e.g. by having environment variables set 
correctly.

For flashing binaries to stm32 devices, "openocd" is needed on the host
system.

On an Debian based host systems, following packages can be used:

* gcc-arm-none-eabi
* binutils-arm-none-eabi
* openocd
* gdb-multiarch

### CMake

The cmake variable "MCU" has to specify the target MCU.
When running the cmake command, a script to obtain the source files from ST 
Github repositories. Per default, the repositories will be stored in 
"$HOME/.cache/HALWrapper". To use an different directory, the environment 
variable HAL_ARCHIVE_PATH can be set.
The correct compiler flags for the used Microcontroller have to be configured.
This can be done for example by setting CMake variables ( CMAKE_C_FLAGS, 
CMAKE_CXX_FLAGS, ...) or by providing a corresponding toolchain file.
Alternatively the option "MCU_AUTO_FLAGS" can be set. libHALWrapper will set 
the compiler flags automatically then.

**Warning:**
Only when building the example, the necessary compiler flags for the specific
MCU are configured automatically.
Otherwise they have to be set manually or in the husk cmake file.

**Example:**
```shell
mkdir -p build
cd build
cmake .. -DMCU=stm32f303x8 \
           -DCMAKE_C_COMPILER=arm-none-eabi-gcc \
           -DCMAKE_CXX_COMPILER=arm-none-eabi-g++ \
           -DCMAKE_C_COMPILER_WORKS=1 \
           -DCMAKE_CXX_COMPILER_WORKS=1 \
           -DCMAKE_C_FLAGS="-mcpu=cortex-m4"
make -j$(nproc)
```

### Install Library files

**Warning:**
Do not install the library into the root filesystem of your host system.

**Example:**
```shell
make install DESTDIR=../install
``` 

## Build the example

This example will run an example application on an "STMicroelectronics 
NUCLEO-F303K8" device. The application will print "Hello world!" on the UART 
interface and the user LED will blink continuously.

### Prerequisite

The example assumes that the host computer is an debian based system and
following packages are installed:

* gcc-arm-none-eabi
* openocd
* gdb-multiarch

If a different toolchain is used, the variables have to be adjusted accordingly.

The example is for an "STMicroelectronics NUCLEO-F303K8" device. The compiler
flags for the MCU are set automatically for the example.
```shell
mkdir -p build
cd build
cmake .. \
    -DMCU=stm32f303x8 \
    -DCMAKE_C_COMPILER=arm-none-eabi-gcc \
    -DCMAKE_CXX_COMPILER=arm-none-eabi-g++ \
    -DCMAKE_C_COMPILER_WORKS=1 \
    -DCMAKE_CXX_COMPILER_WORKS=1 \
    -DBUILD_EXAMPLE=1 \
    -DMCU_AUTO_FLAGS=1
make -j$(nproc)
```

### Flash the example

Start OpenOCD in seperate terminal:
```shell
openocd -f /usr/share/openocd/scripts/board/st_nucleo_f3.cfg
```
Generate the actual binary from ELF file:
```shell
arm-none-eabi-objcopy -S --strip-unneeded --strip-debug -O binary example/hello_world example/hello_world.bin
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

### Debug application

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

## Integrate in CMake project as subdirectory

A CMake husk file can be created and libHALWrapper can be integrated as 
subdirectory. This avoids problems when working with different MCUs with 
different compiler settings.

Example for CMakeLists.txt:
```cmake
cmake_minimum_required( VERSION 3.11 )

project( hello CXX )

set( MCU_AUTO_FLAGS 1 )
add_subdirectory( libHALWrapper )

add_executable(
    hello
    src/main.cpp
)

target_link_libraries(
   hello
   HALWrapper-${MCU_REV}
)
```

## Defines

LibHALWrapper will automatically set some prefines describing the target MCU.
These are needed by the HAL source code.
For example when building for an "stm32f303x8", following defines would be set:

| Define        | Value        |
| ------------- | ------------ |
| STM32F3       |              |
| STM32F303     |              |
| STM32F303xx   |              |
| STM32F303x8   |              |
| STM32F303     |              |
| MCU_REV       | f3           |
| MCU           | stm32f303x8  |

## Configuration

The configuration header file used in HAL is the default template header.

## Predefines

Some configuration can be set via preprocessor predefines:

| Define                    | Component | Description                                                                                                                                                 |
| ------------------------- | --------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| USE_LSE                   | SUP       | Configure the external low speed oszilator. Needed for RTC running on Standby with battery. Not implemented for all MCUs clock configuration functions yet. |
| USE_FULL_ASSERT           | HAL       | Perform sanity check on many function calls. Only usefull for development.                                                                                  |

## CMake Variables

| Define                    | Component | Description                                                                                         |
| ------------------------- | --------- | --------------------------------------------------------------------------------------------------- |
| MCU_AUTO_FLAGS            | CMake     | When this option is set, adding libHALWrapper as subdirectory will set compiler flags for given MCU |
| BUILD_EXAMPLE             | CMake     | Build the example. This can only be done when libHALWrapper is the top level CMake project.         |

## CMake Modules

| Define    | Description                                                                                         |
| --------- | --------------------------------------------------------------------------------------------------- |
| MCURev    | Parses the variable 'MCU' and sets others like MCU_REV. Internally used by CMakeLists.txt.          |
| MCUFlags  | Set compiler flags for given mcu family. Automatically used when building example.                  |
| MCUShrink | Set compiler/linker flags for very small binary size. Automatically used when building example.     |

## Clock configuration

For each MCU family a default configuration is present. It can be initialized
with (pseudo-) function "SystemClock_Config()" called in main. Afer this the HAL function
"SystemCoreClockUpdate()" has to be called.

If a special clock configuration is needed, the default weak function can be 
overloaded with an custom  strong function. E.g. for an stm32f303x8 the function
"void SystemClock_Config_f3( void )" has to be implemented as strong function.

# FAQ

* Compiler throws errors like "Error: selected processor does not support `sev' in ARM mode"
  Compiler flags are not set correctly. You can set the cmake variable "MCU_AUTO_FLAGS" or include the cmake package 'MCUFlags' in your CMakeLists.txt file.

* Linker message "undefined reference to `__exidx_start'"
  You are probably using a toolchain wich is using newlib. You have to specify "--specs=nano".
