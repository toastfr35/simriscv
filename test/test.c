const int fff[64]={42,43,44,45,46,47,48,50};
int ggg[64]={42,43,44,45,46,47,48,50};
int hhh[64];

void foo(float v) 
{
	v = v / 100.0;
}


void main() 
{
	asm ("addi	a0, zero, 1");
	foo(1.0);
	asm ("addi	a1, a1, 0x20");
}