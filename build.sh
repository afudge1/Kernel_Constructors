#/bin/bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make
qemu-system-i386 -hda ./bin/os.bin

#qemu-system-x86_64 -drive format=raw,file=bin/os.bin