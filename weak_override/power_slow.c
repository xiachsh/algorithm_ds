#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>


#include "power_slow.h"

int power2(int x)
{
	printf("slow power2\n");
	return x*x;
}


int power3(int x)
{
	return power2(x)*x;
}
