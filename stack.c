#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "stack.h"

stack_t *stack_create()
{
	stack_t *stack = NULL;

	stack=(stack_t *)malloc(sizeof(stack_t));
	stack->head=NULL;
	stack->length=0;

	return stack;
}

stack_node_t *stack_node_create(int val)
{
	stack_node_t *node = NULL;

	node=(stack_node_t *)malloc(sizeof(stack_node_t));
	node->val=val;
	node->next=NULL;
	return node;
}

void stack_push(stack_t *stack, int val)
{
	stack_node_t *node = NULL;

	node=stack_node_create(val);
	node->next=stack->head;
	stack->head=node;
	(stack->length)++;
}

void stack_print(stack_t *stack)
{
	stack_node_t *node;
	node=stack->head;
	int i=0;
	if(stack_empty(stack)==1)
    {
        printf("Stiva este vida.\n\n");
    }
    else
	{
        while(node!=NULL)
        {
            printf("%d ",node->val);
            node=node->next;
            i++;
        }
	}

}

int stack_pop(stack_t *stack)
{
	int val = 0;
	if(stack_empty(stack)==1)
    {
        return INT_MIN;
    }
	stack_node_t *node;
	node=stack->head;
	val=node->val;
	stack->head=node->next;
	(stack->length)--;
	free(node);

	return val;
}

int stack_empty(stack_t *stack)
{
    if(stack->head==NULL)
    {
        return 1;
    }
	return 0;
}

