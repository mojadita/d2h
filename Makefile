# Makefile --- makefile for d2h program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Nov  8 08:03:06 EET 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

RM ?= rm -f

targets = d2h
toclean = $(targets)

all: $(targets)
clean:
	$(RM) $(toclean)
depend:
	mkdep $(depends)

.PHONY: all clean install depend

d2h_objs = d2h.o

.for t in $(targets)
toclean += $t $($t_objs)
$t_srcs += $($t_objs:.o=.c)
depends += $($t_srcs)
$t: $($t_deps) $($t_objs)
	$(CC) $(LDFLAGS) -o $@ $($t_objs) $($t_ldflags) $($t_libs)
.endfor
