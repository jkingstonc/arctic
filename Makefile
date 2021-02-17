CXXFLAGS=-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions
LDFLAGS=-m elf_i386 -T src/link.ld
ASMFLAGS=-f elf32
ASFLAGS=-felf
SUBDIRS:= $(wildcard */)
SOURCES := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp */*/*/*/*/*.cpp)
ASMSOURCES := $(wildcard *.asm */*.asm */*/*.asm */*/*/*.asm */*/*/*/*.asm */*/*/*/*/*.asm)
OUTPUT=./build
BINARY=build/Arctic-0
ASM=nasm
CC=/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc
LINKER=/usr/local/x86_64elfgcc/bin/x86_64-elf-ld
OBJECTS:=$(patsubst %.cpp, %.o, $(SOURCES))
ASMOBJECTS:=$(patsubst %.asm, %.o, $(ASMSOURCES))
QEMU='/mnt/c/Program Files/qemu/qemu-system-i386.exe'


ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	OS := Windows
else
	OS := $(shell uname)  # same as "uname -s"
endif

.PHONY: all

all: $(OBJECTS) $(ASMOBJECTS) $(BINARY)
	echo $(OS)

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ 

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BINARY): $(OBJECTS) $(ASMOBJECTS)
	echo "creating binary..."
	$(LINKER) $(LDFLAGS) -o $@ $(OBJECTS) $(ASMOBJECTS)

clean:
	rm -f $(OUTPUT)/Arctic-0
	rm -f $(OUTPUT)/boot/Arctic-0
	rm -f $(OUTPUT)/boot/Arctic-0.iso
	rm -f -r $(OUTPUT)/*.o
	find . -name "*.o" -type f -delete

run-graphics: all
	cp ./src/grub.cfg ./build/boot/grub
	objcopy -O elf32-i386 ./build/Arctic-0 ./build/boot/Arctic-0
	grub-mkrescue build -o ./build/boot/Arctic-0.iso
	$(QEMU) -cdrom ./build/boot/Arctic-0.iso -serial stdio

run-text: all
	cp ./src/grub.cfg ./build/boot/grub
	objcopy -O elf32-i386 ./build/Arctic-0 ./build/boot/Arctic-0
	$(QEMU) -kernel ./build/boot/Arctic-0 -serial stdio

listsources:
	dir *.cpp /S /B