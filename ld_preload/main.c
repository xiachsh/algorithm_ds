#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>


int main()
{
	char * str1 = "hello";
	char * str2 = "world";


	if ( !(strcmp(str1,str2) )) {
		printf("str1 (%s) == str2 (%s) ?\n",str1,str2);
	}
	else 
		printf("str1 (%s) != str2 (%s) ?\n",str1,str2);

	return 0;

}
