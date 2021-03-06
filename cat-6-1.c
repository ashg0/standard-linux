/*
    cat3.c -- read stdin if no argument given.

    Copyright (c) 2017 Minero Aoki

    This program is free software.
    Redistribution and use in source and binary forms,
    with or without modification, are permitted.
*/

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

static void
do_cat(FILE *f)
{
    int c;
	char *buf;

    while ((c = fgetc(f)) != EOF) {
		if (c=='\t') {
			if (fputs("\\t", stdout) < 0) exit(1);
		} else if (c=='\n') {
			if (fputs("$\n", stdout) < 0) exit(1);
		} else {
			if (putchar(c) < 0) exit(1);
		}
    }
}
