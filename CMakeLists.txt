cmake_minimum_required(VERSION 3.10)

project(arctic)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_CXX_FLAGS_DEBUG "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
set(CMAKE_CXX_FLAGS_RELEASE "-m32 -ffreestanding -nostdlib -nostdinc -lgcc")
