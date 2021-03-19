%{
#include <cstdio>
#include <iostream>
#include <string>

#include "../model/headers/vesicule.h"
#include "../model/headers/espece.h"
#include "../model/headers/reaction.h"
#include "../model/headers/instance.h"


instance inst;
int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(char *s);
%}



%union {
    int ival;
    float fval;
    char *texte;
}

%type<texte>            Prog
%type<texte>            Vesicule 
%type<texte>            Lespece 
%type<texte>            Lrest 
%type<texte>            Lreact 
%type<texte>            Espece
%type<texte>            Reste
%type<texte>            React
%type<texte>            Lident
%type<texte>            Suite
%type<texte>            Taille
%type<texte>            Vitesse
%type<texte>            Init
%type<texte>            React0
%type<texte>            React1
%type<texte>            React2
%type<texte>            React3


//Symboles terminaux qui seront fournis par yylex()

%token <ival> ENTIER
%token <fval> FLOAT
%token PLUS
%token IMPLIZE
%token ASSIGN 
%token PV
%token V
%token PO
%token PF
%token CO
%token CF
%token <texte> IDENT
%token VESICULE
%token ESPECE
%token TAILLE
%token VITESSE
%token INIT


%%
Prog:           Vesicule Lespece Lrest Lreact  
    ;

Lespece:        Espece 
    |           Espece Lespece
    ;

Espece:         ESPECE Lident  
    ;


Lident:         IDENT Suite {
                              espece e($1);
                              inst.addEspece(e);  
                            }
;
   


Suite:          V IDENT Suite {
                              espece e($2);
                              inst.addEspece(e);  
                            }   
    |           PV          
    ;

Lrest:          Reste 
    |           Reste Lrest
    ;

Vesicule:       VESICULE ASSIGN ENTIER PV {
                 vesicule v($3);
                 inst.setVesicule(v);
                }
    ;


Reste:          Taille 
    |           Vitesse 
    |           Init
    ; 

Taille:         TAILLE PO IDENT PF ASSIGN ENTIER PV {
                inst.setTaille($3,$6);
                }
    ;


Vitesse:        VITESSE PO IDENT PF ASSIGN FLOAT PV{
                        inst.setVitesse($3,$6);
                        }
    ;


Init:           INIT PO IDENT PF ASSIGN ENTIER PV{
                inst.setNb($3,$6);
} 
    ;

Lreact:     React
    |       React Lreact
    ;

React:      Reacttype      
    ;
Reacttype:  React0
    |       React1
    |       React2
    |       React3
    ;


React0:         IDENT IMPLIZE IDENT CO FLOAT CF PV {
                reaction r($5,0);
                r.S1 = inst.getEspece($1);
                r.setProd(inst.getEspece($3),1);
                inst.addReaction(r);

                
}          
    ;

React1:         IDENT PLUS IDENT IMPLIZE IDENT CO FLOAT CF PV{
                reaction r($7,1);
                r.S1=inst.getEspece($1);
                r.S2=inst.getEspece($3);
                espece* p1=inst.getEspece($5);
                r.setProd(p1,1);
                inst.addReaction(r);

}
;

React2:         IDENT IMPLIZE IDENT PLUS IDENT CO FLOAT CF PV {
                reaction r($7,2);
                espece* s1=inst.getEspece($1);
                r.S1=s1;
                espece* p1=inst.getEspece($3);
                r.setProd(p1,1);
                espece* p2=inst.getEspece($5);
                r.setProd(p2,2);
                inst.addReaction(r);
                
}  
    ;



React3:         IDENT PLUS IDENT IMPLIZE IDENT PLUS IDENT CO FLOAT CF PV {
                reaction r($9,3);
                espece* s1=inst.getEspece($1);
                r.S1=s1;
                espece* s2=inst.getEspece($3);
                r.S2=s2;
                espece* p1=inst.getEspece($5);
                r.setProd(p1,1);
                espece* p2=inst.getEspece($7);
                r.setProd(p2,2);
                inst.addReaction(r);

                
}
    ;

%%


void yyerror(char *s) {
    std::cout << "Parse error: " << s << std::endl;
    exit(-1);
}


