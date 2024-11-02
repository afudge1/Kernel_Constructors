export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="PREFIX/bin:$PATH"
make
qemu-system-i386 -hda ./bin/os.bin
