#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap_element(int *buffer,int i,int j)
{
	int tmp = buffer[i];
	buffer[i] = buffer[j];
	buffer[j] = tmp;
}





int partition(int * buffer,int left,int right)
{
 	int pivot  = *(buffer+right);
	int i = left - 1;
	int j = right;

	for (;;)
	{
		//can not add i < j since we cann't exchange the i with right 
		//in case the right element is in the correct position
		while (buffer[++i] < pivot);
		while (buffer[--j] > pivot) if (i>=j) break;
		if (j>i)
			swap_element(buffer,i,j);
		//cann't only break if the j == i in case the the right element is in the correct position
		// in this condition the value of i is larger than value of j
		else
			break;
	}
	swap_element(buffer,i,right);
	return i;
}

void quicksort(int * buffer, int left,int right)
{
	if (left<right)
	{
		int i = partition(buffer,left,right);	
		quicksort(buffer,left,i-1);
		quicksort(buffer,i+1,right);
	}
}



void print_array(int * buffer,int size)
{
	int i = 0;
	for (i = 0;i<size;i++)
	{
		printf("%d\t",buffer[i]);
	}
	printf("\n");
}

void usage(int argc,char ** argv)
{
	printf("%s usage:\n",argv[0]);	
	printf("%s Num\n",argv[0]);	
	exit(1);
}




int main(int argc,char ** argv)
{
	if ( 2 != argc) usage(argc,argv);
	if ( ! isdigit(*argv[1]) )
	{
		printf("you input non digit,exiting");
		exit(1);
	}
	int num = atoi(argv[1]);

	int *buffer = (int *) malloc(sizeof(int) * num);
	int i;
	for (i=0;i<num;i++)
		buffer[i] = rand() % 1000;
	quicksort(buffer,0,num-1);
	print_array(buffer,num);
	free(buffer);

	return 0;
}
