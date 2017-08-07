#define WTCON 0x53000000

.text
.global _start
_start:
	//关闭看门狗
	ldr r0, =WTCON
	mov r1, #0x0                     
	str r1, [r0]

	//设置栈
	ldr sp, =1024*4         

	//跳到main执行
	bl main

halt_loop:
	b halt_loop

