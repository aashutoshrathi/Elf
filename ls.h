#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

extern  int alphasort();
char pathname[MAXPATHLEN];

int file_select(struct direct *entry) {
	return !((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0));
}

int isExecutable(const char *name) {
	struct stat sb;
	return (stat(name, &sb) == 0 && sb.st_mode & S_IXUSR);
}

int check(const char *name) {    
 	struct stat buf;  
 	int x;
 	x = lstat(name, &buf);
 	switch (buf.st_mode & S_IFMT) {
		case S_IFDIR: return 1;                       //Check for directory file 
	 	case S_IFLNK: return 2;                       //Check for a link file
	 	case S_IFBLK: return 3;                       //Check for Block Device
	 	case S_IFCHR: return 3;                       //Check for Character Device  
	 	return 0;
	}      
}
  
int check_ext(const char *name) {
  	char *extension, *n;
  	n = strdup(name);
  	extension = strrchr(n, ".");
  	if(extension==NULL) {
  		return 0;
  	}
  	extension++;
  	char i1[]="jpeg", i2[]="gif", i3[]="bmp", i4[]="tiff", i5[]="png", i6[]="jpg";
  	char a1[]="a", a2[]="ar", a3[]="sbx", a4[]="cpio", a5[]="tar", a6[]="shar", a7[]="LBR", a8[]="iso", a9[]="lbr", a10[]="mar";
  
 	if(strncmp(extension,i1,4)==0 || strncmp(extension,i2,3)==0 || strncmp(extension,i3,3)==0 || strncmp(extension,i4,4)==0 || strncmp(extension,i5,3)==0 || strncmp(extension,i6,3)==0) {
   		return 1;
 	}
	else if(strncmp(extension,a1,1)==0 || strncmp(extension,a2,2)==0 || strncmp(extension,a3,3)==0 || strncmp(extension,a4,4)==0 || strncmp(extension,a5,3)==0 || strncmp(extension,a6,4)==0 || strncmp(extension,a7,3)==0 || strncmp(extension,a8,3)==0 || strncmp(extension,a9,3)==0 || strncmp(extension,a10,3)==0) { 
  		return 2;
	}
	else
		return 0;
}    

int ls() {
	int count,i;
	struct dirent **files;
	int file_select();
	if (getcwd(pathname, sizeof(pathname)) == 0 ) {
	  printf("Error getting pathname");
	}
 	count = scandir(pathname, &files, file_select, alphasort);
  	if (count <= 0) {         
	 printf("No files in this directory");
    }
    else {
    	int Max_FnLen=strlen(files[0]->d_name);
	   	for (i=0; i<count; i++) {
			if(strlen(files[i]->d_name)>Max_FnLen) { 
		  		Max_FnLen=strlen(files[i]->d_name);
			}
	   	}
		for (i=1; i<count+1; i++) { 
			 //check for directory files    
			if(check(files[i-1]->d_name)==1) {
				printf("%s%s",KBLU,BOLD);  
			}
			//check for executable files
			else if(isExecutable(files[i-1]->d_name)==1) {
			   printf("%s%s",KGRN,BOLD);
			}    
			//check for linked file
			else if(check(files[i-1]->d_name)==2) {
			   printf("%s%s",KCYN,BOLD);
			}
			//check for device file
			else if(check(files[i-1]->d_name)==3) {
			   printf("%s%s%s",KYEL,BOLD,BGBLACK);
			} 
			//check for graphic or image file
			else if(check_ext(files[i-1]->d_name)==1) {
			   printf("%s%s", KMAG, BOLD);
			} 
			//check for archive file
			else if(check_ext(files[i-1]->d_name)==2) {
			   printf("%s%s", KRED, BOLD);
			} 
			char *a;
			asprintf(&a, "%%-%ds  ", Max_FnLen);
			printf(a, files[i-1]->d_name);
			free(a); 
			printf("%s", KNRM);
			if ((i % (180/Max_FnLen)) == 0) 
				printf("\n");
	   }
   }	
	printf("\n");    
}

