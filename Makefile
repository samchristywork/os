CFLAGS=-m32 -ffreestanding -fno-stack-protector -nostdlib -O2
ASFLAGS=-f elf32
LDFLAGS=-m elf_i386 -T linker.ld
OBJECTS=build/boot.o build/kernel.o

all: build/os.bin

build:
	mkdir -p build

build/boot.o: boot.asm | build
	nasm $(ASFLAGS) -o $@ $<

build/kernel.o: kernel.c | build
	gcc $(CFLAGS) -c -o $@ $<

build/os.bin: $(OBJECTS)
	ld $(LDFLAGS) -o $@ $(OBJECTS)

run: build/os.bin
	qemu-system-i386 -kernel build/os.bin -nographic

clean:
	rm -rf build
