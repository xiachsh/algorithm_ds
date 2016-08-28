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
		table->list[i].arrLen = 0;
	}

	*hash = table;
}


int main()
{




}
