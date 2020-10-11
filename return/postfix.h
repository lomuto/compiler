#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_EXP 101
#define STACK_SIZE 101
typedef char STACK_t;

STACK_t STACK[STACK_SIZE];
STACK_t* ptr = STACK-1;

bool is_empty();
bool is_full();
void push(STACK_t);
STACK_t pop();
void clear_STACK();
STACK_t peek();

bool operator_precedence(char,char);
void parentheses_check(const char*);
char* to_POSTFIX(char*,int);


bool is_empty() {
	return ptr == STACK - 1 ? true : false;
}

bool is_full() {
	return ptr == STACK + STACK_SIZE-1 ? true : false;
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
	for (;is_empty();)
		*ptr-- = 0;
}

STACK_t peek() {
	return *ptr;
}

bool operator_precedence(char a, char b) {
	switch (a) {
	case '*':
		a = 2;
		break;
	case '/':
		a = 2;
		break;
	case '+':
		a = 1;
		break;
	case '-':
		a = 1;
		break;
	}
	switch (b) {
	case '*':
		b = 2;
		break;
	case '/':
		b = 2;
		break;
	case '+':
		b = 1;
		break;
	case '-':
		b = 1;
		break;
	}
	if (a - b >= 0) return true;
	else return false;
}

void parentheses_check(const char* EXP) {
	for (; *EXP != NULL; EXP++) {
		if (*EXP == '(')
			push(*EXP);
		else if(*EXP == ')')
			pop();
	}

	if (!is_empty()) {
		printf("EXPRESSION'S PARENTHESES ARE ASYMMETRICAL\n");
		exit(EXIT_FAILURE);
	}
}

char* to_POSTFIX(char* EXP, int EXP_LEN) {
	char temp[MAX_EXP];
	strcpy(temp,EXP);
	int i=0;

	for (int k=0 ; k < EXP_LEN;k++) {
		if (isalpha(*(temp + k)))								// 숫자면 exp에 넣기
			*(EXP + i++) = *(temp + k);
		else {													/*********숫자가 아닌 연산자일 떄********/
			if (is_empty())										/*    스택에 연산자 없으면 일단 하나 push   */
				push(*(temp + k));
			else {												/**********스택에 연산자가 있다면**********/
				if (*(temp + k) == '(')								
					push(*(temp + k));
				else if (*(temp + k) == ')') {
					for (; peek() != '(';)
						*(EXP + i++) = pop();
					pop();
				}
				else if (peek() != '(') {
					if (operator_precedence(peek(), *(temp + k))) {
						for(;peek() != '(' && !is_empty()&& operator_precedence(peek(), *(temp + k));)			// 스택의 연산자가 들어오는 연산자보다 우선순위가 높으면 스택 다 비워야함
						*(EXP + i++) = pop();
						push(*(temp + k));
					}
					else
						push(*(temp + k));
				}
				else
					push(*(temp + k));
			}
		}
	}
	for (;!is_empty();)
		*(EXP + i++) = pop();

	*(EXP + i) = '\0';

	return EXP;
}

