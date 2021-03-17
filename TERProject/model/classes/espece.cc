#include <iostream>
#include "../headers/espece.h"



espece::espece(std::string e):id(e){};
std::ostream& operator<<(std::ostream& os, const espece& e)
{
    // write obj to stream
    os<< "espece : "<<e.id<<" ,taille : "<<e.taille <<", nb :"<<e.nb<<", vitesse :"<<e.vitesse<<std::endl;
    return os;
}

bool operator==(const espece& e1, const espece& e2){
	return e1.id==e2.id; }

bool operator!=(const espece& e1, const espece& e2){
	return e1.id!=e2.id;
}

bool operator< (const espece &l, const espece &r){
	return l.id<r.id;
}


void espece::setTaille(const int& t){
	taille=t;
}
void espece::setVitesse(const float& v){
	vitesse=v;
}
void espece::setNb(const int& n){
	nb=n;
}

