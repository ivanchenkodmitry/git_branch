#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

#define CWD_LEN 1000
#define ERROR(str) {fprintf(stderr,str);exit(1);}


int main(int argc, char *argv[])
{
	FILE *head_file;
	char head_str[CWD_LEN];
	char cwd[CWD_LEN];
	if (getcwd(cwd, CWD_LEN) == NULL)
		ERROR("error: current pathname is too long\n");

	char *dirname_ptr = cwd;
	int dirname_length;
	while((dirname_length = strlen(dirname_ptr)) > 1) {
		strcat(dirname_ptr, "/.git/HEAD");
		if((head_file = fopen(dirname_ptr, "r")) != NULL) {
			if (!fread(head_str, sizeof(char), CWD_LEN , head_file))
				ERROR("HEAD is empty");
			char *ptr = strrchr(head_str,'/');
			if (ptr != NULL) {
				printf("%s",ptr + 1);
				break;
			}
			fclose(head_file);
		}
		dirname_ptr[dirname_length] = '\0';
		dirname_ptr = dirname(dirname_ptr);
	}

	return 0; 
}

