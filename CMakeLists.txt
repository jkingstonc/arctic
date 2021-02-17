cmake_minimum_required(VERSION 3.10)

project(arctic)

set(CMAKE_C_COMPILER   wsl $WSLENV/x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER wsl $WSLENV/x86_64-elf-gcc)
set(CMAKE_ASM_COMPILER nasm)


set(SOURCES src)
set(BUILD build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BUILD})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BUILD})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BUILD})

set(CMAKE_CXX_FLAGS_DEBUG "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_RELEASE "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_LINK_FLAGS "-m elf_i386 -T ${SOURCES}/link.ld -o ${BUILD}/Kernel-0 ")

set(KERNEL_BIN Kernel-0)

include_directories(
    ${SOURCES}/kernel
    ${SOURCES}/kernel/cpu
    ${SOURCES}/kernel/dev
    ${SOURCES}/kernel/driver
    ${SOURCES}/kernel/io
    ${SOURCES}/kernel/memory
    ${SOURCES}/kernel/shell
    ${SOURCES}/kernel/utils
)

set (ASM_SOURCES
    ${SOURCES}/kernel/Kernel.asm

    ${SOURCES}/kernel/cpu/CPU.asm
    ${SOURCES}/kernel/cpu/GDT.asm
    ${SOURCES}/kernel/cpu/IDT.asm

    ${SOURCES}/kernel/memory/Memory.asm
    ${SOURCES}/kernel/memory/Paging.asm
)

set(CXX_SOURCES
    ${SOURCES}/kernel/Kernel.cpp

    ${SOURCES}/kernel/cpu/CPU.cpp
    ${SOURCES}/kernel/cpu/GDT.cpp
    ${SOURCES}/kernel/cpu/IDT.cpp
    ${SOURCES}/kernel/cpu/Interrupt.cpp
    
    ${SOURCES}/kernel/dev/Block.cpp
    ${SOURCES}/kernel/dev/Character.cpp
    ${SOURCES}/kernel/dev/Keyboard.cpp
    ${SOURCES}/kernel/dev/Mouse.cpp
    ${SOURCES}/kernel/dev/Timer.cpp
    
    ${SOURCES}/kernel/driver/Driver.cpp
    ${SOURCES}/kernel/driver/PS2Keyboard.cpp
    ${SOURCES}/kernel/driver/VGAGraphics.cpp

    ${SOURCES}/kernel/io/KPrintf.cpp
    ${SOURCES}/kernel/io/Port.cpp
    
    ${SOURCES}/kernel/memory/Memory.cpp
    ${SOURCES}/kernel/memory/Paging.cpp

    ${SOURCES}/kernel/shell/Shell.cpp
    
    ${SOURCES}/kernel/utils/Bitmap.cpp
)

## Building the kernel binary
add_executable(${KERNEL_BIN} ${ASM_SOURCES} ${CXX_SOURCES})

# add the link command
set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS ${CMAKE_LINK_FLAGS})

add_custom_command(TARGET ${KERNEL_BIN} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD}
        COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BIN} ${BUILD})