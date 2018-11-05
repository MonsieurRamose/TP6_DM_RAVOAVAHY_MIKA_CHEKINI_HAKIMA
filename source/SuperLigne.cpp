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
