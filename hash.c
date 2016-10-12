#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct _hash_element_t 
{
	char *key;
	int index;
	void * data;
} hash_element_t;


typedef struct _hash_element_arr_t
{
	hash_element_t** elems;
	int curIndex;
	int arrLen;
} hash_list_t;


typedef struct _hast_table_t {
	int totalNum;
	int (*hashFunc) (char *key,int size);
	int size;
	hash_list_t * list;
} hash_table_t;


int hash_string (char *key,int size)
{
	//currently make it simple 
	return (atoi(key) % size);
}

void init_hash_table(hash_table_t ** hash ,int size,int len)
{
	hash_table_t * table = malloc(sizeof(hash_table_t));
	table->size = size;
	table->hashFunc = hash_string;	
 	table->totalNum = 0;
	table->list = malloc(sizeof(hash_list_t) * size);

	int i = 0;
	for (i=0;i<size;i++) {
		table->list[i].elems = malloc(sizeof(hash_element_t*) * len); 		
		table->list[i].curIndex = 0;
		table->list[i].arrLen = len;
	}

	*hash = table;
}

hash_element_t * create_element(int index,char *key,void *obj)
{
	hash_element_t * t = malloc(sizeof(hash_element_t));
	t->index = index;
	t->key = strdup(key);
	t->data = obj;

	return t;
}

void destroy_element(hash_table_t hash,int index,int elementIndex)
{
	if (hash.list[index].elems[elementIndex]) {
		if (hash.list[index].elems[elementIndex]->data) 
			free(hash.list[index].elems[elementIndex]->data);
		if (hash.list[index].elems[elementIndex]->key) 
			free(hash.list[index].elems[elementIndex]->key);
	}
	free(hash.list[index].elems[elementIndex]);
	hash.list[index].elems[elementIndex] = NULL;
}

int insert_hash_elem(hash_table_t hash,char * key,void *obj)
{
	int keyIndex = hash.hashFunc(key,hash.size);
	if (find_hash_elem(hash,keyIndex,key))
		return -1;
	hash_element_t * t = create_element(keyIndex,key,obj);
	int i =  hash.list[keyIndex].curIndex;
	hash.list[keyIndex].elems[i++] = t;
	hash.list[keyIndex].curIndex = i;

	hash.totalNum += 1;
	return 0;
}

int remove_hash_elem(hash_table_t hash,char *key)
{
	int keyIndex = hash.hashFunc(key,hash.size);
	int elemIndex = 0;
	if (!find_hash_elem(hash,keyIndex,key,&elemIndex))
		return -1;

	int curIndex = hash.list[keyIndex].curIndex;
	if (curIndex != elemIndex ) {
		hash.list[keyIndex].elems[elemIndex] = hash.list[keyIndex].elems[curIndex];	
	}
	hash.list[keyIndex].elems[curIndex] = NULL;
	hash.list[keyIndex].curIndex -= 1;

	hash.totalNum -= 1;
}


int find_hash_elem(hash_table_t hash ,int index,char * _key,int *returnIndex) {
	int i = 0;
	int len = hash.list[index].curIndex;
	for (i=0;i<len;i++)
	if ( strcmp( hash.list[index].elems[i]->key,_key) == 0 )  {
		*returnIndex = i ;
		return 1;
	}
	return 0;
}

int get_value(hash_table_t hash,char * key,void ** data)
{
	int keyIndex = hash.hashFunc(key,hash.size);	
	int elementIndex = -1;
	int ret = find_hash_elem(hash,keyIndex,key,&elementIndex);
	if (!ret) 
		return 0;
	*data =  hash.list[keyIndex].elems[elementIndex]->data;

	return 1;	
}


void destroy_hash_table(hash_table_t ** hash ,int size)
{
	int i = size-1;
	hash_table_t * hash_table = *hash;
	for (;i>=0;i--) {
		int j = hash_table->list[i].curIndex-1;
		for (;j>=0;j--) {
			destroy_element(*hash_table,i,j);
		}
		free(hash_table->list[i].elems);	
	}		
	free(hash_table->list);
	free(hash_table);		
	*hash = NULL;
}
int main()
{

	hash_table_t * table = NULL;
	init_hash_table(&table,10,10);
	int * num = NULL;
	int i = 0;
	char iNum[40];
	bzero(iNum,40);
	for (i=0;i<64;i++) {
		sprintf(iNum,"%d",i);
		num = (int *) malloc(sizeof(int));
		*num = i;
		insert_hash_elem(*table,iNum,num);
	}

	void * element  = NULL;

	sprintf(iNum,"%d",20);	
	get_value(*table,iNum,&element);
	if (element) {
		printf("%d\n", *((int*)element));
	}

	destroy_hash_table(&table,10);
	return 0;
}

