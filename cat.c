#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void do_cat(const char *path);
static void stdin_cat();
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
		stdin_cat();
/*
        fprintf(stderr, "errno: %d, string: %s\n", errno, strerror(errno));
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
*/
    }
    for (i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for (;;) {
        n = read(fd, buf, sizeof buf);
        if (n < 0) die(path);
        if (n == 0) break;
        if (write(STDOUT_FILENO, buf, n) < 0) die(path);
    }
    if (close(fd) < 0) die(path);
}

static void
stdin_cat()
{
	int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;
	const char *s;
	s = "stdin_cat";

    //fd = open(path, O_RDONLY);
    //if (fd < 0) die(s);
    for (;;) {
        n = read(STDIN_FILENO, buf, sizeof buf);
        if (n < 0) die(s);
        if (n == 0) break;
        if (write(STDOUT_FILENO, buf, n) < 0) die(s);
    }
    if (close(fd) < 0) die(s);
}
	
static void
die(const char *s)
{
    fprintf(stderr, "errno: %d, string: %s\n", errno, strerror(errno));
    perror(s);
    exit(1);
}
