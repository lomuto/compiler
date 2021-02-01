#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"

struct node{
	char op;
	struct node *left_child,*right_child;	// int* a,b ==> int* a, int b. not int* b
};

typedef struct node NODE;

NODE* root_ptr;

NODE* init_node(){
	NODE* node = malloc(sizeof(NODE));
	node->left_child = NULL;
	node->right_child = NULL;

	return node;
}

void make_tree(const char* EXP){

	for(;*EXP;EXP++){
		NODE* new_node = init_node();
		if(isdigit(*EXP)){
			new_node->op = *EXP;
			push((void*)new_node);
		}
		else{
			NODE* operator = new_node;
			operator->op = *EXP;
			operator->right_child = (NODE*)pop();
			operator->left_child = (NODE*)pop();
			
			root_ptr = operator;

			push((void*)operator);
		}
	}
}

void POSTORDER(NODE* node){
	if(node){
		POSTORDER(node->left_child);
		POSTORDER(node->right_child);
		printf("%c ",node->op);
	}
}