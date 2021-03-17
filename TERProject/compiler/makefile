
prog: parser.cc lexer.cc main.cc
	g++  lexer.cc parser.cc  main.cc   -o analyser



parser.cc:parser.y
	bison parser.y --defines=parser.h -o parser.cc


lexer.cc:lexer.l
	flex++ -o lexer.cc .lexer.l 