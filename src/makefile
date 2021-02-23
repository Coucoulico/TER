prog: parser.o flex_parser.o
	gcc -Wall parser.o flex_parser.o -o analyser

parser.o:parser.c
	gcc -c -Wall parser.c

parser.c:parser.y
	bison parser.y --defines=parser.h -o parser.c

flex_parser.o : flex_parser.c
	gcc -c -Wall flex_parser.c

flex_parser.c:parser.l
	flex -o flex_parser.c parser.l






