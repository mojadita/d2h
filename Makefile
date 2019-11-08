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

.PHONY: all clean install

d2h_objs = d2h.o

.for t in $(targets)
toclean += $t $($t_objs)
$t: $($t_deps) $($t_objs)
	$(CC) $(LDFLAGS) -o $@ $($t_objs) $($t_ldflags) $($t_libs)
.endfor
