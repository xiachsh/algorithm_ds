#ifndef __DS_H
#define __DS_H

#include <stdio.h>
#include <stdlib.h>
	

typedef struct treenode
{
	int val;
	struct treenode * left;
	struct treenode * right;
} TreeNode, * Tree;

typedef struct linknode
{
	int val;
	struct linknode * next;
} LinkNode, * LinkList;


void ll_init(LinkList * l);
void ll_insert_node(LinkList * l, int val);
void ll_delete_node(LinkList * l, int val);
void ll_destroy(LinkList *l);
void ll_print(LinkList l);
void ll_random(LinkList *l, int num);


#endif



