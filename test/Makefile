PREFIX=/d/SysGCC/risc-v/bin/riscv64-unknown-elf-

CC=$(PREFIX)gcc
LD=$(PREFIX)ld
OBJDUMP=$(PREFIX)objdump
OBJCOPY=$(PREFIX)objcopy

test.bin : test.elf
	$(OBJCOPY) -O binary test.elf test.bin

test.elf : test.c boot.s
	$(CC) -c boot.s
	$(CC) -c test.c
	$(CC) -o test.elf -nostdlib -T linker_script.ld boot.o test.o
	$(OBJDUMP) -d test.elf > test.asm

clean:
	rm -f test.elf test.bin test.asm *.o
