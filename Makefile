ASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

BUILD = build

BOOT = $(BUILD)/boot.bin
ENTRY = $(BUILD)/kernel_entry.o
KERNEL = $(BUILD)/kernel.bin
IMAGE = $(BUILD)/jtos.img

CFLAGS = -m32 -ffreestanding -fno-pie \
         -fno-stack-protector -fno-builtin \
         -Wall -Wextra -O0

LDFLAGS = -m elf_i386 -T linker.ld

.PHONY: all
all: $(IMAGE)

$(BUILD):
	mkdir -p $(BUILD)

$(BOOT): boot.asm | $(BUILD)
	$(ASM) -f bin $< -o $@

$(ENTRY): kernel_entry.asm | $(BUILD)
	$(ASM) -f elf32 $< -o $@

$(BUILD)/kernel.o: kernel.c kernel.h | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/char.o: char.c char.h | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(ENTRY) $(BUILD)/kernel.o $(BUILD)/char.o linker.ld
	$(LD) $(LDFLAGS) $(ENTRY) $(BUILD)/kernel.o $(BUILD)/char.o -o $@

$(IMAGE): $(BOOT) $(KERNEL)
	cat $(BOOT) $(KERNEL) > $(IMAGE)
	truncate -s 1440k $(IMAGE)

.PHONY: run
run: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE),if=floppy

.PHONY: debug
debug: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE),if=floppy \
		-no-reboot -no-shutdown -d int,cpu_reset -D $(BUILD)/qemu.log

.PHONY: clean
clean:
	rm -rf $(BUILD)

.PHONY: rebuild
rebuild: clean all

