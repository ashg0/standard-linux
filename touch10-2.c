/*
    Simple touch(1) command.
    This program does not create file, just update atime/mtime.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <utime.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;
	int fd;

    fd = open(argv[1], O_RDONLY);
	printf("open %s\n", argv[1]);
    if (fd < 0) die(argv[1]);
	/*
	printf("rename to %s\n", "hogehoge");
    if (rename(argv[1], "hogehoge") < 0) {
        perror(argv[1]);
        exit(1);
    }
	*/
	/*
	printf("rename hage to %s\n", "hagehage");
    if (rename("hage", "hagehage") < 0) {
        perror(argv[1]);
        exit(1);
    }
	*/
	printf("unlink %s\n", argv[1]);
    if (unlink(argv[1]) < 0) {
        perror(argv[1]);
        exit(1);
    }
	if (close(fd) < 0) die(argv[1]);
    exit(0);
}

static void
die(const char *s)
{
    fprintf(stderr, "errno: %d, string: %s\n", errno, strerror(errno));
    perror(s);
    exit(1);
}
