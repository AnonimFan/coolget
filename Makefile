OUTPUT = coolget
FILES_SRC = coolget.c
FILES_OBJ = coolget.o
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I/usr/include -ggdb
LDFLAGS = -L/usr/lib -lcurl
CC = cc -c $(CFLAGS) $(FILES_SRC)
LD = cc -o $(OUTPUT) $(LDFLAGS) $(FILES_OBJ)

all: builder

builder:
	$(CC)
	$(LD)

install:
	sudo cp ./coolget /usr/local/bin

