
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
	assert(( *p != *S1) && "produit et reactif1 en meme temps");
	if (type==1 || type==3) assert(*p != *S2 && "produit et reactif2 en meme temps" );
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








