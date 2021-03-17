#include <iostream>
#include "../headers/vesicule.h"

vesicule::vesicule(){};
vesicule::vesicule(const int &d):diamettre(d){};
void vesicule::setDiamettre(const int &d){
	diamettre=d;
};

std::ostream& operator<<(std::ostream& os, const vesicule& v){
	os << "Vesicule : diamettre :"<<v.diamettre<<std::endl;
	return os;
	}
