#include "compiler/parser.h"
#include <iostream>
#include "model/headers/vesicule.h"
#include "model/headers/espece.h"
#include "model/headers/reaction.h"

#include "model/headers/instance.h"
#include "model/headers/solver.h"
extern "C" int yyparse();
extern "C" FILE *yyin;
extern instance inst;

int main(int argc, char *argv[]) {
    if (argc!= 2) {
        std::cout <<"Usage: <command> filename"<<std::endl;
        return 1;
    }

    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        std::cout << "I can't open "<<argv[1]<< std::endl;
        return -1;
    }

    yyin = myfile;

    do {
        yyparse();
    } while (!feof(yyin));

    std::cout << inst <<std::endl;
    pcsolver s(inst);
    s.solve(1000);
   



}