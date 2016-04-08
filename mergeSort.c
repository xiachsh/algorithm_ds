#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void merge(int * buffer,int left,int mid,int right)
{
	//split the array into two sub arrays 
	//first one : from left to mid
	//second:     from mid+1 to right
	int l1 = mid-left+1;
	int l2 = right - mid;
	int arr1[l1],arr2[l2];
	int i = 0;
	int j = 0;
	//copy two sub array to seperate arrays 
	
	for (i=0;i<l1;i++)
		arr1[i] = buffer[left+i];
	for (j=0;j<l2;j++)
		arr2[j] = buffer[mid+1+j];

	i = 0;
	j = 0;
	int k = left;
	while(i<l1 && j<l2)
	{
		if (arr1[i] < arr2[j])
		{
			buffer[k++] = arr1[i++];
		}
		else
		{
			buffer[k++] = arr2[j++];
		}
	}
	
	while(i<l1)
		buffer[k++] = arr1[i++];
	while(j<l2)
		buffer[k++] = arr2[j++];
}

int mergeSort(int * buffer,int left,int right)
{
	if(left<right)
	{
		int mid = left+ (right-left) / 2;
		mergeSort(buffer,left,mid);
		mergeSort(buffer,mid+1,right);
		merge(buffer,left,mid,right);
	}
}

void print_buffer(int * buffer,int length)
{
	int i = 0;
	for (;i<length;i++)
		printf("%4d\t",buffer[i]);
	printf("\n");
}
void usage(int argc,char** argv)
{
	printf("%s -n num\n",argv[0]);
	exit(1);
}
int main(int argc,char **argv)
{
	int size = 10;
	int c;
	int i;
	int * buffer;
	while( ( c = getopt(argc,argv,"n:") ) != -1 )
	{
		switch (c)
		{
			case 'n':
				size = atoi(optarg);
				break;	
			default:
				usage;
				break;
		}

	}

	buffer = malloc(sizeof(int) * size);
	for (i=0;i<size;i++)
		buffer[i] = rand () % 100;
	print_buffer(buffer,size);
	mergeSort(buffer,0,size-1);
	print_buffer(buffer,size);
	
	free(buffer);
	return 0;
}
