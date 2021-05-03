#ifndef SOLVER_H
#define SOLVER_H
#include "instance.h"
#include "molecule.h"
#include <vector>

class solver
{
public:
	solver();
	solver(instance i);
	virtual ~solver()=default;
	virtual void solve(int time_max,char *path)=0;

	static float rand_uniforme();
	static bool rand_bernoulie(float p);
	instance i;
	
	
};


class pcsolver:public solver
{
public:
	pcsolver(instance i);

	virtual void solve(int time_max,char* path) override;

	float alpha;
	
};
class ecsolver:public solver
{
public:
	ecsolver(instance i);

	virtual void solve(int time_max,char* path) override;
	void init();

	std::vector<molecule> molecules;
	
};

class ecsolverOpt:public solver
{
public:
	ecsolverOpt(instance i);


	virtual void solve(int time_max,char* path) override;
	void init();
	
	void place_molecule(molecule m);
	
	int size;//la taille du cube
	std::vector<std::vector<std::vector<std::vector<molecule>>>> cube;
	
};

#endif