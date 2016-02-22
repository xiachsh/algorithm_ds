#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/ds.h"

void ll_insert_node(LinkList * l, int val)
{
	LinkNode * tmp = malloc(sizeof(struct linknode));
	tmp->val = val;
	tmp->next = NULL;

	if (*l)
	{
		LinkList cur = (*l);
		while (cur->next)
			cur=cur->next;
		cur->next = tmp;
	}
	else
		*l = tmp;	
}
void ll_delete_node(LinkList * l, int val)
{
	LinkList cur = *l;
	LinkList prev = NULL;
	LinkList next = NULL;
	while (cur)
	{
		if (cur->val == val)
		{
			next = cur->next;
			free(cur);
			if (prev)
				prev->next = next;
			else
				*l = next;
		}
		prev=cur;
		cur=cur->next;
	}
}
void ll_init(LinkList *l)
{
	(*l) = NULL;
}
void ll_destroy(LinkList *l)
{
	LinkList cur = (*l);
	LinkList tmp = NULL;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*l = NULL;
}



void ll_random(LinkList *l, int num)
{
	srand(time(NULL));
	int i = 0 ;
	for (;i<num;i++)
	{
		ll_insert_node(l,rand() % 10000);
	}
}

void ll_print(LinkList l)
{
	LinkList cur = l;
	while (cur)
	{
		printf("%d\t",cur->val);
		cur=cur->next;
	}	
	printf("\n");
}
