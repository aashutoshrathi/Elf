#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
   
 int main (int *argc,char **argv){
    	  int ret;
    	 
    	    if(mkdir("/home/giant/Desktop/abhi1",S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==-1)
    	     {
    	     	printf("Cannot create Directory,Given path is incorrect");
			 }
    	    else {
    	 			ret = mkdir("/home/giant/Desktop/abhi1",S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);   	
		      	} 
    	    
    	  return 0;
	}
	
	
	
	/*S_IRWXU is the bitwise inclusive OR of S_IRUSR,S_IWUSR,S_IXUSR.
	  S_IRUSR = Read permission ,owner.
	  S_IWUSR = Write permission ,owner.
	  S_IXUSR = Execute/Search  permission ,owner.
	  
	  
	  S_IRWXG is the bitwise inclusive OR of S_IRGRP,S_IXGRP,S_IXGRP.
	  S_IRGRP = Read permission ,group.
	  S_IWGRP = Write permission ,group.
	  S_IXGRP = EXecute/Search permission ,group.
	
	  
	  S_IRWXO is bitwise inclusive OR of S_IROTH,S_IWOTH,S_IXOTH.
	  S_IROTH = Read permission, others.
	  S_IWOTH = Write permission ,others.
	  S_IXOTH = Execute/Search permission ,others.*/
	  
