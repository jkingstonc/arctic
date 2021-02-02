
SOURCES=./src
BUILD=./build
CCOMPILER=g++
LINKER=ld
CFLAGS="-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions"

clear

nasm -f elf32  $SOURCES/kernel/cpu/GDT.asm -o $BUILD/GDTasm.o
nasm -f elf32  $SOURCES/kernel/cpu/IDT.asm -o $BUILD/IDTasm.o
nasm -f elf32  $SOURCES/kernel/cpu/CPU.asm -o $BUILD/CPUasm.o
nasm -f elf32  $SOURCES/kernel.asm -o $BUILD/kasm.o

$CCOMPILER $CFLAGS -c $SOURCES/kernel/Kernel.cpp -o $BUILD/Kernel.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/KPrintf.cpp -o $BUILD/KPrintf.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/shell/Shell.cpp -o $BUILD/Shell.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/memory/Memory.cpp -o $BUILD/Memory.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/cpu/Interrupt.cpp -o $BUILD/Interrupt.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/cpu/GDT.cpp -o $BUILD/GDT.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/io/Port.cpp -o $BUILD/Port.o
$CCOMPILER $CFLAGS -c $SOURCES/kernel/cpu/CPU.cpp -o $BUILD/CPU.o

$LINKER -m elf_i386 -T $SOURCES/link.ld -o $BUILD/Kernel-0 \
    $BUILD/kasm.o \
    $BUILD/Kernel.o \
    $BUILD/KPrintf.o \
    $BUILD/Shell.o \
    $BUILD/Memory.o \
    $BUILD/Port.o \
    $BUILD/Interrupt.o \
    $BUILD/GDT.o \
    $BUILD/CPU.o \
    $BUILD/GDTasm.o \
    $BUILD/IDTasm.o \
    $BUILD/CPUasm.o

objcopy -O elf32-i386 $BUILD/Kernel-0 $BUILD/Kernel-0.elf
qemu-system-i386 -kernel ./build/Kernel-0