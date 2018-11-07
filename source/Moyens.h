#ifndef MOYENS_H
#define MOYENS_H

#include <iostream>

class Moyens{
	private:
	int vitesse;
	double empreinte;
	int capacite;

	public:
	Moyens();
	Moyens(int _vitesse, double _empreinte, int _capacite);
	const int getCapacite() const;
	const int getVitesse() const;
	const double getEmpreinte() const;
	void setEmpreinte(double emp);
	virtual void afficher() const;
	~Moyens();

};
#endif
