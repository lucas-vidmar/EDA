
all: main parser
	gcc -o terminal-parser main.o parser.o

main: main.c
	gcc -c main.c

parser: parser.c parser.h
	gcc -c parser.c -o parser.o

clean:
	rm -f terminal-parser *.o