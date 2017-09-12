#define _GNU_SOURCE // to avoid "implicit declaration of function `asprintf'"
#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFFERSIZE 200 //define size

int cd(char *pth) { //takes pth as argument
	char temp[BUFFERSIZE];
	getcwd(temp, sizeof(temp)); //store current directory to temp
	char path[BUFFERSIZE];
	strcpy(path, pth); //copy pth to path
	char cwd[BUFFERSIZE];
	if(pth[0] != '/') {// true for the dir in cwd
		getcwd(cwd, sizeof(cwd)); //stores current working directory to cwd
		strcat(cwd, "/"); //concates "/" to cwd
		strcat(cwd, path); //concates path to cwd
		chdir(cwd); //change dir to cwd
	} else {//true for dir w.r.t. /
		chdir(pth);
	}
	getcwd(cwd, sizeof(cwd)); //stores current working directory to cwd
	if(strcmp(cwd, temp) == 0){ // if cwd == temp , then no directory change
		printf("No such File or Directory\n");
	}
	return 0;
}
