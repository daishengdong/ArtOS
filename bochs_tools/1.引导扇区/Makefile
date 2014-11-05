TARGET	= boot.bin

default:
	make run

boot.bin: boot.asm Makefile
	# nasm boot.asm -o boot.bin
	nasm $< -o $@ 

bin:
	make boot.bin

install:
	make bin
	dd if=boot.bin of=a.img bs=512 count=1 conv=notrunc

clean:
	rm -f $(TARGET)

all: clean run

run:
	make install
	bochs -f bochsrc
