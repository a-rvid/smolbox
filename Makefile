CC = gcc
CFLAGS = -Wall -Oz -s -fno-ident -fno-asynchronous-unwind-tables -DNDEBUG -static -std=c23

smolbox:
	$(CC) $(CFLAGS) src/main.c -o smolbox

clean:
	rm -f smolbox
