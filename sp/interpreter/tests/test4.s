.data.itabel
	.long .text.main
	.long .text.intr
	.long 
	.long

.extern read, write

.text.main
	call read
	mov r3,r1
	call read
	add r1,r3
	call write

.text.intr
	add r15,0x2000
	add r7,65
	out r7,r9
	iret
