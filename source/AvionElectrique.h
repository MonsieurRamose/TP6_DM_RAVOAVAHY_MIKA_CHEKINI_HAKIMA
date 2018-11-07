#ifndef AVIONELECTRIQUE_H
#define AVIONELECTRIQUE_H

#include <iostream>
#include "Moyens.h"

class AvionElectrique : public Moyens{
	public:
	AvionElectrique ();
	~AvionElectrique ();
	void afficher() const;
};
#endif
