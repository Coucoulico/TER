%{
#include <stdio.h>
#include <stdbool.h>
#define YYSTYPE int
int yyparse();
int yylex();
int yyerror(char *s);
extern unsigned int lineno;
extern bool error_lexical;
%}

%union {
        long nombre;
        char* texte;
}

//declaration des no terminal comme text
%type<texte>            Prog
%type<texte>			Vesicule 
%type<texte>			Lespece 
%type<texte>			Lrest 
%type<texte>			Lreact 
%type<texte>			Espece
%type<texte>			Reste
%type<texte>			React
%type<texte>			Lident
%type<texte>			Suite
%type<texte>			Taille
%type<texte>			Vitesse
%type<texte>			Init
%type<texte>			React1
%type<texte>			React2
%type<texte>			React3
%type<texte>			React4

//Symboles terminaux qui seront fournis par yylex()

%token ENTIER
%token FLOAT
%token PLUS
%token IMPLIZE
%token ASSIGN 
%token PV
%token V
%token PO
%token PF
%token CO
%token CF
%token IDENT<text>
%token VESICULE
%token ESPECE
%token TAILLE
%token VITESSE
%token INIT

%%

Prog: 			Vesicule Lespece Lrest Lreact 
	;

Lespece:		Espece 
	|			Espece Lespece
	;

Espece:			ESPECE Lident 
	;

Lident:			IDENT Suite {
	printf("%s",$1);
}

Suite:			V Lident
	|			PV
	;

Lrest:			Reste 
	|			Reste Lrest
	;

Vesicule:		VESICULE ASSIGN ENTIER PV
	;

Reste:			Taille 
	| 			Vitesse 
	| 			Init
	; 

Taille:			TAILLE PO IDENT PF ASSIGN ENTIER PV
	;

Vitesse:		VITESSE PO IDENT PF ASSIGN FLOAT PV
	;

Init:			INIT PO IDENT PF ASSIGN ENTIER PV
	;

Lreact:		React
	|			React Lreact
	;

React: 		React1 CO FLOAT CF PV 
	|			React2 CO FLOAT CF PV
	|			React3	CO FLOAT CF PV
	|			React4 CO FLOAT CF PV
	;

React1:			IDENT PLUS IDENT IMPLIZE IDENT 
	;

React2:			IDENT IMPLIZE IDENT
	;

React3:			IDENT IMPLIZE IDENT PLUS IDENT
	;

React4:			IDENT PLUS IDENT IMPLIZE IDENT PLUS IDENT
	;


%%

int yyerror(char *msg) {
    fprintf(stderr, "Erreur de syntaxe a la ligne %d: %s\n", lineno, msg);

    return 0;
}

int main(void) {
    yyparse();
    return 0;
}
