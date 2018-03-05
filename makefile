CC=gcc
CFLAGS=-O3 -fPIC -Werror -Wall -fno-builtin

all: check

default: check

clean:
	rm -rf *.o Data.txt cache_measure mem_aprox

mem_aprox: mem_aprox.o
	$(CC) $(CFLAGS) $< -o $@

cache_measure: cache_measure.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

ramTest: clean mem_aprox
	./mem_aprox

cacheTest: clean cache_measure
	./cache_measure

dist:
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar
