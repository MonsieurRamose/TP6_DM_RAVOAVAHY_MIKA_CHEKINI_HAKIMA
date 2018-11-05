#include <iostream>
#include "Avion.h"

	Avion::Avion ():Moyens(700, 18.0, 150){

	}
	Avion::~Avion (){
		std::cout << "destructeur Avion" << std::endl;
	}
