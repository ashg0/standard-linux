/*
    cat3.c -- read stdin if no argument given.

    Copyright (c) 2017 Minero Aoki

    This program is free software.
    Redistribution and use in source and binary forms,
    with or without modification, are permitted.
*/

#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_cat(FILE *f, int tflag, int lflag);

static struct option longopts[] = {
    {"tab", no_argument, NULL, 't'},
    {"line",  no_argument, NULL, 'l'},
    {0, 0, 0, 0}
};

int
main(int argc, char *argv[])
{
    int i;
	int opt;
	int tflag = 0;
	int lflag = 0;

    while ((opt = getopt_long(argc, argv, "tl", longopts, NULL)) != -1) {
        switch (opt) {
        case 't':         /* (4) */
            tflag = 1;
            break;
        case 'l':         /* (5) */
			lflag = 1;
            break;
        case '?':         /* (6) */
            fprintf(stderr, "Usage: %s [-t] [-l] [FILE ...]\n", argv[0]);
            exit(1);
        }
    }

    if (argc == optind) {
        do_cat(stdin, tflag, lflag);
    }
    else {
		int i;
        for (i = optind; i < argc; i++) {
            FILE *f;

            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            do_cat(f, tflag, lflag);
            fclose(f);
        }
    }
    exit(0);
}

static void
do_cat(FILE *f, int tflag, int lflag)
{
    int c;
	char *buf;

    while ((c = fgetc(f)) != EOF) {
		if (c=='\t' && tflag) {
			if (fputs("\\t", stdout) < 0) exit(1);
		} else if (c=='\n' && lflag) {
			if (fputs("$\n", stdout) < 0) exit(1);
		} else {
			if (putchar(c) < 0) exit(1);
		}
    }
}
