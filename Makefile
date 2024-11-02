FILES = ./build/libc/string.o ./build/kernel.asm.o ./build/kernel/syscall_handler.o ./build/kernel.o ./build/terminal.o ./build/libc/syscall.o 
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >> ./bin/os.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./src/kernel/kernel.asm
	nasm -f elf -g ./src/kernel/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o: ./src/kernel/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel/kernel.c -o ./build/kernel.o

./build/terminal.o: ./src/terminal/terminal.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/terminal/terminal.c -o ./build/terminal.o

./build/libc/syscall.o: ./src/libc/syscall.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/libc/syscall.c -o ./build/syscall.o

#./build/terminal/vga_text_graphics.o: ./src/terminal/vga_text_graphics.c
#	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/terminal/vga_text_graphics.c -o ./build/vga_text_graphics.o

./build/kernel/syscall_handler.o: ./src/kernel/syscall_handler.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel/syscall_handler.c -o ./build/syscall_handler.o

./build/libc/string.o: ./src/libc/string.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/libc/string.c -o ./build/string.o

