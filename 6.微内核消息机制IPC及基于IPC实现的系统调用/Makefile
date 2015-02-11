# Makefile for ArtOS

# Entry point of ArtOS
# It must have the same value with 'KernelEntryPointPhyAddr' in load.inc
ENTRYPOINT	= 0x30400

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	= 0x400

# Programs, flags, etc.
ASM			= nasm
DASM		= objdump
CC			= gcc
LD			= ld
ASMBFLAGS	= -I boot/include/
ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include/ -c -fno-builtin -Wall
# CFLAGS	= -I include/ -c -fno-builtin -fno-stack-protector -fpack-struct -Wall
LDFLAGS		= -Ttext $(ENTRYPOINT) -Map krnl.map
DASMFLAGS	= -D

# This program
ARTOSBOOT	= boot/boot.bin boot/loader.bin
ARTOSKERNEL	= kernel.bin
OBJS		= kernel/kernel.o kernel/syscall.o kernel/start.o kernel/main.o \
			  kernel/clock.o kernel/keyboard.o kernel/tty.o kernel/console.o \
			  kernel/i8259.o kernel/global.o kernel/protect.o kernel/proc.o \
			  kernel/systask.o kernel/printf.o kernel/vsprintf.o \
			  lib/klib.o lib/kliba.o lib/string.o lib/misc.o
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
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/main.o: kernel/main.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/clock.o: kernel/clock.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/keyboard.o: kernel/keyboard.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h include/keyboard.h include/keymap.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/tty.o: kernel/tty.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h include/keyboard.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/console.o: kernel/console.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h include/keyboard.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/i8259.o: kernel/i8259.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/global.o: kernel/global.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o: kernel/protect.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/proc.o: kernel/proc.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/printf.o: kernel/printf.c include/type.h include/const.h \
 include/protect.h include/string.h include/proc.h include/tty.h \
 include/console.h include/global.h include/proto.h include/keyboard.h	
	$(CC) $(CFLAGS) -o $@ $<

kernel/vsprintf.o: kernel/vsprintf.c include/type.h include/const.h \
 include/protect.h include/string.h include/proc.h include/tty.h \
 include/console.h include/global.h include/keyboard.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/systask.o : kernel/systask.c include/type.h include/const.h \
 include/protect.h include/string.h include/proc.h include/tty.h \
 include/console.h include/global.h include/proto.h include/keyboard.h
	$(CC) $(CFLAGS) -o $@ $<

lib/klib.o: lib/klib.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

lib/misc.o: lib/misc.c include/type.h include/const.h include/protect.h \
 include/string.h include/proc.h include/tty.h include/console.h \
 include/global.h include/proto.h include/keyboard.h
	$(CC) $(CFLAGS) -o $@ $<

lib/kliba.o: lib/kliba.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/string.o: lib/string.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<
