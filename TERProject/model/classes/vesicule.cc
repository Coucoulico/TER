#include <iostream>
#include "../headers/vesicule.h"
#include <math.h>

vesicule::vesicule(){};
vesicule::vesicule(const int &d):diamettre(d){};
void vesicule::setDiamettre(const int &d){
	diamettre=d;//en nano
};

std::ostream& operator<<(std::ostream& os, const vesicule& v){
	os << "Vesicule : diamettre :"<<v.diamettre<<std::endl;
	return os;
	}

float vesicule::volume() const{
	float d_umcube=diamettre * pow(10,-3);
	return 4 * M_PI * pow(d_umcube/2,3) / 3;
}