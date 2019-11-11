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

#include "d2h.h"

struct profile {
	char *name;
	int flags;
	void (*print)(const struct profile *prof, const char*buff, size_t buflen);
	size_t (*decode)(const struct profile *prof,
					const char *line, char **pbuf);
};

int config_flags;

static void
do_usage(char *progname)
{
	fprintf(stderr,
		"Usage: %1$s [ options ... ] [ file ... ]\n"
		"Options:\n"
		"  -m mode.  The possible modes are strings in the set \n"
		"     {\"flt-le\", \"flt-be\", \"dbl-le\", \"dbl-be\"} meaning\n"
		"     dbl to use double numbers and flt to use float\n"
		"     number.  'le' means little-endian while 'be' means\n"
		"     big-endian numbers.  Default is \"flt-be\".\n"
		"  -v Be verbose.  Program prints to 'stderr' input filenames,\n"
		"     as they are processed.\n"
		"  -?, -h\n"
		"     Help.  Shows this help screen.\n"
		"\n",
		progname);
} /* do usage */

static void
print_le(const struct profile *prof, const char *b, size_t sz)
{
	char *sep = "";
	while(sz--) {
		printf("%s%02hhx", sep, *b++);
		sep = " ";
	}
	puts("");
}

static void
print_be(const struct profile *prof, const char *b, size_t sz)
{
	char *sep = "";
	b += sz;
	while(sz--) {
		printf("%s%02hhx", sep, *--b);
		sep = " ";
	}
	puts("");
}

static size_t
decode_le(const struct profile *prof, const char *line, char **b)
{
	size_t res = sscanf(line,
		"%hhx%hhx%hhx%hhx%hhx%hhx%hhx%hhx",
		*b+0, *b+1, *b+2, *b+3,
		*b+4, *b+5, *b+6, *b+7);
    return res;
}

static size_t
decode_be(const struct profile *prof, const char *line, char **b)
{
	size_t res = sscanf(line,
		"%hhx%hhx%hhx%hhx%hhx%hhx%hhx%hhx",
		*b+7, *b+6, *b+5, *b+4,
		*b+3, *b+2, *b+1, *b+0);
	size_t diff = sizeof(double) - res;
	if (diff) {
		*b +=  diff;
	}
    return res;
} /* decode_rev_end */

static size_t
decode(const struct profile *prof, const char *line, char **b)
{
	size_t res = prof->decode(prof, line, b);
	switch(res) {
	case 0: case 1: /* a single number, or no number at all.
					 * Can be a floating point */
		if (prof->flags & FLAG_FLOAT) {
			res = sscanf(line, "%g", (float *)*b);
			return res == 1 ? FLAG_FLOAT : -1;
		} else {
			res = sscanf(line, "%lg", (double *)*b);
			return res == 1 ? 0 : -1;
		}
	case sizeof(float): case sizeof(double):
		return res;
	}
	return -1;
} /* decode */
	
static void
process(const struct profile *prof, char *fname, FILE *fdesc)
{
	if (config_flags & FLAG_VERBOSE)
		fprintf(stderr,
			F("%s(mode=%s):\n"),
			fname, prof->name);

	char line[1024];
	int line_number = 0;

	while(fgets(line, sizeof line, fdesc)) {
		char buffer[sizeof(double)];
		char *p = buffer;
		switch(decode(prof, line, &p)) {
		case sizeof(double): /* decode a double */
			printf(FMT_DBL, *(double*)p); break;
		case sizeof(float): /* decode a float */
			printf(FMT_FLT, *(float *)p); break;
		case 0: /* encode a double */
			prof->print(prof, p, sizeof(double)); break;
		case FLAG_FLOAT: /* encode a float */
			prof->print(prof, p, sizeof(float)); break;
		case -1: /* error decoding */
			fprintf(stderr,
				F("%s:%d: error decoding: %s"),
				fname, line_number, line);
			break;
		} /* switch */
	} /* while */
} /* process */

static const struct profile tab_modes[] = {
    { .name		= MODE_DOUBLE_LE,
      .flags	= 0,
      .print	= print_le,
      .decode	= decode_le,
    }, {
      .name		= MODE_DOUBLE_BE,
      .flags	= 0,
      .print	= print_be,
      .decode	= decode_be,
    }, {
      .name		= MODE_FLOAT_LE,
      .flags	= FLAG_FLOAT,
      .print	= print_le,
      .decode	= decode_le,
    }, {
      .name		= MODE_FLOAT_BE,
      .flags	= FLAG_FLOAT,
      .print	= print_be,
      .decode	= decode_be,
    },
    { .name = NULL, },
};

const struct profile *lookup_mode(char *mode_name)
{
    const struct profile *mode;
    for (mode = tab_modes; mode->name; mode++)
        if (!strcmp(mode_name, mode->name))
            break;
    if (!mode->name)
        fprintf(stderr,
                F("mode %s not found, defaulting to %s.\n"),
                mode_name, tab_modes->name);
    return mode->name
		? mode
		: lookup_mode(DEFAULT_MODE);
}

int main(int argc, char **argv)
{
	int opt;
	char *mode = DEFAULT_MODE;

	while ((opt = getopt(argc, argv, "?hm:v")) != EOF) {
		switch (opt) {
		case '?': case 'h':
			do_usage(argv[0]); exit(EXIT_USAGE); 	   break;
        case 'm': mode = optarg;                       break;
		case 'v': config_flags |= FLAG_VERBOSE; 	   break;
		} /* switch */
	} /* while */

	argc -= optind;
	argv += optind;

    const struct profile *prof = lookup_mode(mode);

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
			process(prof, argv[i], f);
			fclose(f);
		}
	} else {
		process(prof, "<<stdin>>", stdin);
	}

	exit(EXIT_SUCCESS);
} /* main */
