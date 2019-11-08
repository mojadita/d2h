/* d2h.c -- double to hex to convert ieee752 binary floating
 * point representations of numbers to hexadecimal form or float
 * type.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Nov  8 07:52:45 EET 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

#define EXIT_USAGE		(1)
#define EXIT_FOPEN		(2)

void do_usage(char *progname)
{
	fprintf(stderr,
		"Usage: %1$s [ options ... ] [ file ... ]\n"
		"\n",
		progname);
} /* do usage */

void process(char *fname, FILE *fdesc)
{
} /* process */

int main(int argc, char **argv)
{
	int opt;
	void (*prc)(char *fn, FILE *fd) = process;

	while ((opt = getopt(argc, argv, "?")) != EOF) {
		switch (opt) {
		case '?':
			do_usage(argv[0]);
			exit(EXIT_USAGE);
			break;
		} /* switch */
	} /* while */

	argc -= optind;
	argv += optind;

	if (argc > 0) {
		int i;
		for (i = 0; i < argc; i++) {
			FILE *f = fopen(argv[i], "rt");
			if (!f) {
				fprintf(stderr,
					F("fopen: %s: %s (errno = %d)\n"),
					argv[i], strerror(errno), errno);
				exit(EXIT_FOPEN);
			}
			prc(argv[i], f);
			fclose(f);
		}
	} else {
		prc("<<stdin>>", stdin);
	}

	exit(EXIT_SUCCESS);
} /* main */
