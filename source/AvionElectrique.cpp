#include <iostream>
#include "AvionElectrique.h"

	AvionElectrique::AvionElectrique ():
	Moyens(400, 6.0, 100, "AvionElectrique"){};


	AvionElectrique::~AvionElectrique ()
	{
		std::cout << "destructeur AvionElectrique" << std::endl;
	}

	void AvionElectrique::afficher() const{
	 std::cout << "      Avion electrique de ";
	 Moyens::afficher();
	}

	const std::string& AvionElectrique::getName()const{
		return name;
	}
