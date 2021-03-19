#include <iostream>
#include "../headers/vesicule.h"
#include <math.h>

vesicule::vesicule(){};
vesicule::vesicule(const int &d):diamettre(d){};
void vesicule::setDiamettre(const int &d){
	diamettre=d;
};

std::ostream& operator<<(std::ostream& os, const vesicule& v){
	os << "Vesicule : diamettre :"<<v.diamettre<<std::endl;
	return os;
	}

float vesicule::volume() const{
	return 4/3 * M_PI * pow(diamettre/2,3);
}