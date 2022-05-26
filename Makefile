CC=gcc
AR=ar

EXTRA_CFLAGS=
CFLAGS=-O3 -Wall -m64 -fPIC -I include

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