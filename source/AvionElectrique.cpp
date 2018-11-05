#include <iostream>
#include "AvionElectrique.h"

	AvionElectrique::AvionElectrique (){
	Moyens(400, 6.0, 100);
	}

	AvionElectrique::~AvionElectrique ()
	{
		std::cout << "destructeur AvionElectrique" << std::endl;
	}
