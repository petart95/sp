.extern a,b
.global c,d

.text.prvideo
.char a,b
.long 8,c
.char 1,1
c:
.word b,2
d:
.skip 10
int 8
add r4,r6
sub r3,r7
.bss
mul r3,r5
lab:
div r8,r10
add-gt r3,20
.data
.char 4,4
l: cmp r5,r5
and r1,r2
or r4,r4
e: not r1,r1
test r1,r2
.text.drugideo
f: ldr r5,r1,6,3
str r4,r3,6,8
call r2,f
g:
call 32
in r4,R6
out R2,r2
.long 9,15
.align 5,4095,5
h:
mov r3,r14
shr r13,r5,23
shl r7,r6,b
ldch r3,h-g
ldcl r3,g-h
call h
.end
