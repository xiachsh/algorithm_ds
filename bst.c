#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

typedef struct _bstnode
{
	int val;
	struct _bstnode * left;
	struct _bstnode * right;
} BSTNode,*BSTree;


void bst_init(BSTree *t)
{
	*t = NULL;
}
int bst_insert(BSTree *t, int val)
{
	if ( !(*t) ) 
	{
		BSTNode * node = (BSTNode *)malloc(sizeof(BSTNode));
		node->val = val;
		node->left = NULL;
		node->right = NULL;
		*t = node;
		return 0;
	}
	else if ( (*t)->val > val )
	{
		return bst_insert( &((*t)->left),val );
	}
	else if ( (*t)->val < val )
	{
		return bst_insert( &((*t)->right),val );
	}
	else if ( (*t)->val == val)
	{
		return -1;
	}

}
/*
 *	return the depth of node
 *	return -1 if the node not found
 *
 */
int depth(BSTree t,int val)
{
	if (t == NULL) return -1;
	if (t->val == val) return 0;
	else if (t->val > val)
	{
		int depth_left = depth(t->left,val);
		if (depth_left != -1)
			return depth_left+1;
		else
			return -1;
	}
	else 
	{
	
		int depth_right = depth(t->right,val);
		if (depth_right != -1)
			return depth_right+1;
		else
			return -1;
	}

}

/*
 *
 *	return shortest path from node val1 to node val2
 *
 */

void shortest_path(BSTree t, int val1, int val2)
{
	

}


/*
 *
 *
 *
 *
 */
int height(BSTree t,int val)
{


	return -1;
}

void bst_print(BSTree t)
{
	if (t)
	{
		bst_print(t->left);	
		printf("Address : %lx\t Value %4d\t Left:%lx\t Right: %lx\t\n",t,t->val,t->left,t->right);
		bst_print(t->right);	
	}
}

void bst_print_preorder(BSTree t)
{
        if (t)
	{
		printf("Address : %lx\t Value %4d\t Left:%lx\t Right: %lx\t\n",t,t->val,t->left,t->right);
		bst_print_preorder(t->left);
		bst_print_preorder(t->right);
	}
}


void bst_destroy(BSTree *t)
{
	if (*t)
	{
		
		 bst_destroy( &((*t)->left) );
		 (*t)->left = NULL;
		 bst_destroy( &((*t)->right) );
		 (*t)->right = NULL;
		 free(*t);
	}
}
int find_min(BSTree t)
{
	BSTNode *cur = t;
	while (cur && cur->left)
	{
		cur=cur->left;
	}
	return cur->val;
}
int find_max(BSTree t)
{
	BSTNode *cur = t;
	while (cur && cur->right)
	{
		cur=cur->right;
	}
	return cur->val;
}

void bst_delete_node_recursive(BSTree *t,int val)
{

	if (*t == NULL)return ;
	if ((*t)->val > val)
		bst_delete_node_recursive( &((*t)->left),val );
	else if  ((*t)->val < val)
		bst_delete_node_recursive( &((*t)->right),val);
	else
	{
		if (!(*t)->left && !(*t)->right)
		{
			free(*t);
			*t = NULL;
		}
		else if ((*t)->left && !(*t)->right)
		{
			BSTNode * tmp = (*t);
			*t = (*t)->left;
			free(tmp);
		}
		else if (!(*t)->left && (*t)->right)
		{
			 BSTNode * tmp = (*t);
			 *t = (*t)->right;
			 free(tmp);
		}
		else
		{
			int min = find_min((*t)->right);
			(*t)->val = min;
			bst_delete_node_recursive(&((*t)->right),min);
		}
	}
}

void bst_delete_node(BSTree *t,int val)
{
	BSTNode * cur = *t;
	BSTNode * parent = NULL;
	int left_child = -1;
	while (cur)
	{
		if (cur->val > val)
		{
			parent = cur;
		 	cur = cur->left;
			left_child = 1;	
		 }
		else if (cur->val < val)
		{
			parent = cur;
			cur = cur->right;
			left_child = 0;
		}
		else
			break;
	}
	if ( cur )
	{
		if ( !(cur->left) && ! (cur->right))
		{
			if (left_child == 1)
				parent->left = NULL;
			else if (left_child == 0)
				 parent->right = 0;
			else 
				*t = NULL;
			free(cur);
		}
		else if ((cur->left) && ! (cur->right))
		{
			if (left_child == 1)
				 parent->left = cur->left;
			else if (left_child == 0)
				parent->right = cur->left;
			else
				*t = cur->left;
			free(cur);
		}
		else if ( !(cur->left) &&  (cur->right))
		{
			if (left_child == 1)
				 parent->left = cur->right;
			else if (left_child == 0)
				parent->right = cur->right;
			else
				*t = cur->right;
			free(cur);
		}
		else
		{
			int min = find_min(cur->right);
			cur->val = min;
			bst_delete_node(&(cur->right),min);	
		}
	}
	else
	{
		printf("Warnning, cannot find the val %d\n",val);
	}	
}


void usage(int argc,char ** argv)
{

	printf("%s usage:\n",argv[0]);
	printf("%s -p \n",argv[0]);
	printf("%s -o \n",argv[0]);
	printf("%s -i iteration \n",argv[0]);
	printf("%s -n Numbers \n",argv[0]);

	exit(-1);
}

int main(int argc,char ** argv)
{
	BSTree t = NULL;
	bst_init(&t);
	int i = 0;
	int num = 10;
	int itr = 1;
	int flag_p_pre = 0;
	int flag_p_post = 0;
	int num_delete = -1;
	int c ;
	while ((c=getopt(argc,argv,"poi:n:d:")) != -1)
	{
		switch(c)
		{
			case 'p':
				flag_p_pre  = 1;
				break;
			case 'o':
				flag_p_post = 1;
				break;
			case 'i':
				itr = atoi(optarg);	
				break;
			case 'n':
				num = atoi(optarg);
				break;
			case 'd':
				num_delete = atoi(optarg);
				break;
			default:
				usage(argc,argv);
				break;
		}
	}

	int j = 0;
	for (j=0;j<itr;j++)
	{
		t = NULL;
		for (i=0;i<num;i++)
		{
			bst_insert(&t,rand() % 100);
		}
		if (flag_p_pre == 1)
		{
			bst_print_preorder(t);
			printf("\n\n");
		}

		printf("val %d has # %d depth\n",num_delete,depth(t,num_delete));
		bst_delete_node_recursive(&t,num_delete);
		if (flag_p_post == 1)
			bst_print_preorder(t);
		bst_destroy(&t);
	}
	return 0;
}
