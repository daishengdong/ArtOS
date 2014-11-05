##################################################
# Makefile
##################################################

SRC:=boot.asm
BIN:=$(subst .asm,.com,$(SRC))

.PHONY : everything

default:
	make run

install: $(BIN)
	sudo mount -o loop a.img /mnt/floppy/
	sudo cp $(BIN) /mnt/floppy/ -v
	sudo umount /mnt/floppy/

$(BIN) : $(SRC)
	nasm $< -o $@

clean:
	rm -f $(BIN)

all: clean run

run:
	make install
	bochs -f bochsrc
