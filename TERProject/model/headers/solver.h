#ifndef SOLVER_H
#define SOLVER_H
#include "instance.h"

class solver
{
public:
	solver(instance i);

	virtual void solve()=0;

	instance i;
	
};


class essolver:public solver
{
public:
	essolver();
	
};

#endif