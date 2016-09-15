.data.1
reci1:	.word 1,2,3,4,5
char1:	.char 'A',1+2-3,drugi1+24
hptr1: 	.word 0 @ ar ara ar a a
tptr1: 	.word 0 // kometar a a
buffer1: .skip 512
align11:	.align
align21:	.align 64
drugi1:	.skip 55
	.extern end1
d:	.long (hptr1-tptr1+4)<<2
	.extern printf1,d1
	.text.prvi1
printf: 	sub r1,r2
	.warning WARNING
printf1:	.print "fdsf"
d1:	add r1,1<<4
	sub r2,r3
	add r2, buffer1
	sub r3,r3
	call r3, printf1
e1:	.long e1
end1:	.long d1
	.end

