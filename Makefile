CC = gcc
CFLAGS = -g -Wall

OBJECTS = symbol.o lexer.o parser.o

main: $(OBJECTS) main.c
	$(CC) $(CFLAGS) -o $@ $^

symbol.o: symbol.c symbol.h

parser.o: parser.c parser.h

lexer.o: lexer.c lexer.h

.PHONY : clean
clean:
	rm -rf *.o main

