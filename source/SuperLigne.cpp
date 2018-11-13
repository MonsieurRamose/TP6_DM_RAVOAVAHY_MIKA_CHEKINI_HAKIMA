#include "SuperLigne.h"
#include <iostream>


	SuperLigne::SuperLigne(){}
	SuperLigne::SuperLigne(Terminal* orig, Terminal* dest, int freq)
	:  origine(orig), destination(dest),frequence(freq){
		int ajout = origine->ajouterLiaison(destination);
		switch (ajout)
		{
			case 0:
				std::cout << "Creation d'une liaison entre " << origine->getNom() << " et "  << destination->getNom() << std::endl;
			case -1:
				std::cout<< " Le terminal: " << origine->getNom() << " est deja relié à " << destination->getNom() << std::endl;
			break;
			case -2:
				std::cout<< " Le terminal: " << origine->getNom() << " a atteint sa capacité maximum de liaison " << std::endl;
			break;
			case -3:
				std::cout<<" Le terminal " << origine->getNom() << " n'est relié qu'avec des gares ou des hubs multimodal "<< std::endl;
			break;
			case -4:
				std::cout<<" Le terminal: " << origine->getNom() << " n'est relié qu'avec une seule gare"<< std::endl;
			break;
			default:
			// ajout == -5
			std::cout<<" Le terminal " << origine->getNom() << " n'est relié qu'avec des aeroports "<< std::endl;
			break;
		}

	}

	SuperLigne::~SuperLigne()
	{
		std::cout << "destructeur SuperLigne" << std::endl;
	}
	 Terminal* SuperLigne::getOrigine() {
	return origine;
	}

	 Terminal* SuperLigne::getDestination() {
	return destination;
	}

	const int SuperLigne::getFrequence() const{
	return frequence;
	}
	void SuperLigne::setFrequence(int freq){
		frequence = freq;
	}
	void SuperLigne::afficher() const{
		std::cout << " reliant "<< origine->getNom() <<" et " << destination->getNom() <<", frequence: " << frequence<< " passagers/jour"<<std::endl;
	}


	bool SuperLigne::operator== (SuperLigne* s){
	return (this->origine == s->getOrigine()) && (this->destination == s->getDestination()) && (this->frequence == s->getFrequence());
  }
