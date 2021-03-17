%{
#include "parser.h"
using namespace std;
#include <iostream>

%}
%option noyywrap
blanks		[ \t]+
line        [\n]+
entier      [0-9]+
float 		[0-9]+.[0-9]+
plus        \+
implize		\-\>
assign		\=
pv		    \;
v			\,
po			\(
pf 			\)
co			\[
cf			\]
ident 		[a-zA-Z][a-zA-Z0-9]*
comment		\/\/.*


%%
{line} 			{ }

{comment}      	{}

"vesicule"		{return (VESICULE);}

"espece"		{return (ESPECE);}

"taille"		{return (TAILLE);}

"vitesse"		{return (VITESSE);}

"init"			{return (INIT);}

{entier}    	{ 
					yylval.ival = atoi(yytext); return(ENTIER); 
				}

{plus}      	{ return(PLUS); }

{float}      	{ 
				  	yylval.fval = atof(yytext);return(FLOAT); 
				}

{implize}    	{  return(IMPLIZE); }

{assign}    	{  return(ASSIGN); }

{pv}         	{  return(PV); }

{v}    			{  return(V); }

{po}      		{  return(PO); }

{pf}      		{  return(PF); }

{co}    		{  return(CO); }

{cf}    		{  return(CF); }

{ident}         {  yylval.texte = strdup(yytext); return(IDENT);  }



%%
