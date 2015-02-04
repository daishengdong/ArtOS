# Makefile for ArtOS

# Entry point of ArtOS
# It must have the same value with 'KernelEntryPointPhyAddr' in load.inc!
ENTRYPOINT	= 0x30400

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	= 0x400

# Programs, flags, etc.
ASM			= nasm
DASM		= ndisasm
CC			= gcc
LD			= ld
ASMBFLAGS	= -I boot/include/
ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include/ -c -fno-builtin
LDFLAGS		= -s -Ttext $(ENTRYPOINT)
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This program
ARTOSBOOT	= boot/boot.bin boot/loader.bin
ARTOSKERNEL	= kernel.bin
OBJS		= kernel/kernel.o kernel/syscall.o kernel/start.o kernel/main.o kernel/clock.o \
			  kernel/i8259.o kernel/global.o kernel/protect.o kernel/proc.o \
			  lib/klib.o lib/kliba.o lib/string.o
DASMOUTPUT	= kernel.bin.asm

# All Phony Targets
.PHONY: everything final image clean realclean disasm all buildimg default

default: image
	bochs -f bochsrc

# Default starting position
everything: $(ARTOSBOOT) $(ARTOSKERNEL)

all: realclean everything

final: all clean
	
image: final buildimg

clean:
	rm -f $(OBJS)

realclean:
	rm -f $(OBJS) $(ARTOSBOOT) $(ARTOSKERNEL)

disasm:
	$(DASM) $(DASMFLAGS) $(ARTOSKERNEL) > $(DASMOUTPUT)

# We assume that "a.img" exists in current folder
buildimg:
	dd if=boot/boot.bin of=a.img bs=512 count=1 conv=notrunc
	sudo mount -o loop a.img /mnt/floppy
	sudo cp -fv boot/loader.bin /mnt/floppy
	sudo cp -fv kernel.bin /mnt/floppy
	sudo umount /mnt/floppy

boot/boot.bin: boot/boot.asm boot/include/load.inc boot/include/fat12hdr.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

boot/loader.bin: boot/loader.asm boot/include/load.inc \
				 boot/include/fat12hdr.inc boot/include/pm.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

$(ARTOSKERNEL): $(OBJS)
		$(LD) $(LDFLAGS) -o $(ARTOSKERNEL) $(OBJS)

kernel/kernel.o: kernel/kernel.asm include/sconst.inc
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/syscall.o: kernel/syscall.asm include/sconst.inc
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/start.o: kernel/start.c include/type.h include/const.h include/protect.h \
	include/proto.h include/string.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/main.o: kernel/main.c include/type.h include/const.h include/protect.h \
	include/proto.h include/string.h include/proc.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/clock.o: kernel/clock.c include/type.h include/const.h include/protect.h \
 include/proto.h include/string.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/i8259.o: kernel/i8259.c include/type.h include/const.h include/protect.h \
 include/proto.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/global.o: kernel/global.c include/type.h include/const.h include/protect.h \
	include/proto.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o: kernel/protect.c include/type.h include/const.h include/protect.h \
	include/proto.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/proc.o: kernel/proc.c include/type.h include/const.h include/protect.h \
 include/proto.h include/string.h include/proc.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

lib/klib.o: lib/klib.c include/type.h include/const.h include/protect.h \
 include/proto.h include/proc.h include/string.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

lib/kliba.o: lib/kliba.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/string.o: lib/string.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<
