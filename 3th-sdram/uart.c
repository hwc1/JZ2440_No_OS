#define GPHCON		(*(volatile unsigned long *)0x56000070)
#define GPHUP		(*(volatile unsigned long *)0x56000078)
#define ULCON0		(*(volatile unsigned long *)0x50000000)
#define UCON0		(*(volatile unsigned long *)0x50000004)
#define UFCON0		(*(volatile unsigned long *)0x50000008)
#define UMCON0		(*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0	(*(volatile unsigned long *)0x50000010)
#define UTXH0		(*(volatile unsigned char *)0x50000020)
#define URXH0		(*(volatile unsigned char *)0x50000024)
#define UBRDIV0		(*(volatile unsigned long *)0x50000028)

#define GPH3_msk	(3 << (2*3))
#define GPH2_msk	(3 << (2*2))

#define GPH3_rx		(2 << (2*3))
#define GPH2_tx		(2 << (2*2))

#define TXD0READY	(1<<2)
#define RXD0READY	(1)

#define PCLK					50000000    // init.c中的clock_init函数设置PCLK为50MHz
#define UART_CLK			PCLK        //  UART0的时钟源设为PCLK
#define UART_BAUD_RATE		115200      // 波特率
#define UART_BRD			((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

void init_uart(void)
{
	GPHCON  |= 0xa0;    // GPH2,GPH3用作TXD0,RXD0
	GPHUP   = 0x0c;     // GPH2,GPH3内部上拉

	ULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
	UCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
	UFCON0  = 0x00;     // 不使用FIFO
	UMCON0  = 0x00;     // 不使用流控
	UBRDIV0 = UART_BRD; // 波特率为115200
}

void uart_putc(unsigned char val)
{
	while (!(UTRSTAT0 & TXD0READY));

	UTXH0 = val;	
}

unsigned char uart_getc(void)
{
	unsigned char val = 0;

	while (!(UTRSTAT0 & RXD0READY));

	val = URXH0;

	return val;
}

