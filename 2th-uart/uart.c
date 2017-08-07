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

void init_uart(void)
{
	//设置端口
	GPHCON &= ~(GPH3_msk | GPH2_msk);
	GPHCON |= (GPH3_rx | GPH2_tx);
	GPHUP   = 0x0c;     
	
	//设置数据格式
	ULCON0 = 0x3;	
	
	//设置工作方式
	UCON0 = 0x5;
	UFCON0  = 0x00;     // 不使用FIFO
	UMCON0  = 0x00;     // 不使用流控	
	
	//设置波特率
	UBRDIV0 = 0x35;
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

