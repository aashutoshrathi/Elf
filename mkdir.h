#define _GNU_SOURCE // to avoid "implicit declaration of function `asprintf'"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFERSIZE 200

int make_dir(char *pth){ //takes pth as a input
	int ret; //initialize return
	char path[BUFFERSIZE]; //initialize storage for path
	char cwd[BUFFERSIZE];
	strcpy(path, pth); //copies argument pth to path
	if(pth[0] != '/') {// true for the dir in cwd
		getcwd(cwd, sizeof(cwd)); //stores current working directory to cwd
		strcat(cwd, "/"); //concates "/" to cwd
		strcat(cwd, path); //concates path to cwd
	}
	if(mkdir(cwd, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==-1) { //if the path cwd have no read write access to user then returns 1
		printf("Cannot create Directory,Given path is incorrect");
	} else { //else create a directory
		ret = mkdir(cwd, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);   	
	} 
	return 0;
}
