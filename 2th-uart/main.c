#define GPFCON    (*(volatile unsigned long *)(0x56000050))
#define GPFDAT    (*(volatile unsigned long *)(0x56000054))

#define GPF4_MSK (0b11 << 8)
#define GPF5_MSK (0b11 << 10)
#define GPF6_MSK (0b11 << 12)

#define GPF4_OUT (0b01 << 8)
#define GPF5_OUT (0b01 << 10)
#define GPF6_OUT (0b01 << 12)

void delay(void)
{
	int i = 0;

	for(i = 0; i < 30000; i++);
	for(i = 0; i < 30000; i++);
}

/*
 * GPF4 GPF5 GPF6
 */

int main(void)
{
	int i = 0;
	unsigned char cnt = 0x10;

	init_uart();

	uart_putc('H');
	uart_putc('e');
	uart_putc('l');
	uart_putc('l');
	uart_putc('o');
	uart_putc(0x12);
	uart_putc(0x34);
	uart_putc(0x56);
	uart_putc(0x78);

	//设置GPIO端口
	GPFCON &= ~(GPF4_MSK | GPF5_MSK | GPF6_MSK);
	GPFCON |= (GPF4_OUT | GPF5_OUT | GPF6_OUT);

	//进入死循环
	while(1)
	{
		cnt = uart_getc();
		uart_putc(cnt);
	}

	return 0;
}

