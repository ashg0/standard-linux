/*
    tail -- Shows last 10 lines of files (with line length limitation)
*/

#include <stdio.h>
#include <stdlib.h>

//#define N_LINES 10
#define MAX_LINE_LENGTH 1024

static void tail(FILE *f, long num);

int
main(int argc, char *argv[])
{
	char *p;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s line_number < infile\n", argv[0]);
        exit(1);
    }
    tail(stdin, strtol(argv[1], &p, 10));
    exit(0);
}


#define RING_BUFFER_INC(idx) do { \
    idx++; \
    if (idx >= num) { \
        idx = 0; \
    } \
} while (0)

static void
tail(FILE *f, long num)
{
    long curr = 0;
    long n_read_lines = 0;
	char** ring_buffer = (char**)malloc(num * sizeof(char*));
	for (int i=0; i < num; i++)
		ring_buffer[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));

    // Read all lines into ring buffer
    while (fgets(ring_buffer[curr], MAX_LINE_LENGTH, f)) {
        RING_BUFFER_INC(curr);
        n_read_lines++;
    }

    // Rewind ring buffer
    if (n_read_lines < num) {
        curr = 0;
    }

    // Flush ring buffer
    int n;
    for (n = num; n > 0 && n_read_lines; n--, n_read_lines--) {
        printf("%s", ring_buffer[curr]);
        RING_BUFFER_INC(curr);
    }
	free(ring_buffer);
}
