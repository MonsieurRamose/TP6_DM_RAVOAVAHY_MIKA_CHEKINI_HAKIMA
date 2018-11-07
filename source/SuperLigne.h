#ifndef SUPERLIGNE_H
#define SUPERLIGNE_H

#include <iostream>
#include "Terminal.h"


class SuperLigne{
	private:
	Terminal* origine;
	Terminal* destination;
	int frequence;

	public:
	SuperLigne();
	SuperLigne(Terminal* _origine, Terminal* _destination, int _frequence);
	~SuperLigne();
	const Terminal* getOrigine() const;
	const Terminal* getDestination() const;
	const int getFrequence() const;
	virtual void afficher() const ;


};
#endif
