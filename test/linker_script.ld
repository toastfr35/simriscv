/* Rapita Systems Ltd (c) 2020 */

__heap_size  = 0x1000;
__stack_size = 0x1000;

MEMORY
{
  ram      (rwx) : ORIGIN = 0x0, LENGTH = 0x100000 /* 1MB RAM */
}

ENTRY(_start)

SECTIONS
{

	/* SP,PC interrupt_vectors, interrupt_handlers */
	.boot : {
		boot.o(.init)
		boot.o(.vector_table)
		boot.o(.interrupt_handlers)
	} > ram

	/* Code */
	.text : {
		. = ALIGN (4);
		*(.text)
		*(.text.*)
	} > ram

	/* Constant variables */
	.rodata : {
		. = ALIGN (4);
		*(.rodata)
		*(.rodata.*)
	} > ram

	/* Statically-allocated variables that are declared and have been assigned a value */
	.data : {
		. = ALIGN (4);
		*(.data)
		*(.data.*)
	} > ram

	/* Statically-allocated variables that are declared but have not been assigned a value yet */
	.bss(NOLOAD) : {
		. = ALIGN (4);
		*(.bss)
		*(COMMON)
	} > ram

	.heap(NOLOAD) : {
		. = ALIGN(4);
		PROVIDE ( end = . );
		__heap_start = .;
		. = . + __heap_size;
		. = ALIGN(4);
		__heap_end = .;
	} >ram

	/* Use the rest for the stack with a minimum of __stack_size */
	rest = LENGTH(ram) - (. + __stack_size + 0x4);
	.stack : {
		. = ALIGN (4);
		_estack = .;
		. = . + __stack_size;
		. = . + rest;
		_sstack = .;
	} > ram

}
