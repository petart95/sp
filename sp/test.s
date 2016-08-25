	.data
reci:	.word 1,2,3,4,5
char:	.char 1
head_ptr: 	.word 0 @ ar ara ar a a
tail_ptr: 	.word 0 // kometar a a 
buffer: 	.skip 512
align1:	.align
align2:	.align 64
drugi:		.skip 55
	.text
	.extern end
start: //komentar
	load r0
	mov-eq r4
	add-uf 1
    add-lrt
	and-eq-uf r0,r1
	add r0, r1,   ,   , r2
end:	stor r0
	.end
	add
error:	add
	add
	.end
