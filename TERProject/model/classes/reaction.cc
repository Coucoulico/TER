
#include <vector>
#include <iostream>
#include "../headers/reaction.h"
//#include "../headers/espece.h"

reaction::reaction(){};
reaction::reaction(float pr,int t){
	proba =pr;
	type=t;
	/*S1=nullptr;
	S2=nullptr;
	P1=nullptr;
	P2=nullptr;*/
}

void reaction::setProd(espece* p,int to){
	if ((type == 0 || type == 1)) assert (to ==1 && "ce type de reaction contient un seul produit");
	
	if(to==1) P1=p;
	else P2=p;
}

std::ostream& operator<<(std::ostream& os,const reaction& r){
 	os << "reaction : "<< r.type << ": ";
 	
 	os << (*r.S1).id;
 	
 	if(r.type ==1 || r.type==3) os << " + " << (*r.S2).id;
 	
 	os << " --> ";
 	os << (*r.P1).id;
 	
 	if(r.type ==2 || r.type==3) os << " + " << (*r.P2).id;
 	os << std::endl;
	return os;
}

bool operator==(const reaction& r1, const reaction& r2){
	return false;;
}

float reaction::collision(float alpha,float vol){
	if(type==0 || type==2) return S1->nb * proba;
	else {
		if(*S1==*S2) return proba * (alpha/vol)*(S1->nb) * ((S1->nb)-1)/2;
		else{
			return proba * (alpha/vol) * (S1->nb) * (S2->nb);
		}
	}
}

void reaction::apply(int n){
		std::cout << n;
		switch (type){
			case 0:{
				S1->setNb(S1->nb - n);
				P1->setNb(P1->nb + n);

				break;
			}

			case 1:{
				S1->nb -= n;
				S2->nb -= n;
				P1->nb += n;
				break;
			}
			case 2:{
				S1->nb -= n;
				P1->nb += n;
				P2->nb += n;
				break;
			}
			case 3:{
				S1->nb -= n;
				S2->nb -= n;
				P1->nb += n;
				P2->nb += n;
				break;
			}
			default:
				std::cout << "impossible type inconnu"<<std::endl;
			std::cout <<*S1 ;

		}
}








