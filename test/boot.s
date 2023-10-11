# (c) 2020-2021 Rapita Systems Ltd 

# Stack pointer points to end of 1MB RAM
#.long   _sstack

.section .text

.global _start
_start:
	la sp, _sstack
	call main
	nop
