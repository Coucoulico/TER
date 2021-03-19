#ifndef VESICULE_H
#define VESICULE_H

class vesicule
{
public:
	vesicule();
	vesicule(const int &d);

	float volume() const;

	void setDiamettre(const int &d);
	friend std::ostream& operator<<(std::ostream& os, const vesicule& v);
	int diamettre;
};
#endif