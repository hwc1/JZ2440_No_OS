#define CLKDIVN		(*(volatile unsigned long *)0x4c000014)
#define LOCKTIME	(*(volatile unsigned long *)0x4c000000)
#define MPLLCON		(*(volatile unsigned long *)0x4c000004)
#define UPLLCON		(*(volatile unsigned long *)0x4c000008)

#define MEM_BASE	0x48000000

void clock_init(void)
{
	CLKDIVN = 0x05;
	LOCKTIME = 0xFFFFFFFF;
	MPLLCON = 0x0007f021;
	UPLLCON = 0x00038022;
}

void init_sdram(void)
{
	volatile unsigned long *p = (volatile unsigned long *)MEM_BASE;

	*(p) = 0x22011110;
	*(p + 1) = 0x00000700;
	*(p + 2) = 0x00000700;
	*(p + 3) = 0x00000700;
	*(p + 4) = 0x00000700;
	*(p + 5) = 0x00000700;
	*(p + 6) = 0x00000700;
	*(p + 7) = 0x00018005;
	*(p + 8) = 0x00018005;
	*(p + 9) = 0x008C04F4;
	*(p + 10) = 0x000000B1;
	*(p + 11) = 0x00000030;
	*(p + 12) = 0x00000030;
}

void copy_to_sdram(void)
{
	int i = 0;

	unsigned char *src = (unsigned char *)0;
	unsigned char *dst = (unsigned char *)0x30000000;

	for(i = 0; i < 4096; i++)
	{
		*(dst + i) = *(src + i);
	}
}

