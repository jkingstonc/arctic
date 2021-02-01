
SOURCES=./src
BUILD=./build

nasm -f elf32  $SOURCES/kernel.asm -o $BUILD/kasm.o
gcc -m32 -c $SOURCES/kernel.cpp -o $BUILD/kc.o -ffreestanding -nostdlib -nostdinc -lgcc

ld -m elf_i386 -T $SOURCES/link.ld -o $BUILD/kernel-0 $BUILD/kasm.o $BUILD/kc.o
objcopy -O elf32-i386 $BUILD/kernel-0 $BUILD/kernel-0.elf
qemu-system-i386 -kernel ./build/kernel-0