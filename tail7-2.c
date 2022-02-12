#include <stdio.h>
#include <stdlib.h>

static void do_tail(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }
    int i;
    for (i = 1; i < argc; i++) {
        do_tail(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 8

static void
do_tail(const char *path)
{
    unsigned char buf[BUFFER_SIZE];
    FILE *f = fopen(path, "r");
    if (!f) die(path);
	//int pos = BUFFER_SIZE;
	if (fseek(f, 0, SEEK_END) != 0) die("first fseek");
	int nl = 0;
	int c;
	//int c = fgetc(f);
	//if (c!='\n') nl++;
    for (;;) {
		if (fseek(f, -2, SEEK_CUR) != 0) die("fseek");
        c = fgetc(f);
		if (c == '\n') nl++;
        if (ferror(f)) die(path);
		if(nl==5) {
			break;
		}
        //size_t n_written = fwrite(buf, 1, n_read, stdout);
        //if (n_written < n_read) die(path);
        //if (n_read < sizeof buf) break;
    }
    while ((c = fgetc(f)) != EOF) {
        if (putchar(c) < 0) exit(1);
    }
    if (fclose(f) != 0) die(path);
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
