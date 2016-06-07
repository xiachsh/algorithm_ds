#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#define LEN 128

typedef struct _cs {
	char * start;	
	int len;
} LCS;

LCS find_lcs(char * buffer1,int len1,char *buffer2,int len2) 
{
	int i = 0;
	int j = 0;
	LCS lcs = {NULL,-1};
	char * buf_long = NULL;
	char * buf_short = NULL;
	int len_short, len_long ;
	if (len2>len1) {
		buf_long = buffer2;
		buf_short = buffer1;
		len_long = len2;
		len_short = len1;
	}
	else {
		buf_long = buffer1;
		buf_short = buffer2;
		len_long = len1;
		len_short = len2;
	}

	for (i=0;i<len_short;i++)
	{
		for (j=0;j<len_long;j++) {
			int len = 0;
			if (buf_short[i] == buf_long[j]  && buf_short[i] != ' ') {
				len = 1;
				int _i = i+1;
				int _j = j+1;
				while (_i<len_short && j<len_long){
					if(buf_short[_i] != buf_long[_j] || buf_short[_i] == ' ')  
						break;
					len++;
					_i++;
					_j++;
				}
				if (len>lcs.len){
					lcs.start = &(buf_short[i]);
					lcs.len = len;
				}
		    	}
		}	
	}
	return lcs;
}


int main()
{

	char *buffer1 = malloc(sizeof(char) * LEN+1);
	char *buffer2 = malloc(sizeof(char) * LEN+1);

	/*
	int i = 0;
	for(i=0;i<LEN;i++){	
		buffer1[i] = rand () % 26 + 65; 	
		buffer2[i] = rand () % 26 + 65; 	
	}
	*/
	bzero(buffer1,LEN+1);
	bzero(buffer2,LEN+1);
	sprintf(buffer1,"%s\n","Hi,hello world");
	sprintf(buffer2,"%s\n","he world he");
	
	printf("%s\n",buffer1);
	printf("%s\n",buffer2);

	LCS lcs = find_lcs(buffer1,strlen(buffer1),buffer2,strlen(buffer2));
	char buffer[1024] ;
	bzero(buffer,1024);
	memcpy(buffer,lcs.start,lcs.len);
	printf("len:%d %s\n",lcs.len,buffer);
	free(buffer1);
	free(buffer2);
	return 0;
}
