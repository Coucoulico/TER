#include "../headers/solver.h"
#include "../headers/instance.h"
#include "../headers/molecule.h"
#include <stdlib.h>
#include <random>
#include <vector>
#include <stdio.h>
#include <string>

solver::solver(){}
//initialisation d'un solver 
solver::solver(instance inst){
	i=inst;
	
}

// generer un float x E [0,1] selon la loi uniforme
float solver::rand_uniforme(){
	std::random_device rd;
	std::default_random_engine g(rd());
	std::uniform_real_distribution<float>  dist(0.0,1.0);
	return dist(g);
}

//genere un choix de bernoulie avec une prba p
bool solver::rand_bernoulie(float p){
	std::random_device rd;
	std::default_random_engine generator(rd());
  	std::bernoulli_distribution distribution(p);
  	return distribution(generator);
}

//initialiser un simulateur population centre 
pcsolver::pcsolver(instance inst):solver(inst){alpha = 7.4e-7;};

//l'algorithme de simulation du model population centre
void pcsolver::solve(int max_time,char* path)  {
	//preparer les fichier,resultat
	FILE * file ;
	file = fopen(path,"w+");
	fputs("time,",file);
	for(const espece& e :i.especes){
		fputs(e.id.c_str(),file);
		if(e != i.especes.back()) fputs(",",file);
	}
	fputs("\n",file);

	std::cout <<"*********           Population centrée simulateur            ********\n";
	
	for(int t=0;t< max_time;t++){

		if(t%50==0){
			std::string s=std::to_string(t/50)+",";
			fputs(s.c_str(),file);
			//à chaque seconde on ecris une ligne dans le fichier resultats
			i.store(file);
		}
		
		
		//50 fois dans un sens 
		for(int slot=0;slot++<50;){

			for(std::size_t j=0 ;j<i.reactions.size();j++){
				//number of collision
				float n=i.reactions[j].collision(alpha,i.vesi.volume());
				//applying the reaction
				i.apply(j,(int)n);
				//getting fraction n
				float frac=n-((int)n);
				//traiter la fraction
				if (solver::rand_uniforme()<frac){
					i.apply(j,1);
					
				}
			
			}
		
			//50 fois dans un autre sens
			for (std::size_t j = i.reactions.size()-1; j--;){
				//number of collision
				float n = i.reactions[j].collision(alpha,i.vesi.volume());
				//applying the reaction
				i.apply(j,(int)n);
				//getting fraction n
				float frac=n-((int)n);
				
				//traitement de la fraction
				if (solver::rand_uniforme()<frac){
					i.apply(j,1);
					
				}
				
			}
		}
	}
	fclose(file);

}



//******* le model entité centré Non optimisé *********//



//instantiation d'un simulateur entité centré
ecsolverOpt::ecsolverOpt(instance inst):solver(inst){
	size = i.vesi.diamettre/10 +2;
	init();
}

//initialisation des molecules et repartition des ces dernieres sur les mini-cube
void ecsolverOpt::init(){
	
	for(int i =0 ;i<size;i++){
		std::vector<std::vector<std::vector<molecule>>> a;
		
		for(int j = 0;j<size;j++){
			std::vector<std::vector<molecule>> b;
			
			for(int k=0;k<size;k++){
				std::vector<molecule> c;
				b.push_back(c);
			}
			a.push_back(b);
		}
		cube.push_back(a);
	}
	for(espece& e :i.especes){
		for(int j=0;j++<e.nb;) {	
			molecule m=molecule::make_molecule(i.vesi.diamettre/2);
			m.setEspece(&e);
			place_molecule(m);
		}
	}

}

//placer une molecule dans les mini-cube assicié .
void ecsolverOpt::place_molecule(molecule m){
	int x = m.x/10 + size/2;
	int y = m.y/10 + size/2;
	int z = m.z/10 + size/2;
	cube[x][y][z].push_back(m);
}

//l'algorithme de simulation entité centré
void ecsolverOpt::solve(int time,char* path){
	std::cout << "*********  Entité centré simulateur ********"<<std::endl;

	FILE * file ;
	file = fopen(path,"w+");
	fputs("time,",file);
	for(const espece& e :i.especes){
		fputs(e.id.c_str(),file);
		if(e != i.especes.back()) fputs(",",file);
	}
	fputs("\n",file);

	int nb_slot=10000;//un pas correspond à 100 uS ==> 10 simulation par miliseconds 
											//   ==> 10000 par secondes

	//on boucle sur le temps en seconds
	for(int k=0;k<time;k++){
		std::string s=std::to_string(k)+",";
		fputs(s.c_str(),file);
		//à chaque instant t on ecris l'evolution des concentration dans le fichier resultat
		i.store(file);

		//pour chaque pas de temps de l'intervalle  [t-t+1]
		for(int n=0; n<nb_slot;n+=2){
			
			//ascendant
			
			for(int v=0;v<cube.size();v++){
				for(int w=0;w<cube[v].size();w++){
					for(int s=0;s<cube[v][w].size();s++){
						for(int u=0;u<cube[v][w][s].size();u++){
								//on ignore les molecules qui sont dans le future
								if(cube[v][w][s][u].step_time > k*nb_slot +n) continue;
								
								//pour les molecule dans le present
								//on fait bouger la molecule
								cube[v][w][s][u].move(i.vesi.diamettre/2,1);
								//on la replace dans le mini-cube correspondant il se peut qu'elle change de mini-cub
								place_molecule(cube[v][w][s][u]);

								//on la supprime de l'ancien mini-cube
								cube[v][w][s].erase(cube[v][w][s].begin()+u);
								
								//on recupere les coords du cube ou elle se trouve la molecule apres avoir bouger
								int x=cube[v][w][s][u].x/10 +size/2;
								int y=cube[v][w][s][u].y/10 +size/2; 
								int z=cube[v][w][s][u].z/10 +size/2;
								
								//si la molecule entre en collision et reagit avec succes avec une autre molecul stop=true 
								bool stop=false;

								//on regarde si il se passe qlq chose autour de cette derniere
								for(int a=x-1;a<=x+1;a++){
									for(int b=y-1;b<=y+1;b++){
										for(int c=z-1;c<=z+1;c++){
											if(a<size && b< size && c < size && a>=0 && b>=0 && c>=0 ){
												for(int j=0 ;j<cube[a][b][c].size();j++){
													
													//ignorer la reaction de la molecule avec elle meme
													if( &cube[v][w][s][u] == &cube[a][b][c][j] ) continue;
													
														if(cube[v][w][s][u].step_time % 4 == 2)
															std::reverse(i.reactions.begin(),i.reactions.end());													//chercher si une reaction entre les deux molecule est possible
														for(reaction& r:i.reactions){
															//on essaie d'applique la reaction avec sa probabilité
															if(!rand_bernoulie(r.proba)) continue;//on saint qu'il n y aura pas de choque
															
															stop=r.make_collision(&cube[v][w][s][u],&cube[a][b][c][j]);
															
															//si le choque est reussit
															if(stop) {	
																//on incremente les reactifs on decremente les produits
																//et on passe à la molecule suivante avec break pour sortir des boucles																
																i.getEspece(r.S1->id)->nb--;
																i.getEspece(r.P1->id)->nb++;

																if(r.type == 1){
																	i.getEspece(r.S2->id)->nb--;
																	cube[a][b][c].erase(cube[a][b][c].begin()+j);
																	
																}
																if(r.type == 2){
																	i.getEspece(r.P2->id)->nb++;

																	std::tuple<float,float,float> pos(cube[v][w][s][u].x,cube[v][w][s][u].y,cube[v][w][s][u].z);
																	molecule m1 =molecule(pos);
																	m1.setEspece(r.P2);
																	m1.step_time = cube[v][w][s][u].step_time;
																	cube[a][b][c].push_back(m1);
																	
																}
																if(r.type == 3){
																		i.getEspece(r.S2->id)->nb--;
																		i.getEspece(r.P2->id)->nb++;
																}
																i.affichage();
																break;
																}
															if(stop) break;
															}

												if(stop)break;
											}
											if(stop) break;
										}

										if(stop)break;
									}
									if(stop)break;
								}
								if(stop)break;
							}
							if(stop)break;
						}
					}
				}
			}


			//descendant
			
			for(int v=cube.size()-1;v>=0;v--){
				for(int w=cube[v].size()-1;w>=0;w--){
					for(int s=cube[v][w].size()-1;s>=0;s--){
						for(int u=cube[v][w][s].size()-1;u>=0;u--){
								//std::cout <<"***** Asc *****\n";
								//on ignore les molecules qui sont dans le future
								if(cube[v][w][s][u].step_time > k*nb_slot +n+1) continue;
								
								//pour les molecule dans le present
								//on fait bouger la molecule
								cube[v][w][s][u].move(i.vesi.diamettre/2,1);
								//on la replace dans le mini-cube correspondant il se peut qu'elle change de mini-cub
								place_molecule(cube[v][w][s][u]);

								//on la supprime de l'ancien mini-cube
								cube[v][w][s].erase(cube[v][w][s].begin()+u);
								
								//on recupere les coords du cube ou elle se trouve la molecule apres avoir bouger
								int x=cube[v][w][s][u].x/10 +size/2;
								int y=cube[v][w][s][u].y/10 +size/2; 
								int z=cube[v][w][s][u].z/10 +size/2;
								
								
								//si la molecule entre en collision et reagit avec succes avec une autre molecul stop=true 
								bool stop=false;

								//on regarde si il se passe qlq chose autour de cette derniere
								for(int a=x-1;a<=x+1;a++){
									for(int b=y-1;b<=y+1;b++){
										for(int c=z-1;c<=z+1;c++){
											if(a<size && b< size && c < size && a>=0 && b>=0 && c>=0 ){
												for(int j=0 ;j<cube[a][b][c].size();j++){
													
													//ignorer la reaction de la molecule avec elle meme
													if( &cube[v][w][s][u] == &cube[a][b][c][j] ) continue;
													
													//chercher si une reaction entre les deux molecule est possible
													for(reaction& r:i.reactions){
														//on essaie d'applique la reaction avec sa probabilité
														if(!rand_bernoulie(r.proba)) continue;//on saint qu'il n y aura pas de choque
														
														stop=r.make_collision(&cube[v][w][s][u],&cube[a][b][c][j]);
														
														//si le choque est reussit
														if(stop) {	
															//on incremente les reactifs on decremente les produits
															//et on passe à la molecule suivante avec break pour sortir des boucles																
															i.getEspece(r.S1->id)->nb--;
															i.getEspece(r.P1->id)->nb++;

															if(r.type == 1){
																i.getEspece(r.S2->id)->nb--;
																cube[a][b][c].erase(cube[a][b][c].begin()+j);
																
															}
															if(r.type == 2){
																i.getEspece(r.P2->id)->nb++;

																std::tuple<float,float,float> pos(cube[v][w][s][u].x,cube[v][w][s][u].y,cube[v][w][s][u].z);
																molecule m1 =molecule(pos);
																m1.setEspece(r.P2);
																m1.step_time = cube[v][w][s][u].step_time;
																cube[a][b][c].push_back(m1);
																
															}
															if(r.type == 3){
																	i.getEspece(r.S2->id)->nb--;
																	i.getEspece(r.P2->id)->nb++;
															}
															i.affichage();
															break;
															}
														if(stop) break;
														}
													//}
												
												if(stop)break;
											}
											if(stop) break;
										}

										if(stop)break;
									}
									if(stop)break;
								}
								if(stop)break;
							}
							if(stop)break;
						}
					}
				}
			}
			
		}
	}
				
	fclose(file);
}



