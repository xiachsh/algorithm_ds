#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>


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
void avl_inorder_tranversal(avlTree * tree)
{
	if (*tree)
	{
		avl_inorder_tranversal(&((*tree)->left));
		printf("Address: 0x%lx\tVal: %d\tLeft: 0x%lx\tRight: 0x%lx\n",*tree,(*tree)->val,(*tree)->left,(*tree)->right);
		avl_inorder_tranversal(&((*tree)->right));
	}	
}

int find_max_in_left(avlTree tree,int * ret)
{
	if (tree)
	{
		avlTree cur = tree;
		while (cur->right)
			cur=cur->right;
		*ret = cur->val;
		return 0;
	}
	else 
		return -1;
}

int find_min_in_right(avlTree tree,int * ret)
{
	if (tree)
	{
		avlTree cur = tree;
		while (cur->left)
			cur = cur->left;
		*ret = cur->val;
		return 0;
	}
	else 
		return -1;
}

void avl_delete(avlTree * tree,int val)
{
	if(*tree)
	{
		if((*tree)->val > val)
			avl_delete((&(*tree)->left),val);
		else if ((*tree)->val < val)
			avl_delete((&(*tree)->right),val);
		else 
			{
				if ( (!(*tree)->left) && (!(*tree)->right) )
				{
					free(*tree);
					*tree = NULL;	
				}
				else if ((!(*tree)->left) && ((*tree)->right) )
				{
					free(*tree);
					*tree = (*tree)->right;
				}
				else if (((*tree)->left) && (!(*tree)->right) )
				{
					free(*tree);
					*tree = (*tree)->left;
				}
				else
				{
					int min ;
					find_min_in_right((*tree)->right,&min);
					(*tree)->val = min;
					avl_delete((&(*tree)->right),min);
				}
			}
	}
}

int node_height(avlTree * tree,avlNode node)
{
	if (*tree)
	{

	}

}

void usage(int argc,char ** argv)
{

	printf("%s usage:\n",argv[0]);
	printf("	%s -n num\n",argv[0]);
	printf("	%s -d num   # to deleted \n",argv[0]);
	exit (1);
}

int main(int argc,char ** argv)
{
	int elements = 10;
	int i = 0;
	avlTree t = NULL;
	int c;
	int deleted = 0;
	int delete_num;
	while ( (c=getopt(argc,argv,"n:d:")) != -1 )
	{
		switch(c)
		{		
			case 'n':
				elements = atoi(optarg);
				break;
			case 'd':
				deleted = 1;
				delete_num = atoi(optarg);
				break;
			default:
				usage(argc,argv);
				break;	
		}
	}	

	avl_init(&t);
	
	for (i=0;i<elements;i++)
		avl_insert(&t,rand() % 1000);
	avl_preorder_tranversal(&t);
	printf("\n");
	int min ;
	int max ;
	int ret = find_min_in_right(t,&min);
	ret = find_max_in_left(t,&max);

	if(deleted)
		avl_delete(&t,delete_num);

	avl_inorder_tranversal(&t);
	
	avl_destroy(&t);
	return 0;
}
