
#include <vector>
#include <iostream>
#include "../headers/reaction.h"



reaction::reaction(){};
reaction::reaction(float pr,int t){
	proba =pr;
	type=t;
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
 	

 	os << "["<<r.proba <<"]";
 	os << std::endl;
	return os;
}

bool operator==(const reaction& r1, const reaction& r2){
	return false;;
}

float reaction::collision(float alpha,float vol){
	if(type==0 || type==2) return S1->nb * proba;
	else {
		if(*S1==*S2) return proba * (alpha/vol) * S1->nb * (S1->nb-1)/2;
		else{
			return proba * (alpha/vol) * S1->nb * S2->nb;
		}
	}
}


bool reaction::make_collision(molecule* m1,molecule* m2){
	if(m1->step_time == m2->step_time && m1->e->nb>0 && m2->e->nb>0){
		switch(type){
		case 0:
			if(*(m1->e) == *S1) {
				S1->nb--;
				P1->nb++;
				m1->e = P1;
				m1->step_time++;
				return true;
				
			}
			return false;
		break;

		case 1:
			if(*(m1->e) == *S1 && *(m2->e) == *S2 ){
				S1->nb--;
				S2->nb--;
				P1->nb++;
				
				m1->e = P1;
				m1->step_time++;
				m2->step_time++;
				
				return true;

			}

			if(*(m1->e) == *S2 && *(m2->e) == *S1){
				if(m1->in_colision(*m2)){
					S1->nb--;
					S2->nb--;
					P1->nb++;
					
					m1->e = P1;
					m1->step_time++;
					m2->step_time++;
					return true;
				}
				
			}
			return false;
		break;

		case 2:
			if(*m1->e == *S1){
				S1->nb--;
				P1->nb++;
				P2->nb++;
				
				m1->e = P1;
				m1->step_time++;
				return true;
			}
			return false;
		break;
		case 3:
			if(*(m1->e) == *S1 && *(m2->e) == *S2 ){
				if(m1->in_colision(*m2)){
					S1->nb--;
					S2->nb--;
					P1->nb++;
					P2->nb++;
					m1->e = P1;
					m2->e = P2;
					m1->step_time++;
					m2->step_time++;
					return true;
				}
				
			}

			if(*m1->e == *S2 && *m2->e == *S1){
				S1->nb--;
				S2->nb--;
				P1->nb++;
				P2->nb++;

				m1->e = P1;
				m2->e = P2;
				m1->step_time++;
				m2->step_time++;
				return true;
			}
			return false;
		break;

		default:
		return false;
			
	}
	}
	else return false;
	
}







