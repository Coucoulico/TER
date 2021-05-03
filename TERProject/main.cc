#include "compiler/parser.h"
#include <iostream>
#include "model/headers/vesicule.h"
#include "model/headers/espece.h"
#include "model/headers/reaction.h"

#include "model/headers/instance.h"
#include "model/headers/solver.h"
#include "model/headers/molecule.h"

#include <typeinfo>
extern "C" int yyparse();
extern "C" FILE *yyin;
extern instance inst;



void simulate(instance i,unsigned int m,unsigned int time,char* file_res){
    if(m == 1){
        std::cout <<"*********** simulation starting *********"<<std::endl;
        pcsolver s(inst);
        s.solve(time,file_res);
    }
    else{
        if(m == 2){
            std::cout <<"*********** simulation starting *********"<<std::endl;
            ecsolverOpt ec(inst);
            ec.solve(time,file_res);
        }
        else{
            std::cout << "simulator type : '"
            << m<<"' does note existe.\n make :'1' for population centré simulator"
            <<"\n       '2' for entité centré simulator\n";
        }
    }

}
int main(int argc, char **argv) {
    if (argc > 4) {
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

    char folder[]="resultats/";
    char* file_res = strcat(argv[1],".csv"); 
    int time = 5000;

    if(argc >= 3){
        
        file_res = argv[2];
        
   
    }
    if(argc >= 4){
        
        time = atoi(argv[3]);
        
       
    }
    
    std::cout << "veuillez choisir le simulateur à utiliser :\n"
            <<" 1  ==> Population centrée\n"
            <<" 2  ==> Entité centrée\n";
        int mode;
        std::cin >> mode;

    simulate(inst,mode,time,strcat(folder,file_res));

    std::cout <<"*****    end of the simulation with success     ********\n";      
    
}