	.data
reci:	.word 1,2,3,4,5
char:	.char 'A',1+2-3,drugi+24
hptr: 	.word 0 @ ar ara ar a a
tptr: 	.word 0 // kometar a a 
buffer: .skip 512
align1:	.align
align2:	.align 64
drugi:	.skip 55
	.extern end
a:	.long (hptr-tptr+4)<<2
	.extern printf,d
	.text.prvi
start: 	sub r1,r1
	.warning WARNING
	.print "fdsf"
	add r1,1<<4
	sub r2,r2
	add r2, buffer
	sub r3,r3
	//call r3, printf
e:	.long e
end:	.long d
	.end

