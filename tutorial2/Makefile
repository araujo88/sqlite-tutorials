CC=gcc
CFLAGS=-g -Wall -std=c99
CCLIBS=-lsqlite3
BINS=version2

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(CCLIBS)

clean:
	rm -rf *.dSYM $(BINS)