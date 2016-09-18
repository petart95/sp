.set inAdd,0x1000
.set outAdd,0x2000

// read from input to r1
.text.read
read:	sub r2,r2
	add r2,inAdd
	in r1,r2
	rts

// write to output from r1
.text.write
write:	sub r2,r2
	add r2,outAdd
	out r1,r2	
	rts
