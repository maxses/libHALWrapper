#!/bin/bash
#------------------------------------------------------------------------------
#
# \brief    Obtains STM32 HAL libraries from github
#
#           Receives STM32 HAL libraries for specific MCU and copies necccessary
#           files for libHALWrapper.
#
#           This script is designed to be executed from CMakeLists.txt from
#           libHALWrapper.
#
#           The Repositories are stored "$HOME/.cache/HALWrapper". This can be
#           changed by setting environment variable "HAL_ARCHIVE_PATH" to a
#           custom path.
#           The repositories do NOT get removed when script has finished.
#
#           As argument an controller family can be specified:
#
#               obtain_github.sh [f0|f1|f3|f4|l1|l4|g0|g4]
#
#           If no argument is given, all repositories are downloaded.
#
#           Headers/Sources/Licenses of the HAL library are populated into the
#           current directory.
#
# \author   Maximilian Seesslen <development@seesslen.net>
#
#------------------------------------------------------------------------------


set -e -u

OPWD="$PWD"
ORGPWD="$PWD"
INCPATH="../include/stm"
SRCPATH="../src"
DOCPATH="./doc"
MCU_REV="f4"
base_url="https://github.com/STMicroelectronics"
SCRIPTDIR=$( dirname "${BASH_SOURCE[0]}" )

# -t: retries; -T: timeout for everything (read, connect, ...)
# 5 retries where to less for large images on bad infrastructure
WGETFLAGS="-t15 -T15"

# Don't flood /tmp
# TEMP=$(mktemp -d)
TEMP=$HOME/.cache/HALWrapper

HAL_ARCHIVE_PATH="${HAL_ARCHIVE_PATH:=}"
if [ -z "${HAL_ARCHIVE_PATH}" ]; then
	HAL_ARCHIVE_PATH="${TEMP}"
fi

[ -z "$HAL_ARCHIVE_PATH" ] && ( echo "could not get temp directory '$HAL_ARCHIVE_PATH'"; exit 22 )
mkdir -p $HAL_ARCHIVE_PATH

[ ! -d "$HAL_ARCHIVE_PATH" ] && ( echo "could not get temp directory '$HAL_ARCHIVE_PATH'"; exit 22 )

REVISION_F0=v1.11.5
REVISION_F1=v1.8.6
REVISION_F3=v1.11.5
REVISION_F4=v1.27.1

REVISION_L0=v1.12.3
REVISION_L1=v1.10.5
REVISION_L4=v1.18.1

REVISION_G0=v1.6.2
REVISION_G4=v1.6.1

init()
{
   cd "$OPWD"

   INCPATH="./include/${MCU_REV}/stm"
   SRCPATH="./src/${MCU_REV}"

   mkdir -p ${HAL_ARCHIVE_PATH} && cd ${HAL_ARCHIVE_PATH}
}


shovelFiles()
{
   cd $OPWD
	rm -rf $INCPATH $SRCPATH $DOCPATH/HAL $DOCPATH/CMSIS
	mkdir -p $SRCPATH $INCPATH $DOCPATH/HAL $DOCPATH/CMSIS

	chmod 755 $SRCPATH $INCPATH $DOCPATH/HAL $DOCPATH/CMSIS

	echo "### Target Pathes: $PWD; -> $SRCPATH $INCPATH $DOCPATH/HAL $DOCPATH/CMSIS"

   cp ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Src/*.c $SRCPATH
   cp ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Inc/*.h $INCPATH
	cp ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Release_Notes.html $DOCPATH/HAL
	if [ -d "${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/_htmresc" ]; then
		cp -r ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/_htmresc $DOCPATH/HAL
	else
		cp -r ${sourcePath}/_htmresc $DOCPATH/HAL
	fi
   
   if [ -e "${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/LICENSE.md" ]; then
      cp -r ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/LICENSE.md $DOCPATH/HAL
   else
      cp -r ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/License.md $DOCPATH/HAL/LICENSE.md
   fi
   
   # HAL license file
	if [ -e "${sourcePath}/License.md" ]; then
       cp ${sourcePath}/License.md $DOCPATH/LICENSE_HAL.md
	else
       cp ${sourcePath}/LICENSE.md $DOCPATH/LICENSE_HAL.md
	fi

   # Own license file
   cp $SCRIPTDIR/../LICENSE.md $DOCPATH

	if [ -e "${sourcePath}/Drivers/CMSIS/LICENSE.txt" ]; then
		cp ${sourcePath}/Drivers/CMSIS/LICENSE.txt $DOCPATH/CMSIS
	else
		cp ${sourcePath}/Drivers/CMSIS/Lib/license.txt $DOCPATH/CMSIS
	fi

	if [ -e "${sourcePath}/Drivers/CMSIS/README.md" ]; then
		cp ${sourcePath}/Drivers/CMSIS/README.md $DOCPATH/CMSIS
	else
		cp ${sourcePath}/README.md $DOCPATH/CMSIS
	fi

   if [ -d "${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Inc/Legacy" ]; then
      cp -R ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Inc/Legacy $INCPATH
   fi

   if [ -d "${sourcePath}/Drivers/CMSIS/Device/ST/STM32${MCU_REV^^}xx/Include" ]; then
      cp ${sourcePath}/Drivers/CMSIS/Device/ST/STM32${MCU_REV^^}xx/Include/*.h $INCPATH
   fi
   if [ -d "${sourcePath}/Drivers/CMSIS/Include" ]; then
      cp ${sourcePath}/Drivers/CMSIS/Include/*.h $INCPATH
   fi

   BOARD_NAME="BOARD_${MCU_REV^^}"
   PROJECT_NAME="PROJECT_${MCU_REV^^}"
   # cp ${sourcePath}/Projects/${!PROJECT_NAME}/Templates/Inc/stm32${MCU_REV}xx_hal_conf.h $INCPATH
   cp $INCPATH/stm32${MCU_REV}xx_hal_conf_template.h $INCPATH/stm32${MCU_REV}xx_hal_conf.h

      cp ${sourcePath}/Drivers/CMSIS/Device/ST/STM32${MCU_REV^^}xx/Source/Templates/gcc/startup_stm32*.s \
               $SRCPATH
      cp ${sourcePath}/Drivers/CMSIS/Device/ST/STM32${MCU_REV^^}xx/Source/Templates/system_stm32${MCU_REV}xx.c \
                        $SRCPATH
}


# Creates GIT repository and applies patches
gitInitPart()
{
   gitSourcePath="$1"
   gitPatchPath="$2"

   mkdir -p  "${gitPatchPath}"
   cd "$OPWD"
   cd "$gitSourcePath"
    if [ ! -d ".git" ]; then
       git init > /dev/null
       git add * > /dev/null
       git commit -m "initial commit"
       git checkout -b my
    else
	echo "git repository already set up."

    fi

   if [ ! -e ".patched" ]; then
      echo "Checking for local patches"
      for pfile in $(ls ${gitPatchPath}); do
          echo "Applying $pfile"
          git am --keep-cr < ${gitPatchPath}/$pfile
      done
      touch ".patched"
   fi
   cd "$OPWD"
}


# Initialize new git repositories for patches in the output
gitInit()
{
   gitInitPart "$SRCPATH" "$OPWD/patches/${MCU_REV}/src"
   gitInitPart "$INCPATH" "$OPWD/patches/${MCU_REV}/include"
}


# Receive a sepecific repository. A given tag is checked out.
# Variable sourcePath is set
receiveRepo()
{
   repo=$1
   bn=$(basename $repo)
   subpath=stm32${MCU_REV}/$bn
   # -${!PROJECT_REVISION}
   mkdir -p $(dirname $subpath)
   [ -e "$subpath" ] || git clone $repo $subpath
   pushd $subpath
   git fetch --all
   TAG=$(git describe $(git rev-list --tags --max-count=1))
   if [ "$TAG" != "${!PROJECT_REVISION}" ]; then
      echo "Warning: Newer tag available for ${MCU_REV}: $TAG" >&2
   fi
   git checkout ${!PROJECT_REVISION}
   git submodule update --init --recursive
   popd
   sourcePath="${HAL_ARCHIVE_PATH}/${subpath}"
}


# Receive the repo for current ${MCU_REV}
receive()
{
   optional=no
   cd $TEMP
   PROJECT_REVISION="REVISION_${MCU_REV^^}"

   receiveRepo "${base_url}/STM32Cube${MCU_REV^^}"
}


# Generate text files with a list of al HAL and LL source files and headers.
# This is needed in the CMakeLists.txt files to avoid manual listing the files
# for each MCU family.
generateList()
{
   find ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Src \
      -maxdepth 1 \
      -type f \
      -name "stm32*_hal*.c" \
      ! -name "*_template.c" \
      -printf "%P\n" \
      >  ${SCRIPTDIR}/../data/stm32${MCU_REV}_hal.list

   find ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Src \
      -maxdepth 1 \
      -type f -name "stm32*_ll*.c" -printf "%P\n" \
      >>  ${SCRIPTDIR}/../data/stm32${MCU_REV}_hal.list

   find ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Inc \
      -maxdepth 1 \
      -type f -name "stm32*_hal*.h" -printf "%P\n" \
      >  ${SCRIPTDIR}/../data/stm32${MCU_REV}_hal_header.list

   find ${sourcePath}/Drivers/STM32${MCU_REV^^}xx_HAL_Driver/Inc \
      -maxdepth 1 \
      -type f -name "stm32*_ll*.h" -printf "%P\n" \
      >>  ${SCRIPTDIR}/../data/stm32${MCU_REV}_hal_header.list

   DATA="${SCRIPTDIR}/../data"
   env LC_ALL=C sort -n ${DATA}/stm32${MCU_REV}_hal.list > ${DATA}/stm32${MCU_REV}_hal.list.sort
   mv ${DATA}/stm32${MCU_REV}_hal.list.sort ${DATA}/stm32${MCU_REV}_hal.list
   
   env LC_ALL=C sort -n ${DATA}/stm32${MCU_REV}_hal_header.list > ${DATA}/stm32${MCU_REV}_hal_header.list.sort
   mv ${DATA}/stm32${MCU_REV}_hal_header.list.sort ${DATA}/stm32${MCU_REV}_hal_header.list

   #find ${sourcePath}/Drivers/CMSIS/Include \
   #   -maxdepth 1 \
   #   -type f -name "*.h" -printf "%P\n" \
   #   >>  ${SCRIPTDIR}/../data/stm32${MCU_REV}_header.list
}


# Do all jobs for a single MCU-Revision
doAllForMcu()
{
   # An buildserver could start several build jobs in parallel. But the
   # obtaining processes should be serialized.
   (
      flock -x 200

      init
      receive
      shovelFiles
      generateList

      gitInit
   ) 200>${HAL_ARCHIVE_PATH}/${MCU_REV}.lock
}


if [ "$#" -gt "0" ]; then
    MCU_REVS="$@"
else
    MCU_REVS="f0 f1 f3 f4 l1 l4 g0 g4"
fi

for MCU_REV in $MCU_REVS; do
    doAllForMcu
done

echo "[$0] fin."


#---fin------------------------------------------------------------------------
