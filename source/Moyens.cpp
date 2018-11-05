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
	const double Moyens::getempreinte() const{
	return empreinte;
	}
	Moyens::~Moyens(){
	std::cout << "destructeur Moyens" << std::endl;
	}
