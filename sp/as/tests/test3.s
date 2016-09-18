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
start: 	sub-gt r1,r1
        add r1, 5
        add r2, 7
        mul r2, r1
	.warning WARNING
	.print "fdsf"
	add r1,1<<4
	sub r2,r3
	add r2, buffer
	sub r3,r3
	ldr r10,r10,0,0
        mul r10,r10
	str r11,r10,0,0
	ldr r12,r11,0,0
	call r3, printf
e:	ldcl r7, 1
	ldch r7, 1
	mov r8,r7
	shl r9,r8,2
end:	.long d
	.end

