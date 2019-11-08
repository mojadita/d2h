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

#define EXIT_USAGE		(1)

void do_usage(char *progname)
{
	fprintf(stderr,
		"Usage: %1$s [ options ... ] [ file ... ]\n"
		"\n",
		progname);
}

int main(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "?")) != EOF) {
		switch (opt) {
		case '?':
			do_usage(argv[0]);
			exit(EXIT_USAGE);
			break;
		} /* switch */
	} /* while */

	exit(EXIT_SUCCESS);
} /* main */
