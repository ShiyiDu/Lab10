CC=gcc
CFLAGS=-lWarn -pedantic

tempread: tempread.o
	$(CC) tempread.o -L. -lcurl -o tempread

tempread.o:	tempread.c
	$(CC) $(CFLAGS) -c -ansi $<

clean:
	rm tempread *.o