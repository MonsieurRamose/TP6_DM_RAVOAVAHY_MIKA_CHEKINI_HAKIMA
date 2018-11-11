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
	SuperLigne(Terminal* _origine, Terminal* _destination, int _frequence = 0);
	~SuperLigne();
  Terminal* getOrigine() ;
  Terminal* getDestination() ;
	const int getFrequence() const;
	virtual void afficher() const ;
	void setFrequence(int freq);

	bool operator==(SuperLigne* t);


};
#endif
