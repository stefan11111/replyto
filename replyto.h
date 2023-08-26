#define ALLOCA			/*use alloca instead of malloc, better performance*/
#define EXTENSION ".reply"	/*extension to append to filename*/
#define MODE 00664		/*permissions for created file*/
#define FLAGS O_WRONLY|O_CREAT	/*flags for created file*/
#define MAX_FILENAME 256	/*max filename*/
#define BUFLEN 4		/*buffer to read file, default is 4k*/
#define FILENAME "reply"	/*filename to use if input is from stdin*/
#define STDOUT 1		/*enable writing to stdout, stdout is fd 1*/
