#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFFERSIZE 200

int cd(char *pth) {
	char temp[BUFFERSIZE];
	getcwd(temp, sizeof(temp));
	char path[BUFFERSIZE];
	strcpy(path, pth);
	char cwd[BUFFERSIZE];
	if(pth[0] != '/') {// true for the dir in cwd
		getcwd(cwd, sizeof(cwd));
		strcat(cwd, "/");
		strcat(cwd, path);
		chdir(cwd);
	} else {//true for dir w.r.t. /
		chdir(pth);
	}
	getcwd(cwd, sizeof(cwd));
	if(strcmp(cwd, temp) == 0){
		printf("No such File or Directory\n");
	}
	return 0;
}
