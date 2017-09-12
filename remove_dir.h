#define _GNU_SOURCE // to avoid "implicit declaration of function `asprintf'"
int remove_directory(char *path) {
	DIR *d = opendir(path); //opens the directory of the given argument
	size_t path_len = strlen(path);
	int r = -1;
	int count;
	struct dirent **files; //declares a structure of dirent
	int file_select();
	if (getcwd(pathname, sizeof(pathname)) == 0 ) { //stores current path to pathname
	  printf("Error getting pathname");
	}
	if (d) {  //if the argument directory exists then...
		const struct dirent *p; //initialize structure of dirent
		r = 0; //sets r=0
		while (!r && (p = readdir(d))) { // readdir is defined in the header <dirent.h>, represents a directory stream.
			int r2 = -1;
			char *buf;
			size_t len;

		  	/* Skip the names "." and ".." as we don't want to recurse on them. */
			if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
				continue;
			}
			len = path_len + strlen(p->d_name) + 2; //initializes the length to be given to the name
			buf = malloc(len); //alocates the memory len to buf
			if (buf) { //if buff is not null
				struct stat statbuf; 
				snprintf(buf, len, "%s/%s", path, p->d_name);
				if (!stat(buf, &statbuf)) { 
					if (S_ISDIR(statbuf.st_mode)) { //if the directory exists and we have write access to it then..
						r2 = remove_directory(buf); //remove the directory whose path is in buffer
					}
					else { //else..
						r2 = unlink(buf); //clear buffer
					}
				}
				free(buf); //free the memory allocated to buffer
			}
				r = r2;
		}
		closedir(d); //close the directory initiallly opened at d
	}
	if (!r) { //if false
		r = rmdir(path); //removes the directory
	}
	return r;
}
