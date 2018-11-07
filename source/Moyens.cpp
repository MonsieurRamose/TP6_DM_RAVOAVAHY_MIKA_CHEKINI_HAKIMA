#include <iostream>
#include "Moyens.h"

	Moyens:: Moyens():vitesse(0),empreinte ( 0), capacite (0){}
	Moyens::Moyens(int _vitesse, double _empreinte, int _capacite):
	vitesse(_vitesse),empreinte ( _empreinte), capacite (_capacite){}


	const int Moyens::getCapacite() const{
	return capacite;
	}
	const int Moyens::getVitesse() const{
	return vitesse;
	}
	const double Moyens::getEmpreinte() const{
	return empreinte;
	}
	Moyens::~Moyens(){
	std::cout << "destructeur Moyens" << std::endl;
	}

	void Moyens::setEmpreinte(double emp)
	{
		empreinte = emp;
	}

void Moyens::afficher() const{
		std::cout <<" Vitesse: " << vitesse <<" Km/h, Empreinte: "<< empreinte<< " kg/km, capacite: " << capacite <<" passagers" <<std::endl;
	}
