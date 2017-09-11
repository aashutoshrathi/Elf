#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pwd(void);

int main() {
	char arg[1024];
	while (strcmp(arg,"exit")!=0){	
		printf("myshell$ ");
		scanf("%s", arg);
		switch (arg[0])
		{
			case 'p':
			pwd();
		}
	}
	exit(0);
}

int pwd() {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return 0;
}