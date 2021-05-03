#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>
#include "reaction.h"
#include "espece.h"
#include "vesicule.h"
#include <stdio.h>

class instance
{
public:
	instance();
    void setVesicule(const vesicule& v);

    void addEspece(espece e);

    void addReaction(const reaction& r);
    

    espece* getEspece(std::string id);

    void setNb(const std::string& id,const int& nb);
    void setTaille(const std::string& id,const int& t);
    void setVitesse(const std::string& id,const float& v);
    void apply(const int& r,const int& time);

    friend std::ostream& operator<<(std::ostream& os, const instance& i);

    void affichage() const;
    void store(FILE* f);
    
    vesicule vesi;
	std::vector<espece> especes;
	std::vector<reaction> reactions;
	
};


#endif