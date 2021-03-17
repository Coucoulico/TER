
#include <vector>
#include <iostream>
#include "../headers/reaction.h"
//#include "../headers/espece.h"

reaction::reaction(){};
reaction::reaction(float p):proba(p){};


void reaction::addReactif(const espece& r){
	if(std::find(reactifs.begin(),reactifs.end(),r) == reactifs.end()){
		if(std::find(produits.begin(),produits.end(),r) == produits.end()){
			reactifs.insert(r);
		}
		else{
			std::cout <<r << " ne peut pas etre reactif et produits !"<<std::endl;
		}
		
	}
	else{
		std::cout << r<< "  : figure parmis les reactifs de cette react !"<<std::endl;
	}
}

void reaction::addProduit(const espece& p){
	if(std::find(reactifs.begin(),reactifs.end(),p) == reactifs.end()){
		if(std::find(produits.begin(),produits.end(),p) == produits.end()){
			produits.insert(p);
		}
		else{
			std::cout<< p<< " figure parmis les produits de cette react !"<<std::endl;
		}
		
	}
	else{
		std::cout << p<< "  :ne peut pas etre reactif et produits à la fois ! "<<std::endl;
	}
	}

void reaction::setp1(espece *p){
	if (p==p2)
		std::cout <<"Espece : "<<(*p).id <<" :Est deja produit dans cette rection!";
	else if(p==s1 || p==s2) std::cout <<"Espece : "<< (*p).id <<" parmis les reactifs ";
	else p1=p;
}

void reaction::setp2(espece *p){
	if (p==p1)
		std::cout <<"Espece : "<<(*p).id <<" :Est deja produit dans cette rection!";
	else if(p==s1 || p==s2) std::cout <<"Espece : "<< (*p).id <<" parmis les reactifs ";
	else p1=p;
}


bool operator==(const reaction& r1, const reaction& r2){
	return (r1.p1==r2.p1 && r1.p2==r2.p2 && r1.s1==r2.s1 && r1.s2==r2.s2);
}
bool operator< (const reaction &l, const reaction &r){
	if (l==r) return 0;
	else {
		return l.reactifs<r.reactifs or l.produits<r.produits;
	}
}

std::ostream& operator<<(std::ostream& os, const reaction& r){
	os << "reaction : ";
	os << (*r.s1).id <<" + "<<(*r.s2).id<<" --> "<<(*r.p1).id<<" + "<<(*r.p1).id;
	os <<"     : ["<<r.proba<<"]"<<std::endl;
return os;

}