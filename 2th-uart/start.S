#define WTCON 0x53000000
#define INTMSK 0x4a000008

.text
.global _start
_start:
	//����SVCģʽ
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr_c, r0

	//�رտ��Ź�
	ldr r0, =WTCON
	mov r1, #0x0                     
	str r1, [r0]

	//�����ж�
	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]

	//����ջ
	ldr sp, =4096

	//����ʱ��
	bl clock_init

	//����mainִ��
	bl main

halt_loop:
	b halt_loop
