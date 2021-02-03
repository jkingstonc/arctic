

BUILDDIR=./build
CC="wsl $WSLENV/x86_64-elf-gcc"
CFLAGS=-m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions


clean:
	rm -r $(BUILDDIR)