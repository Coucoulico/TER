#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>

#include "espece.h"
#include "vesicule.h"

class instance
{
public:
	instance();
    void setVesicule(const vesicule& v);

    void addEspece(espece e);

    void addReaction(const reaction& r);

    void addReactif(reaction &r,const espece &e)const;
    void addProduit(reaction &r,const espece &p)const;

    espece* getEspece(std::string id);

    void setNb(const std::string& id,const int& nb);
    void setTaille(const std::string& id,const int& t);
    void setVitesse(const std::string& id,const float& v);

    friend std::ostream& operator<<(std::ostream& os, const instance& i);
    
    vesicule vesi;
	std::vector<espece> especes;
	std::vector<reaction> reactions;
	
};


#endif