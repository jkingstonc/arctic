
SOURCES=./src
BUILD=./build
CFLAGS="-m32 -ffreestanding -nostdlib -nostdinc -lgcc"

nasm -f elf32  $SOURCES/kernel.asm -o $BUILD/kasm.o
gcc $CFLAGS -c $SOURCES/kernel.cpp -o $BUILD/kernel.o
gcc $CFLAGS -c $SOURCES/kernel/kprintf.cpp -o $BUILD/kprintf.o

ld -m elf_i386 -T $SOURCES/link.ld -o $BUILD/kernel-0 $BUILD/kasm.o $BUILD/kernel.o $BUILD/kprintf.o
objcopy -O elf32-i386 $BUILD/kernel-0 $BUILD/kernel-0.elf
qemu-system-i386 -kernel ./build/kernel-0