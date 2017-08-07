#define CLKDIVN		(*(volatile unsigned long *)0x4c000014)
#define LOCKTIME	(*(volatile unsigned long *)0x4c000000)
#define MPLLCON		(*(volatile unsigned long *)0x4c000004)
#define UPLLCON		(*(volatile unsigned long *)0x4c000008)

void clock_init(void)
{
	CLKDIVN = 0x03;
	LOCKTIME = 0xffffffff;
	MPLLCON = 0x0007f021;
	UPLLCON = 0x00038022;
}

