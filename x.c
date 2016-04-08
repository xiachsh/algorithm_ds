#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

	int * buffer = malloc(sizeof(int) * 10);

	*(buffer+100) = 1000;
	printf("%d\n",*(buffer+100));
	return 0;
}
