#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>


void swap_element(int * buffer,int i, int j)
{
	int tmp = *(buffer+i);
	*(buffer+i) = *(buffer+j);
	*(buffer+j) = tmp;
}

int partition(int * buffer,int left,int right)
{
	int pivot = buffer[right];
	int i = left-1;
	int j = right;
	for(;;)
	{
		while(buffer[++i] < pivot);
		while(buffer[--j] > pivot) if (i>=j) break;
		if (i>=j) break;
		swap_element(buffer,i,j);
	}
	swap_element(buffer,i,right);
	return i;
}

void quickSort(int * buffer,int left,int right)
{
	if (left<right)
	{
		int p = partition(buffer,left,right);
		quickSort(buffer,left,p-1);
		quickSort(buffer,p+1,right);
	}
}
void print_buffer(int * buffer,int length)
{
	int i = 0 ;
	for (i=0;i<length;i++)
		printf("%4d\t",buffer[i]);
	printf("\n");
}

int not_sorted(int * buffer, int length)
{
	int i = 0 ;
	for (i=0;i<length-1;i++)
	{
		if (buffer[i] > buffer[i+1])
			return 1;
	}
	return 0;
}
int binary_search(int * buffer,int length,int val)
{
	if (val < buffer[0] || val > buffer[length-1])
		return -1;
	int i = 0;
	int j = length-1;
	while (i<j)
	{
		int mid = (i+j) / 2;
		if (buffer[mid] == val) return mid;
		else if (buffer[mid] > val)
			j = mid-1;
		else 
			i = mid+1;
	}
	if (buffer[i] == val) return i;
	return -1;
}

void usage(int argc,char ** argv)
{
	printf("%s -n num\n",argv[0]);
	exit(1);
}

int main(int argc,char ** argv)
{
	int i;
	int * buffer;
	int size = 16;
	int c;

	while( (c=getopt(argc,argv,"n:")) != -1 )
	{
		switch (c)
		{
			case 'n':
				if (isdigit(optarg[0]))
					size = atoi(optarg); 
				else 
				{
					printf("the size is not valid :%s",optarg);
					usage(argc,argv);
				}
				break;
			default:
				usage(argc,argv);
				break;
		}
	}

	buffer = malloc(sizeof(int) * size);
	for (i=0;i<size;i++)
	buffer[i] = rand() % 1000;
	quickSort(buffer,0,size-1);
	if (not_sorted(buffer,size)){
		printf("quick Sort failed\n");
		goto _exit;		
	}
	for (i=0;i<size;i++)
	{
		int index = binary_search(buffer,size,buffer[i]);
		if (buffer[index] != buffer[i]){
			printf("failed:binary_search\n");
			goto _exit;
		}
	}
_exit:
	free(buffer);
	return 0;
}





