.section .data
	a:.int 3
	b:.int 4

.global main

	main:
		movl (a), %eax
		add (b), %eax
		ret
