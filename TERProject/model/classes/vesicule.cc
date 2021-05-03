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
	float r=diamettre /2000.;

	return 4. *r*r*r * M_PI / 3;
}