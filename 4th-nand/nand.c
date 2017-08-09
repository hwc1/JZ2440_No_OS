#define NFCONF	(*(volatile unsigned long*)0x4E000000)
#define NFCONT	(*(volatile unsigned long*)0x4E000004)
#define NFSTAT	(*(volatile unsigned char*)0x4E000020)
#define NFCMD	(*(volatile unsigned char*)0x4E000008)
#define NFADDR	(*(volatile unsigned char*)0x4E00000C)
#define NFDATA	(*(volatile unsigned char*)0x4E000010)

#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0

//select nand 
static void Nand_select_chip(void)
{
    NFCONT &= ~(1<<1);	
}

//disselect nand 
static void Nand_deselect_chip(void)
{
    NFCONT |= (1<<1);	
}

//wait nand ready
static void Nand_wait_idle(void)
{
	while (!(NFSTAT & 1));
}

//write command 
static void Nand_write_cmd(unsigned char cmd)
{
	NFCMD = cmd;
}

//send address
static void Nand_write_addr(unsigned char addr)
{
	NFADDR = addr;
}

//read data
static unsigned char Nand_read_data(void)
{
	return NFDATA;
}

//reset nand flash
static void Nand_reset(void)
{
	Nand_select_chip();
	Nand_write_cmd(0xff);  
	Nand_wait_idle();
	Nand_deselect_chip();
}

//init nand flash
void Nand_init(void)
{
	//set time 
	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);

	NFCONT = (1<<4)|(1<<1)|(1<<0);

	//reset nand
	Nand_reset();
}

//read Nand flash ID
void Nand_read_id(char *buff)
{
	int i = 0;

	//select nand 
	Nand_select_chip();

	//send command 0x90
	Nand_write_cmd(0x90);

	//send address 0x0
	Nand_write_addr(0x0);

	//read data£¬manufacturer code(ECh), and the device code and 3rd, 4th, 5th cycle ID respectively
	//0xec, 0xda, 0x10, 0x15, 0x44
	for(i = 0; i < 5; i++)
	{
		*(buff + i) = Nand_read_data();
	}
	
	//disselect
	Nand_deselect_chip();
}

void Nand_read(unsigned long addr, char *buff, int size)
{
	int i = 0;

	//select nand 
	Nand_select_chip();

	//send command 0x0
	Nand_write_cmd(0x0);

	//send address
	Nand_write_addr(addr & 0xff);
	Nand_write_addr((addr >> 8) & 0x0f);
	Nand_write_addr((addr >> 12) & 0xff);
	Nand_write_addr((addr >> 20) & 0xff);
	Nand_write_addr((addr >> 28) & 0x01);

	//send command 0x30
	Nand_write_cmd(0x30);

	Nand_wait_idle();

	//read data
	for(i = 0; i < size; i++)
	{
		*(buff + i) = NFDATA;
	}

	//disselect
	Nand_deselect_chip();

}

//Page read

#if 0
void Nand_read(unsigned long addr, char *buff, int size)
{
	int i = 0;
	int col = addr % 2048;

	//select nand 
	Nand_select_chip();

	while(i < size)
	{
		//send command 0x0
		Nand_write_cmd(0x0);

		//send address
		Nand_Send_addr(addr);

		//send command 0x30
		Nand_write_cmd(0x30);

		Nand_wait_idle();

		//read data
		for(; (col < 2048) && (i < size); col++)
		{
			*(buff + i) = NFDATA;
			i++;
			addr++;
		}

		col = 0;
	}

	//disselect
	Nand_deselect_chip();
}
#endif 

