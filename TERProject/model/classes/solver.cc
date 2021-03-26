#include "../headers/solver.h"
#include "../headers/instance.h"
#include <stdlib.h>
#include <random>
#include <vector>


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
		
		
		//number of collision
		float n=i.reactions[reaction_index].collision(alpha,i.vesi.volume());
		
		
		
		//applying the reaction
		
		i.reactions[reaction_index].apply(n);


		//getting fraction n
		float frac=n-((int)n);

		//
		if (solver::rand_uniforme()<frac){
			i.reactions[reaction_index].apply(1);
		}
		std::cout << i;
		time++;
	}

}
