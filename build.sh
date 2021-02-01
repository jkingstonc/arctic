
SOURCES=./src
BUILD=./build
CCOMPILER=g++
LINKER=ld
CFLAGS="-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions"

clear

nasm -f elf32  $SOURCES/kernel.asm -o $BUILD/kasm.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/Kernel.cpp -o $BUILD/Kernel.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/KPrintf.cpp -o $BUILD/KPrintf.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/shell/Shell.cpp -o $BUILD/Shell.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/memory/Memory.cpp -o $BUILD/Memory.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/interrupt/Interrupt.cpp -o $BUILD/Interrupt.o

$LINKER -m elf_i386 -T $SOURCES/link.ld -o $BUILD/Kernel-0 \
    $BUILD/kasm.o \
    $BUILD/Kernel.o \
    $BUILD/KPrintf.o \
    $BUILD/Shell.o \
    $BUILD/Memory.o \
    $BUILD/Interrupt.o

objcopy -O elf32-i386 $BUILD/Kernel-0 $BUILD/Kernel-0.elf
qemu-system-i386 -kernel ./build/Kernel-0