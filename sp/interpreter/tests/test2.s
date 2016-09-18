.set inAdd,0x1000
.set outAdd,0x2000

.data.itabel
	.long .text.main
	.long .text.intr
	.long 
	.long

.extern read, write

.text.main
read:	sub r2,r2
	add r2,inAdd
	in r1,r2
write:	sub r2,r2
	add r2,outAdd
	out r1,r2

.text.intr
	add r15,0x2000
	add r7,65
	out r7,r9
	iret
