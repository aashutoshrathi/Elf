#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> // for readdir
#include <fcntl.h> // 
#include <ftw.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/dir.h>
#include <sys/param.h>
#include "ls.h"
#include "mkdir.h"
#include "pwd.h"
#include "remove_dir.h"
	
#define FALSE 0
#define TRUE 1
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define BOLD "\e[1m"
#define BGBLACK "\e[40m"

int remove_directory(char *r); // Declaration
int pwd();

int main() {
	char arg[1024];
	char args[1024];
	while (strcmp(arg, "exit") != 0){
		printf("myshell$ ");
		gets(arg); // gets is not protected.
		char *del = " ";
		char *s = strtok(arg, del);
		if(strcmp(s, "pwd") == 0) {
			pwd();
		}
		else if(strcmp(s, "ls") == 0) {
			ls();
		}
		else if(strcmp(s, "rmdir") == 0) {
			remove_directory(args);
		}
		else if(strcmp(s, "mkdir") == 0) {
			//make_dir();
		}
		else if(strcmp(s, "cd") == 0) {
			//cd();
		}
		else if(strcmp(s, "cls") == 0) {
			int i = 300;
			while(i--)
				printf("\n");
		}
		else if(strcmp(s, "exit") == 0) {
			exit(0);
		}
		else {
			printf("%s: Command not found\n",arg);
		}

	}
	return 0;
}