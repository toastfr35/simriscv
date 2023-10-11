R7CC=/d/SysGCC/risc-v/bin/riscv64-unknown-elf-gcc
R7LD=/d/SysGCC/risc-v/bin/riscv64-unknown-elf-ld
R7OBJDUMP=/d/SysGCC/risc-v/bin/riscv64-unknown-elf-objdump
R7OBJCOPY=/d/SysGCC/risc-v/bin/riscv64-unknown-elf-objcopy

test.bin : test.elf
	$(R7OBJCOPY) -O binary test.elf test.bin

test.elf : test.c boot.s
	$(R7CC) -c boot.s
	$(R7CC) -c test.c
	#$(R7OBJDUMP) -d test.o
	$(R7CC) -o test.elf -nostdlib -T linker_script.ld boot.o test.o
	$(R7OBJDUMP) -d test.elf > test.asm

clean:
	rm -f test.elf test.bin test.asm *.o
