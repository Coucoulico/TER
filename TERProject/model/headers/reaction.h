
#ifndef REACTION_H
#define REACTION_H

#include "espece.h"

class reaction
{
public:
	reaction();
	reaction(float proba,int type);

	friend std::ostream& operator<<(std::ostream& os,const reaction& r);

	friend bool operator==(const reaction& r1, const reaction& r2);

	void setProd(espece* p,int to);

	float collision(float alpha,float vol);

	void apply(const int& time);

	int type;
	float proba;

	espece* S1;
	espece* S2;
	espece* P1;
	espece* P2;
	
};

#endif