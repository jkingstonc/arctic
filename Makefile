OBJECTS=build/Kernel-0
CXXFLAGS=-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions
LDFLAGS= -m elf_i386 -T src/link.ld
ASFLAGS=-felf

all: $(SOURCES) link 

clean:
	rm build/*.o

link:
	ld $(LDFLAGS) -o kernel $(OBJECTS)

.s.o:
	nasm $(ASFLAGS) $< 