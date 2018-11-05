#include <iostream>
#include "Ligne.h"

	template <class T>
	Ligne<T>::Ligne(): frequence(0){
	
	}

	template <class T
	Ligne<T>::Lige(Terminal * _origine, Termianl* _destination, int _frequence)
	:origine(_origine), destination(_destination), frequence(_frequence){}

	template <class T
	Ligne<T>::~Ligne(){
	std::cout << "destructeur Ligne" << std::endl;
	}

	template <class T
	const Terminal* Ligne<T>::getOrigine() const{
	return origine;
	}

	template <class T
	const Terminal* Ligne<T>::getDestination() const{
	return destination;
	}

	template <class T
	const int Ligne<T>::getFrequence() const{
	return frequence;
	}

	
	




