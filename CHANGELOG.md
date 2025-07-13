# Changes for v0.5.0

* Internal restructuring; simplified CMakeLists.txt files
* Added sample application

# Changes for v0.4.8

* fixed build issues on older distributions
* system_sup: dont use argument for controling LSE
* obtain: copy HAL licence file from repo instead of downloading it

# Changes for v0.4.7

* obtain: updated various versions
* obtain_github.sh: optionally use DATA environment variable
* obtain_github.sh: use git directly to receive files instead of archive files

# Changes for v0.4.6

* fixed URLs from GitHub

# Changes for v0.4.5

* minor fixes

# Changes for v0.4.4

* minor fixes

# Changes for v0.4.3

* minor fixes

# Changes for v0.4.2

* fixed clock configuration for several MCUs
* fix for hardware crc stm32g0 and stm32g4
* obtain-script: fix url for license file

# Changes for v0.4.1

* added support for stm32g0

# Changes for v0.4.0

* fixed cmake warningadded support for STM32G0
* added lock to support simultanious runs of obtain-script

# Changes for v0.3.3

* fixed cmake warning

# Changes for v0.3.2

* obtain: updated Cube revisions
* minor changes

# Changes for v0.3.1

* minor fixes

# Changes for v0.3.0

* [#389] copy HAL sources to binary direcotry instead of source directory
* cmake: renamed project to libHALWrapper
* obtain: use concrete revisions fr all MCUs
* depend on license file to force fresh obtaining when file is missing
* obtain: install license files
* obtain: download sources to /tmp instead of source directory
* minor fixes

# Changes for v0.2.2

* minor build fixes for MCUs
* renamed shw to HALWrapper
* install license files
* obtain: use concrete versions of HAL library for all MCUs
* moves HAL sources to build directory

# Changes for v0.2.1

* minor fixes and compiler warnings

