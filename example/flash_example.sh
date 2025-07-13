#!/bin/bash

set -e -u

cd ..
S=$PWD
cd build

target=example/hello_world

killall openocd | echo  ignoring
openocd -f /usr/share/openocd/scripts/board/stm32f3discovery.cfg &

P=$!
sleep 1

cat << EOF > gdb_commands.txt
set arm abi AAPCS
target remote localhost:3333
monitor reset halt

#monitor fast_load_image $PWD/${target}.bin 0x20000000 bin
#monitor fast_load

monitor flash write_image erase $PWD/${target}.bin 0x08000000

monitor reset run
echo "Finished!"
quit
EOF

gdb-multiarch --command=gdb_commands.txt

kill $P


#--- fin ----------------------------------------------------------------------
