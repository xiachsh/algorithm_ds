#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _avlNode
{
	int val;
	struct _avlNode * left;
	struct _avlNode * right;
	int bf;
} avlNode,* avlTree;


void avl_destroy(avlTree * tree)
{
	if (*tree)
	{
		avl_destroy( &((*tree)->left));
		(*tree)->left = NULL;
		
		avl_destroy( &((*tree)->right));
		(*tree)->right = NULL;
		
		free(*tree);
		*tree = NULL;
	}
}

void avl_init(avlTree * tree)
{
	avl_destroy(tree);	
	*tree = NULL;
}

void left_rotate(avlTree * tree)
{

}

void right_rotate(avlTree * tree)
{



}

void avl_insert(avlTree * tree,int val)
{
	if (*tree)
	{
		if ((*tree)->val > val)
			avl_insert(&((*tree)->left),val);
		else if ((*tree)->val < val)
			avl_insert(&((*tree)->right),val);
		else
			printf("Warning: Duplicate key %d\n",val);
	}	
	else
	{
		avlNode * tmp = (avlNode* ) malloc(sizeof(avlNode));
		tmp->val = val;
		tmp->left = tmp->right = NULL;
		*tree = tmp;
	}
}


void avl_preorder_tranversal(avlTree * tree)
{
	if (*tree)
	{
		printf("Address: 0x%lx\tVal: %d\tLeft: 0x%lx\tRight: 0x%lx\n",*tree,(*tree)->val,(*tree)->left,(*tree)->right);
		avl_preorder_tranversal(&((*tree)->left));
		avl_preorder_tranversal(&((*tree)->right));
	}	
}

void avl_delete(avlTree * tree,int val)
{



}

int node_height(avlTree * tree,avlNode node)
{
	if (*tree)
	{

	}

}

int main(int argc,char ** argv)
{
	int elements = 10;
	int i = 0;
	avlTree t = NULL;
	

	avl_init(&t);
	
	for (i=0;i<elements;i++)
		avl_insert(&t,rand() % 100);
	avl_preorder_tranversal(&t);
	avl_destroy(&t);
	return 0;
}
