
#ifndef REACTION_H
#define REACTION_H

#include <set>
#include "espece.h"
class reaction
{
public:
	reaction();
	reaction(float proba);
	friend std::ostream& operator<<(std::ostream& os, const reaction& r);
	friend bool operator< (const reaction &l, const reaction &r);

	friend bool operator==(const reaction& r1, const reaction& r2);
	void addReactif(const espece& r);
	void addProduit(const espece& p);

	void setp1(espece *p);
	void setp2(espece *p);

	float proba;

	espece* s1;
	espece* s2;
	espece* p1;
	espece* p2;

	std::set<espece> reactifs;
	std::set<espece> produits;
	
};

#endif