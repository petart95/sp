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
	mov-eq-uf r4
	add-uf r13,1
    add-uf r13, start
	add-uf r13, nema
    add-lrt r7,r18
	and-eq-uf r0,r1
    and-eq-uf r0,sP
    and-eq-uf r0,psw
	add r0, r1,   ,   , r2
end:	stor r0
	.end
	add
error:	add
	add
	.end
