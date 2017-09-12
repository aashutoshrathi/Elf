#define _GNU_SOURCE // to avoid "implicit declaration of function `asprintf'"
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#ifdef HAVE_ST_BIRTHTIME
#define birthtime(x) x.st_birthtime
#else
#define birthtime(x) x.st_ctime
#endif
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
void lsl() {
	int count,i,j,k=0;
	struct dirent **files;
	struct stat fileStat;
	int file_selectl();
	
	if (getcwd(pathname, sizeof(pathname)) == 0 ) {
		printf("Error getting path\n");
	}
		
	//for getting parent directory name
	char *user;
	struct passwd *p;
 	while((p = getpwent())) {
		user=p->pw_name;
  	}
  	printf("user -%s\n",user);
	count = scandir(pathname, &files, file_selectl, alphasort);
	if (count <= 0)	{
		printf("No files in this directory\n");
	}
  	//for ls -l(parent directory and creation time not added) moe like ls -g
	for (i=1;i<count-1;i++) {
		if(files[i-1]->d_name[0]!='.') {
	  		stat(files[i-1]->d_name, &fileStat);
	  		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
			printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
			printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
			printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
			printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
			printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
			//prints Owner
			printf("\t%s", user);
			//prints file size
			int length=files[i-1]->d_reclen/32;
			if(files[i-1]->d_reclen<32 )
				printf("\t%d  \t",length+1);
			else if(files[i-1]->d_reclen>32)
				printf("\t%d  \t",length+1);
			else
				printf("\t%d  \t",1);
			
			off_t  a=fileStat.st_size;
			printf("%d\t", a);
			printf("%i\t",birthtime(fileStat) );
				
			//checkl for directory files    
			if(checkl(files[i-1]->d_name)==1) {
				printf("%s%s",KBLU,BOLD);  
			}
			//checkl for executable files
			else if(isExecutablel(files[i-1]->d_name)==1) {
				printf("%s%s",KGRN,BOLD);
			}    
			//checkl for linked file
			else if(checkl(files[i-1]->d_name)==2) {
			   printf("%s%s",KCYN,BOLD);
			} 
			//checkl for device file
			else if(checkl(files[i-1]->d_name)==3) {
				printf("%s%s%s",KYEL,BOLD,BGBLACK);
			} 
			//checkl for graphic or image file
			else if(checkl_ext(files[i-1]->d_name)==1) {
			   printf("%s%s",KMAG,BOLD);
			}
			//checkl for archive file
			else if(checkl_ext(files[i-1]->d_name)==2) {
				printf("%s%s",KRED,BOLD);
			}
			printf("%s  \t",files[i-1]->d_name);
			printf("\n");
			printf("%s",KNRM);
		}
	}
}


int file_selectl(struct direct   *entry) {
	if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0))
   		return (FALSE);
 	else
   		return (TRUE);
}
int isExecutablel(const char *name) {
	struct stat sb;
	if (stat(name, &sb) == 0 && sb.st_mode & S_IXUSR) 
		return 1;
	else  
		return 0;
}
int checkl(const char *name) {
	struct stat buf;
	int x;
	x = lstat(name, &buf);
	switch (buf.st_mode & S_IFMT) {
	case S_IFDIR: return 1;                       //checkl for directory file 
	case S_IFLNK: return 2;                       //checkl for a link file
	case S_IFBLK: return 3;                       //checkl for Block Device
	case S_IFCHR: return 3;                       //checkl for Character Device  
	return 0;
	}      
}    
int checkl_ext(const char *name) {
	char *extension, *n;
	n=strdup(name);
	extension=strrchr(n,'.');
	if (extension==NULL) {
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
