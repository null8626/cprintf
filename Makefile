CC=gcc
AR=ar

EXTRA_CFLAGS=
CFLAGS=-O3 -DCPRINTF_BUILDING -Wall -fPIC $(EXTRA_CFLAGS)

ifeq ($(CC),clang)
AR=llvm-ar
endif

ifeq ($(SHARED),yes)
LIB=libcprintf.so
_EXTRA_LIB_CFLAGS=$(LIB) -Wl,-rpath=.
else
LIB=libcprintf.a
_EXTRA_LIB_CFLAGS=-L. -lcprintf
endif

.PHONY: $(LIB)

libcprintf.so: cprintf.o
	$(CC) -shared -o $@ $^

libcprintf.a: cprintf.o
	$(AR) rcs -o $@ $^

cprintf.o: cprintf.c
	$(CC) $(CFLAGS) -c $< -o $@