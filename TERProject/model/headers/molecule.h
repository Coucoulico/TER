#ifndef MOLECULE_H
#define MOLECULE_H
#include "espece.h"
#include <tuple>
class molecule
{
public:
	molecule();
	molecule(std::tuple<float,float,float> pos);
	static molecule make_molecule(float diamettre_vesi);
	static std::tuple<float,float,float> make_point(float r_vesi);
	
	void setEspece(espece *e);
	bool changePosition(std::tuple<float,float,float> dmouv,float r_vesi);

	bool move(float r_vesi,int time);
	bool in_colision(molecule m);
	friend std::ostream& operator<<(std::ostream& os,const molecule& m);

	static constexpr float v_max = 10.;
	espece *e;
	float x;
	float y;
	float z;

	//
	int step_time;

	
};

#endif