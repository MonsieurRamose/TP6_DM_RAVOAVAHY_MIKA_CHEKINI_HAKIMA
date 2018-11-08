#ifndef AVION_H
#define AVION_H

#include <iostream>
#include "Moyens.h"

class Avion : public Moyens{
	public:
	Avion ();
	~Avion ();
	void afficher() const;
	const std::string& getName() const;
};
#endif
