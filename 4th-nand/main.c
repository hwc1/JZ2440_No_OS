#define GPFCON	(*(volatile unsigned long *)(0x56000050))
#define GPFDAT	(*(volatile unsigned long *)(0x56000054))

#define GPF4_MSK (0x3 << 8)
#define GPF5_MSK (0x3 << 10)
#define GPF6_MSK (0x3 << 12)

#define GPF4_OUT (0x1 << 8)
#define GPF5_OUT (0x1 << 10)
#define GPF6_OUT (0x1 << 12)

int main(void)
{
	int i = 0;
	unsigned char cnt = 0x10;
	unsigned char buff[20];
	unsigned int addr = (unsigned int)buff;

	GPFCON &= ~(GPF4_MSK | GPF5_MSK | GPF6_MSK);
	GPFCON |= (GPF4_OUT | GPF5_OUT | GPF6_OUT);

	uart_putc(addr & 0xff);
	uart_putc((addr >> 8) & 0xff);
	uart_putc((addr >> 16) & 0xff);
	uart_putc((addr >> 24) & 0xff);

	while(1)
	{
		cnt = uart_getc();
		uart_putc(cnt);
	}

	return 0;
}

