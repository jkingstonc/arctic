clear

set SOURCES=./src
set BUILD=./build

set CCOMPILER=g++
set CCOMPILER=wsl $WSLENV/x86_64-elf-gcc
set LINKER=wsl $WSLENV/x86_64-elf-ld
set CFLAGS=-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions

nasm -f elf32 %SOURCES%/kernel/cpu/GDT.asm -o %BUILD%/GDTasm.o
nasm -f elf32 %SOURCES%/kernel/cpu/IDT.asm -o %BUILD%/IDTasm.o
nasm -f elf32 %SOURCES%/kernel/cpu/CPU.asm -o %BUILD%/CPUasm.o
nasm -f elf32 %SOURCES%/kernel/memory/Paging.asm -o %BUILD%/Pagingasm.o
nasm -f elf32 %SOURCES%/kernel/memory/Memory.asm -o %BUILD%/Memoryasm.o
nasm -f elf32 %SOURCES%/kernel/kernel.asm -o %BUILD%/kasm.o

%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/Kernel.cpp -o %BUILD%/Kernel.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/io/KPrintf.cpp -o %BUILD%/KPrintf.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/shell/Shell.cpp -o %BUILD%/Shell.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/memory/Memory.cpp -o %BUILD%/Memory.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/cpu/Interrupt.cpp -o %BUILD%/Interrupt.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/cpu/IDT.cpp -o %BUILD%/IDT.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/cpu/GDT.cpp -o %BUILD%/GDT.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/io/Port.cpp -o %BUILD%/Port.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/cpu/CPU.cpp -o %BUILD%/CPU.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/memory/Paging.cpp -o %BUILD%/Paging.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/dev/Keyboard.cpp -o %BUILD%/Keyboard.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/dev/Character.cpp -o %BUILD%/Character.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/dev/Device.cpp -o %BUILD%/Device.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/dev/Timer.cpp -o %BUILD%/Timer.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/driver/Driver.cpp -o %BUILD%/Driver.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/driver/PS2Keyboard.cpp -o %BUILD%/PS2Keyboard.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/driver/VGAGraphics.cpp -o %BUILD%/VGAGraphics.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/Panic.cpp -o %BUILD%/Panic.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/dev/Video.cpp -o %BUILD%/Video.o
%CCOMPILER% %CFLAGS% -c %SOURCES%/kernel/memory/KMalloc.cpp -o %BUILD%/KMalloc.o

%LINKER% -m elf_i386 -T %SOURCES%/link.ld -o %BUILD%/Kernel-0 ^
    %BUILD%/kasm.o ^
    %BUILD%/Kernel.o ^
    %BUILD%/KPrintf.o ^
    %BUILD%/Shell.o ^
    %BUILD%/Memory.o ^
    %BUILD%/Port.o ^
    %BUILD%/Interrupt.o ^
    %BUILD%/IDT.o ^
    %BUILD%/GDT.o ^
    %BUILD%/CPU.o ^
    %BUILD%/Paging.o ^
    %BUILD%/Keyboard.o ^
    %BUILD%/Device.o ^
    %BUILD%/Character.o ^
    %BUILD%/Timer.o ^
    %BUILD%/Driver.o ^
    %BUILD%/KMalloc.o ^
    %BUILD%/PS2Keyboard.o ^
    %BUILD%/VGAGraphics.o ^
    %BUILD%/Panic.o ^
    %BUILD%/Video.o ^
    %BUILD%/GDTasm.o ^
    %BUILD%/IDTasm.o ^
    %BUILD%/CPUasm.o ^
    %BUILD%/Memoryasm.o ^
    %BUILD%/Pagingasm.o

objcopy -O elf32-i386 %BUILD%/Kernel-0 %BUILD%/Kernel-0.elf
qemu-system-i386 -kernel ./build/Kernel-0

read