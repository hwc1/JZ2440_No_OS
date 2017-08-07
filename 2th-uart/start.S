#define WTCON 0x53000000
#define INTMSK 0x4a000008

.text
.global _start
_start:
	//设置SVC模式
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr_c, r0

	//关闭看门狗
	ldr r0, =WTCON
	mov r1, #0x0                     
	str r1, [r0]

	//屏蔽中断
	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]

	//设置栈
	ldr sp, =4096

	//设置时钟
	bl clock_init

	//跳到main执行
	bl main

halt_loop:
	b halt_loop

