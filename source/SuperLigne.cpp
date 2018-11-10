#include "SuperLigne.h"
#include <iostream>


	SuperLigne::SuperLigne(){}
	SuperLigne::SuperLigne(Terminal* orig, Terminal* dest, int freq)
	:  origine(orig), destination(dest),frequence(freq){}

	SuperLigne::~SuperLigne()
	{
		std::cout << "destructeur SuperLigne" << std::endl;
	}
	const Terminal* SuperLigne::getOrigine() const{
	return origine;
	}

	const Terminal* SuperLigne::getDestination() const{
	return destination;
	}

	const int SuperLigne::getFrequence() const{
	return frequence;
	}
	void SuperLigne::setFrequence(int freq){
		frequence = freq;
	}
	void SuperLigne::afficher() const{
		std::cout << " reliant "<< origine->getNom() <<" et " << destination->getNom() <<", frequence: " << frequence<< " passagers/jour"<<std::endl;
	}


	bool SuperLigne::operator== (SuperLigne* s){
	return (this->origine == s->getOrigine()) && (this->destination == s->getDestination()) && (this->frequence == s->getFrequence());
  }
