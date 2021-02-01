
SOURCES=./src
BUILD=./build

nasm -f elf64  $SOURCES/kernel.asm -o $BUILD/kasm.o
gcc -m64 -c $SOURCES/kernel.cpp -o $BUILD/kc.o -ffreestanding -nostdlib -nostdinc -lgcc

ld -T $SOURCES/link.ld -o $BUILD/kernel $BUILD/kasm.o $BUILD/kc.o
#objcopy -O elf32-i386 $BUILD/kernel $BUILD/kernel.elf
read