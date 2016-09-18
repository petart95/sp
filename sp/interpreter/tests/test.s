.data
inAdd:	.long 30
outAdd:	.long 35

.data.itabel
	.long .text.main
	.long .text.intr
	.long 
	.long

.extern read, write

.text.main
read:	sub r3,r3
	ldr r3,r1,0,inAdd
	ldr r3,r2,0,outAdd
	add r1,r2
write:	sub r2,r2
	add r2,outAdd
	out r1,r2

.text.intr
	add r15,0x2000
	add r7,65
	out r7,r9
	iret
