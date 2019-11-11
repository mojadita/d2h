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

toclean += d2h $(d2h_objs)
d2h_srcs += $(d2h_objs:.o=.c)
depends += $(d2h_srcs)
d2h: $(d2h_deps) $(d2h_objs)
	$(CC) $(LDFLAGS) -o $@ $(d2h_objs) $(d2h_ldflags) $(d2h_libs)
