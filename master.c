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
#include "ls-l.h"
	
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

//checks for prefix of a string
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
	register struct passwd *pw ;
	register uid_t uid;
	uid = getuid(); //gets the userid
	pw = getpwuid(uid); //gets user for the particular userid
	char *name = pw->pw_name; //get username for the user
	tok = strtok (buffer, " "); //breaks the buffer on space and stores the string before space to tok
	while(buffer != NULL){ 
		bzero(buffer, BUFFERSIZE); //allocates memory buffersize to buffer
		getcwd(prompt, sizeof(prompt)); //stores current working directory to prompt
		printf(KGRN ""); //pencolor red
		printf("%s",name); //prints username
		printf("@ubuntu:" KNRM); 
		printf(KBLU "-%s", prompt); 
		printf(KNRM "" KNRM );
		printf(BOLD "$ " KNRM);
		fgets(buffer, BUFFERSIZE, stdin); //stores the input to buffer (with spaces)
		if (hasPrefix(buffer, "cd..") == 0) {   //if a string starts with "cd.." throw error
			buffer[strlen(buffer)-1] = buffer[strlen(buffer)]; 
			printf(KRED "%s: command not found\n", buffer);
			printf(KNRM "" KNRM);
		} 
		else if (strcmp(buffer, "cd \n")==0 || strcmp(buffer, "cd\n")==0) { //if string is "cd__" go to home directory
			cd("/home/");	
		}
		else if (hasPrefix(buffer, "cd") == 0) { //if string has "cd" as prefix, change directory to address after it.
, 			tok = strchr(buffer, ' '); //use something more powerful
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
		else if (hasPrefix(buffer, "rmdir") == 0) { // if buffer has prefix rmdir, deletes the arg file after it (if exist).
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
		else if (hasPrefix(buffer, "mkdir") == 0) { // if buffer has prefix mkdir, makes the arg file after it.
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
		else if (hasPrefix(buffer, "pwd") == 0) { //if buffer has prefix pwd, gives present working directory. 
			pwd();
		}
		else if (hasPrefix(buffer, "cls") == 0) { //clears screen
			int i=100;
			while(i--)
				printf("\n");
		}
		else if ((hasPrefix(buffer, "ls -l") == 0) || hasPrefix(buffer, "ls -color") == 0){
			lsl();
		}
		else if ((hasPrefix(buffer, "ls") == 0) || hasPrefix(buffer, "ls --color") == 0){
			ls();
		}
		else if (hasPrefix(buffer, "sudo apt-get") == 0) { //shows your knowledge 
			printf(KRED "You do not have permissions to install\n"); // prints in laal rang
			printf(KNRM "" KNRM);
		}
		else if (hasPrefix(buffer, "sudo") == 0) { 
			printf(KRED "You do not have superuser access\n");
			printf(KNRM "" KNRM);
		}
		else if (hasPrefix(buffer, "exit") == 0) { //exits the code
			exit(0);
		}
		else {
			buffer[strlen(buffer)-1] = buffer[strlen(buffer)]; 
			// Since fgets stores string with a \n, so we changes second last character to last character, so that buffer can be used to show what command was entered
			printf(KRED "%s: command not found\n", buffer); //shows error in laal rang
			printf(KNRM "" KNRM); // changes color back to aam.
		}
	}
	return 0;
}
