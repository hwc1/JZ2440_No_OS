#define WTCON 0x53000000
#define INTMSK 0x4a000008
#define MEM_CTL_BASE    0x48000000

.text
.global _start
_start:
	//set cpu to svc mode
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr_c, r0

	//disable watchdog
	ldr r0, =WTCON
	mov r1, #0x0                     
	str r1, [r0]

	//mask all the interrupts 
	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]

	//set stack
	ldr sp, =4096

	//init clock
	bl clock_init

	//init sdram
	bl init_sdram
	bl copy_to_sdram

	//reset statk
	ldr sp, =0x34000000

	//init uart
	bl init_uart

	//go to main
	//bl main
	ldr pc, =main

halt_loop:
	b halt_loop

init_sdram:
	ldr r0, =MEM_CTL_BASE
	adr r1, sdram_config     
	add r3, r0, #(13*4)
1:
	ldr r2, [r1], #4
	str r2, [r0], #4
	cmp r0, r3
	bne 1b
	mov pc, lr

sdram_config:
	.long 0x22011110	 //BWSCON
	.long 0x00000700	 //BANKCON0
	.long 0x00000700	 //BANKCON1
	.long 0x00000700	 //BANKCON2
	.long 0x00000700	 //BANKCON3  
	.long 0x00000700	 //BANKCON4
	.long 0x00000700	 //BANKCON5
	.long 0x00018005	 //BANKCON6
	.long 0x00018005	 //BANKCON7
	.long 0x008C04F4	 // REFRESH
	.long 0x000000B1	 //BANKSIZE
	.long 0x00000030	 //MRSRB6
	.long 0x00000030	 //MRSRB7


