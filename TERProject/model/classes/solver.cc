#include "../headers/solver.h"
#include "../headers/instance.h"
#include <stdlib.h>
#include <random>


solver::solver(instance inst){
	i=inst;
	alpha = 7.4 * pow(10,-7);
}


float solver::rand_uniforme(){
	std::default_random_engine g;
	std::uniform_real_distribution<float>  dist(0.0,1.0);
	return dist(g);
}


pcsolver::pcsolver(instance inst):solver(inst){};

void pcsolver::solve(int max_time)  {
	
	int time=0;
	while(time < max_time){
		//i.affichage();
		//choose reaction randomly
		int reaction_index = rand() % i.reactions.size();
		//getting the reaction
		reaction r = i.reactions[reaction_index];
		
		//number of collision
		float n=r.collision(alpha,i.vesi.volume());
		
		
		
		//applying the reaction
		r.apply(n);
		std::cout <<"S1 : "<<*r.S1;
		std::cout <<"P1 : "<<*r.P1;


		//getting fraction n
		float frac=n-((int)n);

		//
		if (solver::rand_uniforme()<frac){
			r.apply(1);
		}
		time++;
	}

}
