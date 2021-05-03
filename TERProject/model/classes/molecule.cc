#include <iostream>
#include "../headers/molecule.h"
#include <math.h>
#include <stdlib.h>
#include <random>
#include <stdio.h>

molecule::molecule(){};

molecule::molecule(std::tuple<float,float,float> pos){
	x=std::get<0>(pos);
	y=std::get<1>(pos);
	z=std::get<2>(pos);
	step_time = 0;
}

//un point dans l'espace d'un rayon r du centre
std::tuple<float,float,float> molecule::make_point(float r){
	std::random_device rd;
	std::default_random_engine g(rd());
	
	std::uniform_real_distribution<float>  dist(0.0 , r);
	float ro=dist(g);

	std::uniform_real_distribution<float> dist_angle(0.0 ,2 * M_PI);

	float alpha = dist_angle(g);
	float theta = dist_angle(g);

	//calculate cartesian coords
	float x = ro * sin(theta) * cos(alpha);
	float y = ro * sin(theta) * sin(alpha);
	float z = ro * cos(theta);
	return std::make_tuple(x,y,z);
}

//un molecule positionnée aleatoirement dans l'espace de la vesicule du rayon r
molecule molecule::make_molecule(float r){
	return molecule(molecule::make_point(r));
}

void molecule::setEspece(espece *es){
	e=es;
}

//r_vesicule correspond au rayon de la vesicule avec un rayon de deplacement pos
bool molecule::changePosition(std::tuple<float,float,float> pos,float r_vesicule){
	float nx =x + std::get<0>(pos);
	float ny =y + std::get<1>(pos);
	float nz =z + std::get<2>(pos);
	//calculer la distance de ce nouveau point du centre de la vesicule qui est (0,0,0)
	float d = sqrt(nx * nx + ny * ny + nz * nz);

	//tester si la nouvelle position est dans la vesicule
	if(d <= r_vesicule){
		//we move the molecule
		x = nx;
		y = ny;
		z = nz;
		return true;
	}
	else {
		return false;
}
}

bool molecule::move(float r_vesi,int time){
	float ro = e->vitesse * molecule::v_max * time;
	step_time++;

	std::random_device rd;
	std::default_random_engine g(rd());
	

	std::uniform_real_distribution<float> dist_angle(0.0 ,2 * M_PI);

	float alpha = dist_angle(g);
	float theta = dist_angle(g);

	//calculate cartesian coords
	float x = ro * sin(theta) * cos(alpha);
	float y = ro * sin(theta) * sin(alpha);
	float z = ro * cos(theta);
	return changePosition(std::make_tuple(x,y,z),r_vesi);
}


bool molecule::in_colision(molecule m){
	float dx =x-m.x;
	float dy =y-m.y;
	float dz =z-m.z;
	float distance = sqrt(dx*dx + dy*dy + dz*dz);
	return (2*distance < (*e).taille + m.e->taille);
}

std::ostream& operator<<(std::ostream& os,const molecule& m){
 	os << "molecule : ";
 	
 	os << (*m.e).id;
 	
 	os << " {" <<m.x <<" , " << m.y << "," << m.z <<"}  time = "<<m.step_time <<std::endl;
 		return os;
	}