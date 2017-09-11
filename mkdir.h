#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFERSIZE 200

int make_dir(char *pth){
	int ret;
	char path[BUFFERSIZE];
	char cwd[BUFFERSIZE];
	strcpy(path, pth);
	if(pth[0] != '/') {// true for the dir in cwd
		getcwd(cwd, sizeof(cwd));
		strcat(cwd, "/");
		strcat(cwd, path);
	}

	if(mkdir(cwd, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==-1) {
		printf("Cannot create Directory,Given path is incorrect");
	} else {
		ret = mkdir(cwd, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);   	
	} 
	return 0;
}
