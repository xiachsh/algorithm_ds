#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define INFO 1
#define ERR 2 
#define STD_OUT stdout
#define STD_ERR stderr



#define LOG_MESSAGE(prio,stream,msg,...) do { \
	char *str;			      \
	if (prio == INFO)		      \	
		str = "INFO"; 		      \
	else if (prio == ERR)		      \
		str = "ERR";		      \
	fprintf(stream,"[%s] : %s : %d : "msg" \n", \
			str,  __FILE__, __LINE__,##__VA_ARGS__); \
	} while (0) 	



int main(void)
{
	char * s = "hello";

	LOG_MESSAGE(ERR,STD_ERR,"Failed to open file");
	

	LOG_MESSAGE(INFO,STD_OUT,"%s some piece of messages",s);

	LOG_MESSAGE(INFO,STD_OUT,"%d + %d = %d",10,20,(10+20));

	return 0;
}
