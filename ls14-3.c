#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

static void do_ls(char *path);

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

static void
do_ls(char *path)
{
    DIR *d;
    struct dirent *ent;
    struct stat st;
    struct passwd *pw;
	char filepath[1024];

    d = opendir(path);          /* (1) */
    if (!d) {
        perror(path);
        exit(1);
    }
    while (ent = readdir(d)) {  /* (2) */
		filepath[0] = '\0';
		strcat(strcat(strcat(filepath, path), "/"), ent->d_name);
    	if (lstat(filepath, &st) < 0) {
        	perror(filepath);
        	exit(1);
    	}
		pw = getpwuid(st.st_uid);
    	if (!pw) {
        	perror(filepath);
        	exit(1);
    	}
        printf("name: %s, owner: %s, last mod: %s", ent->d_name, pw->pw_name, ctime(&st.st_mtime));
    }
    closedir(d);                /* (1') */
}


