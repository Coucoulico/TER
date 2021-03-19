
#ifndef ESPECE_H
#define ESPECE_H

enum propriete {Init, Taille, Vitesse,Nb};
class espece
{
public:
	espece(std::string id);
	friend std::ostream& operator<<(std::ostream& os, const espece& v);
	friend bool operator==(const espece& e1, const espece& e2);
	friend bool operator!=(const espece& e1, const espece& e2);
	friend bool operator< (const espece &l, const espece &r);

	void setTaille(const int& t);//1-10
	void setVitesse(const float& v);//1-
	void setNb(const int& n);


	std::string id;
	int taille;
	float vitesse;
	int nb;
	
};

#endif

