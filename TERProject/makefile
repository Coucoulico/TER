
prog:lexer.cc parser.cc
	g++ -std=c++11 -mmacosx-version-min=10.11 compiler/lexer.cc compiler/parser.cc model/classes/*.cc  main.cc   -o simulateur


parser.cc:compiler/parser.y
	bison compiler/parser.y --defines=compiler/parser.h -o compiler/parser.cc


lexer.cc:compiler/lexer.l 
	lex -o compiler/lexer.cc compiler/lexer.l 