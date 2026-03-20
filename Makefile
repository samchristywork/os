CFLAGS=-m32 -ffreestanding -fno-stack-protector -nostdlib -O2
ASFLAGS=-f elf32
LDFLAGS=-m elf_i386 -T src/linker.ld
OBJECTS=build/boot.o build/kernel.o

all: build/os.bin

build:
	mkdir -p build

build/boot.o: src/boot.asm | build
	nasm $(ASFLAGS) -o $@ $<

build/kernel.o: src/kernel.c | build
	gcc $(CFLAGS) -c -o $@ $<

build/os.bin: $(OBJECTS)
	ld $(LDFLAGS) -o $@ $(OBJECTS)

build/fs.img: | build
	dd if=/dev/zero of=build/fs.img bs=512 count=2048 2>/dev/null

run: build/os.bin build/fs.img
	qemu-system-i386 -kernel build/os.bin \
	    -drive file=build/fs.img,format=raw,if=ide \
	    -nographic

clean:
	rm -rf build
