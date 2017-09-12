#define _GNU_SOURCE // to avoid "implicit declaration of function `asprintf'"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> // for readdir
#include <fcntl.h>
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
#include "cd.h"
	
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
int hasPrefix(char const *, char const *);

int hasPrefix(char const *p, char const *q) {
	int i = 0;
	for(i = 0; q[i]; i++) {
		if(p[i] != q[i])
			return -1;
	}
	return 0;
}

int main() {
	char buffer[BUFFERSIZE];
	char prompt[1024];
	char *tok;
	tok = strtok (buffer, " ");
	while(buffer != NULL){
		bzero(buffer, BUFFERSIZE);
		getcwd(prompt, sizeof(prompt));
		printf(KGRN "myshell:" KNRM);
		printf(KBLU "-%s", prompt);
		printf(KNRM "" KNRM );
		printf(BOLD "$ " KNRM);
		fgets(buffer, BUFFERSIZE, stdin);
		if (hasPrefix(buffer, "cd..") == 0) {
			buffer[strlen(buffer)-1] = buffer[strlen(buffer)];
			printf(KRED "%s: command not found\n", buffer);
			printf(KNRM "" KNRM);
		} 
		else if (strcmp(buffer, "cd \n")==0 || strcmp(buffer, "cd\n")==0) {
			cd("/home/");	
		}
		else if (hasPrefix(buffer, "cd") == 0) {
			tok = strchr(buffer, ' '); //use something more powerful
			if (tok) {
				char *tempTok = tok + 1;
				tok = tempTok;
				char *locationOfNewLine = strchr(tok, '\n');
				if (locationOfNewLine) {
					*locationOfNewLine = '\0';
				}
				cd(tok);
			}
		}
		else if (hasPrefix(buffer, "rmdir") == 0) {
			tok = strchr(buffer, ' '); //use something more powerful
			if (tok) {
				char *tempTok = tok + 1;
				tok = tempTok;
				char *locationOfNewLine = strchr(tok, '\n');
				if (locationOfNewLine) {
					*locationOfNewLine = '\0';
				}
				remove_directory(tok);
			}
		}
		else if (hasPrefix(buffer, "mkdir") == 0) {
			tok = strchr(buffer, ' '); //use something more powerful
			if (tok) {
				char *tempTok = tok + 1;
				tok = tempTok;
				char *locationOfNewLine = strchr(tok, '\n');
				if (locationOfNewLine) {
					*locationOfNewLine = '\0';
				}
				make_dir(tok);
			}
		}
		else if (hasPrefix(buffer, "pwd") == 0) {
			pwd();
		}
		else if (hasPrefix(buffer, "cls") == 0) {
			int i=100;
			while(i--)
				printf("\n");
		}
		else if (hasPrefix(buffer, "ls") == 0) {
			ls();
		}
		else if (hasPrefix(buffer, "sudo apt-get") == 0) {
			printf(KRED "Install karega haan\n");
			printf(KNRM "" KNRM);
		}
		else if (hasPrefix(buffer, "sudo") == 0) {
			printf(KRED "Itne Bade nahi hue abhi\n");
			printf(KNRM "" KNRM);
		}
		else if (hasPrefix(buffer, "exit") == 0) {
			exit(0);
		}
		else {
			buffer[strlen(buffer)-1] = buffer[strlen(buffer)];
			printf(KRED "%s: command not found\n", buffer);
			printf(KNRM "" KNRM);
		}
	}
	return 0;
}
