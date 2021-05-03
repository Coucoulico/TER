#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "../headers/espece.h"
#include "../headers/vesicule.h"
#include "../headers/reaction.h"

#include "../headers/instance.h"

#include <stdio.h>
#include <string>


instance::instance(){};

void instance::setVesicule(const vesicule &v){
    	vesi=v;
    }

void instance::addEspece(espece e){
  	if(find(especes.begin(),especes.end(),e) == especes.end() ){
  		especes.push_back(e);
  	}
  	else{
  		std::cout << e << " est deja declaré";
  	}
  }

void instance::addReaction(const reaction& r){
	if(find(reactions.begin(),reactions.end(),r) == reactions.end() ){
  		reactions.push_back(r);
  	}
  	else{
  		std::cout << r << "recation  deja declaré";
  	}

}

  espece* instance::getEspece(std::string id){
    espece* e=nullptr;
    for(espece& es:especes){
      if(es.id==id) {
        e=&es;
        break;
      }
    }
    std::string msg="Espece Non declaré : "+id;
    if(e==nullptr) throw std::runtime_error(msg);
    return e;

    
  }


void instance::setNb(const std::string& id,const int& nb){
  espece* e=getEspece(id);
  e->setNb(nb);
}
void instance::setTaille(const std::string& id,const int& t){
  
  espece* e=getEspece(id);
  e->setTaille(t);

}
void instance::setVitesse(const std::string& id,const float& v){
  espece* e=getEspece(id);
  e->setVitesse(v);
}

std::ostream& operator<<(std::ostream& os, const instance& i)
{
    // write obj to stream
    os<< "Model : "<<std::endl;

    os<< i.vesi;

    os<<"Especes :\n";
    for(espece e: i.especes){
      os<<e;
    }
    os<<"reactions :\n";
    for(reaction r: i.reactions){
      os<<r;
    }

    return os;
}


void instance::affichage() const{

  for(const espece &e:especes){
    std::cout << e.id << " : "<<e.nb << "  ";
  }
  std::cout << std::endl;
}

void instance::store(FILE* f){
  for(const espece &e:especes){
    
    std::string s= std::to_string(e.nb);
    fputs(s.c_str(),f);
    if(e!=especes.back()) fputs(",",f);
    
  } 
 fputs("\n",f);
}

void instance::apply(const int& i,const int& n){
  if(n > 0){
    reaction r=reactions[i];
    
    espece* s1=getEspece((*r.S1).id);
    if((*s1).nb <= 0) return;
    (*s1).nb -= n;

    espece* p1 = getEspece((*r.P1).id);
    (*p1).nb += n;

    (*r.S1).nb = (*s1).nb;
    (*r.P1).nb = (*p1).nb;

    switch (r.type){
      case 0:{
        break;
      }

      case 1:{
        
        espece* s2=getEspece((*r.S2).id);
        if((*s2).nb <= 0) return;
        (*s2).nb -= n;
        (*r.S2).nb = (*s2).nb;
        
        break;
      }
      case 2:{
       

        espece* p2=getEspece((*r.P2).id);
        (*p2).nb += n;
        (*r.P2).nb = (*p2).nb;
        break;
      }
      case 3:{

        espece* s2=getEspece((*r.S2).id);
        if((*s2).nb <= 0) return;
        (*s2).nb -= n;


        espece* p2= getEspece((*r.P2).id);
        (*p2).nb += n;

        (*r.S2).nb = (*s2).nb;
        (*r.P2).nb = (*p2).nb;
        break;
      }
      default:
        std::cout << "impossible type inconnu"<<std::endl;

    }

   
    
  }
}





