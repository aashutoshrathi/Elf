#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int make_dir(int *argc,char **argv){
	int ret;
	if(mkdir("//mnt/c/Users/Aashutosh Rathi/Desktop/",S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==-1) {
		printf("Cannot create Directory,Given path is incorrect");
	} else {
		ret = mkdir("/mnt/c/Users/Aashutosh Rathi/Desktop/",S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);   	
	} 
	return 0;
}
