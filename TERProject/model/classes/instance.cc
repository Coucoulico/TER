#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "../headers/espece.h"
#include "../headers/vesicule.h"
#include "../headers/reaction.h"

#include "../headers/instance.h"


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
  std::cout <<"add react"<<std::endl;
	if(find(reactions.begin(),reactions.end(),r) == reactions.end() ){
  		reactions.push_back(r);
      std::cout <<"bien ajouté";
  	}
  	else{
  		std::cout << r << "recation  deja declaré";
  	}

}

  espece* instance::getEspece(std::string id){
    for(espece& e:especes){
      if(e.id==id) return &e;
    }
    assert("Espece Non declaré\n" );
    
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


