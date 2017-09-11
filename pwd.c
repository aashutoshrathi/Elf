int pwd() {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "%s\n", cwd);
	else
		perror("Null Pointer Error");
	return 0;
}

