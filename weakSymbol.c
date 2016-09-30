#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <stdint.h>

#pragma weak myPower



/*
 *
 * this program can be compiled successfully without any error 
 *  gcc -g -o weakSymbol weakSymbol.c
 *
 */

int myPower(int);
int main()
{

	int x = 100;
	myPower(x);

	return 0;
}
