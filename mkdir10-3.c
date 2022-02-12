#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void do_mkdir(char *path, mode_t mode);

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) {
		/*
        if (mkdir(argv[i], 0777) < 0) {
            perror(argv[i]);
            exit(1);
        }
		*/
		do_mkdir(argv[i], 0777);
    }
    exit(0);
}

void do_mkdir(char *path, mode_t mode){
	if (mkdir(path, mode) < 0) {
		if (errno==ENOENT) {
			int i;
			for(i=strlen(path); i>-1; --i){
				if (path[i] == '/') break;
			}
			/* first implment
			//printf("i: %d\n", i);
			char buf[i+1];
			for(int j=0; j<i; j++){
				buf[j] = path[j];
			}
			buf[i] = '\0';
			do_mkdir(buf, mode);
			*/
			path[i] = '\0';
			do_mkdir(path, mode);
			path[i] = '/';
			if (mkdir(path, mode) < 0) {
				perror(path);
				exit(1);
			}
			printf("made: %s\n", path);
		}
	}
	return;
}
