#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

static char *do_ls(char *path);
static char *filetype(mode_t mode);

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) {
        do_ls(argv[i]);
    }
    exit(0);
}

static char*
do_ls(char *path)
{
    DIR *d;
    struct dirent *ent;
	struct stat st;
	char *filepath;

    d = opendir(path);          /* (1) */
    if (!d) {
        perror(path);
        exit(1);
    }
	printf("directory: %s\n", path);
    while (ent = readdir(d)) {  /* (2) */
		*filepath = '\0';
		if (strcmp(ent->d_name, ".")==0) continue;
		if (strcmp(ent->d_name, "..")==0) continue;
        strcat(strcat(strcat(filepath, path), "/"), ent->d_name);
        if (lstat(filepath, &st) < 0) {
        	perror(filepath);
        	exit(1);
    	}
		if (filetype(st.st_mode) == "file") printf("%s\n", filepath);
		if (filetype(st.st_mode) == "directory") do_ls(filepath);
    }
    closedir(d);                /* (1') */
}

static char*
filetype(mode_t mode)
{
    if (S_ISREG(mode)) return "file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISCHR(mode)) return "chardev";
    if (S_ISBLK(mode)) return "blockdev";
    if (S_ISFIFO(mode)) return "fifo";
    if (S_ISLNK(mode)) return "symlink";
    if (S_ISSOCK(mode)) return "socket";
    return "unknown";
}
