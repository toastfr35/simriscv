all : simriscv.exe test/test.bin

run: simriscv.exe test/test.bin
	./simriscv.exe test/test.bin

simriscv.exe : simriscv.c
	gcc $< -Iincludes -Llibs -lunicorn -lcapstone -o $@

clean:
	rm -f simriscv.exe
	$(MAKE) -C test clean 

test/test.bin : test/*.c test/*.s
	$(MAKE) -C test