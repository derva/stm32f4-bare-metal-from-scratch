.syntax unified
.cpu cortex-m4
.thumb

.global default_handler
.global reset_handler

.section .isr_vector, "a"
.word _estack
.word reset_handler
.word default_handler @nmi


.section .text
.thumb_func
default_handler:
	b default_handler

.thumb_func
reset_handler:
	ldr r0, =_sidata
	ldr r1, =_sdata
	ldr r2, =_edata
copy_data:
	cmp r1, r2
	bge done_data
	ldr r3, [r0]
	str r3, [r1]
	adds r1, r1, #4
	adds r0, r0, #4	
	b copy_data
done_data:
	ldr r0, =_sbss
	ldr r1, =_ebss
	mov r2, #0
zero_bss:
	cmp r0, r1
	bge done_null
	str r2, [r0]	
	adds r0, r0, #4
	b zero_bss
done_null:
	bl main
loop:
	b loop




