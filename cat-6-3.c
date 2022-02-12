#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *f);

int
main(int argc, char *argv[])
{
    int i;

    if (argc == 1) {
        do_cat(stdin);
    }
    else {
        for (i = 1; i < argc; i++) {
            FILE *f;

            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            do_cat(f);
            fclose(f);
        }
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
do_cat(FILE *f)
{
    unsigned char buf[BUFFER_SIZE];
    int n;

    for (;;) {
        n = fread(buf, 1, sizeof buf, f);
        if (ferror(f) == 0) fwrite(buf, 1, n, stdout);
		if (n < 1) break;
    }
}
