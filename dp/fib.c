#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>

#define MAX 1024
int fib(int n)
{
	if (n==1 || n==0)
		return n;
	else 
		return fib(n-1) + fib(n-2);
}

int fib_1(int n)
{
	static int lookup[MAX];
	static int intialized = 0;
	if (!intialized) {
		int i = 0;
		for (;i<MAX;i++)
			lookup[i] = -1;
		intialized = 1;
	}
	lookup[0] = 0;
	lookup[1] = 1;
	if (lookup[n] == -1) 
		lookup[n] = fib_1(n-1) + fib_1(n-2);
	return lookup[n];				
}
int fib_2(int n)
{
	int i = 0;
	int * sum = malloc (sizeof(int) * n+1);
	sum[0] = 0;
	sum[1] = 1;
	for (i=2;i<=n;i++)
	   sum[i] = sum[i-1] + sum[i-2];
	int ret = sum[n];
	free(sum);
	return ret;
}

void usage(int argc,char ** argv)
{
	fprintf(stderr,"%s usage:\n",argv[0]);
	fprintf(stderr,"	%s -n num\n",argv[0]);
	exit(0);
}

int main(int argc,char ** argv)
{
	int num = 0 ;
	int c ;
	if (argc<2) usage(argc,argv);
	while ( (c=getopt(argc,argv,"n:")) != -1 ){ 	
		switch(c) {
			case 'n':
			if (!isdigit(optarg[0])) 
				usage(argc,argv);
			num = atoi(optarg);
				break;
			default:
				usage(argc,argv);
				break;
		}
	}
	time_t time1 = time(NULL);
	int val = fib_2(num);
	time_t time2 = time(NULL);
	fprintf(stdout,"num:%d value:%d ,time cost:%d secs\n",num,val,time2-time1);
	return 0;
}



