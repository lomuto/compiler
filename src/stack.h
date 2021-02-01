#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 101

typedef void* STACK_t;

STACK_t STACK[STACK_SIZE];
STACK_t* ptr = STACK - 1;

bool is_empty() {
	return ptr == STACK - 1 ? true : false;
}

bool is_full() {
	return ptr == STACK + STACK_SIZE - 1 ? true : false;
}

void push(STACK_t n) {
	if (is_full()) {
		printf("STACK OVERFLOW\n");
		exit(EXIT_FAILURE);
	}
	else
		*(++ptr) = n;
}

STACK_t pop() {
	if (is_empty()) {
		printf("STACK UNDERFLOW\n");
		exit(EXIT_FAILURE);
	}
	else
		return *ptr--;
}

void clear_STACK() {
	for (;!is_empty();)
		*ptr-- = NULL;
}

STACK_t peek() {
	if(is_empty())
		return NULL;
	else
		return *ptr;
}