#define WTCON 0x53000000
#define INTMSK 0x4a000008

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

	//init uart
	bl init_uart

	mov r2, #0xab
	ldr r1, =0x30000000
	str r2, [r1]

	ldr r0, [r1]

	bl uart_putc

	//go to main
	bl main

halt_loop:
	b halt_loop

