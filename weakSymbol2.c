#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <stdint.h>

int __attribute__((weak)) myPower(int);
int myPower_(int) __attribute__((weak));

extern int __attribute__((weak))  g;


/*
 *
 * this program also can be compiled w/o any error
 *
 */

int main()
{

	int x = 0;
	myPower(x);
	myPower_(g);
}
