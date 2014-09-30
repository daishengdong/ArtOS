TARGET	= boot.bin a.img

default:
	make run

boot.bin: boot.asm Makefile
	# nasm boot.asm -o boot.bin
	nasm $< -o $@ 

image:
	make boot.bin

install:
	make image
	dd if=boot.bin of=a.img bs=512 count=1 conv=notrunc

clean:
	rm -f $(TARGET)

all: clean run

run:
	make install
	bochs -f bochsrc
