OUTPUT = coolget
FILES_SRC = $(wildcard **.c)
FILES_OBJ = $(wildcard **.o)
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I/usr/include
LDFLAGS = -L/usr/lib -lcurl
CC = cc -c $(CFLAGS) $(FILES_SRC)
LD = cc -o $(OUTPUT) $(LDFLAGS) $(FILES_OBJ)

all: builder

builder:
	$(CC)
	$(LD)

