#ifndef SOLVER_H
#define SOLVER_H
#include "instance.h"

class solver
{
public:
	solver(instance i);
	virtual ~solver()=default;
	virtual void solve(int time_max)=0;

	static float rand_uniforme();
	instance i;
	float alpha;
	
};


class pcsolver:public solver
{
public:
	pcsolver(instance i);

	virtual void solve(int time_max) override;
	
};

#endif