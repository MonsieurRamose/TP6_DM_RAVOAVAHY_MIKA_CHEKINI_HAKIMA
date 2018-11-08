#ifndef MOYENS_H
#define MOYENS_H

#include <iostream>
#include <string>

class Moyens{
protected:
	int vitesse;
	double empreinte;
	int capacite;
	std::string name;


	public:
	Moyens();
	Moyens(int _vitesse, double _empreinte, int _capacite, std::string _name);
	const int getCapacite() const;
	const int getVitesse() const;
	const double getEmpreinte() const;
	//void setEmpreinte(double emp);
	virtual void afficher() const;
	virtual const std::string& getName()const = 0;
	~Moyens();

};
#endif
