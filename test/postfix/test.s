.global main

main:
push $1
push $2

pop %rax
pop %rbx
imulq %rbx, %rax
push %rax

pop %rax
ret
