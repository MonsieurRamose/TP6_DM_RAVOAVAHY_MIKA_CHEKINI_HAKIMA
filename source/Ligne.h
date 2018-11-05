#include <iostream>
#include "Terminal.h"

template <class T>
class Ligne{

	Terminal* origine;
	Terminal* destination:
	int frequence;

	public:
	Ligne<T>();
	Ligne<T>(Terminal* _origin, Terminal* _destination, int _frequence);
	~Ligne<T>();
	const Terminal* getOrigine() const;
	const Terminal* getDestination() const;
	const int getFrequence() const; 	
	

};
