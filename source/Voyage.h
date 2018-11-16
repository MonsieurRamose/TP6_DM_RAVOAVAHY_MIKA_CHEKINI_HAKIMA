#ifndef VOYAGE_H
#define VOYAGE_H

#include <iostream>
#include "SuperLigne.h"
#include "Ligne.h"
#include <list>
#include "Terminal.h"
#include <typeinfo>
#include "Moyens.h"
#include "Train.h"
#include "Avion.h"
#include "AvionElectrique.h"
#include <algorithm>
class Voyage{
private:
	Terminal* origine;
	Terminal* destination;
	std::list<SuperLigne*> lignes; // un voyage a une liste de lignes à emprunter

public:
	Voyage();
	Voyage(Terminal* _origine, Terminal* _destination);
	~Voyage();
  Terminal*  getOrigine()const;
  Terminal* getDestination() const;
  std::list<SuperLigne*> getLignes() const;
	void setOrigine(Terminal* o);
	void setDestination(Terminal* d);
	void setLignes(SuperLigne * s);
 	bool popLignes(SuperLigne * s);
	void afficherLignes();
	std::list<SuperLigne*> sortLignes();
	double tempsTrajet() ;
	double empreinteCarbone();
	Moyens* getMoyen(std::string& m) const;
	void PlusCourtChemin(std::list<Terminal *> chemin, Terminal* terminaux[], int n, std::list<SuperLigne *> leslignes);
	SuperLigne* existeLigne( Terminal *start,Terminal * l, std::string moyen,std::list<SuperLigne *> leslignes);
	bool operator== (Voyage* v);
	int position(Terminal *t, Terminal*[] );


};
#endif
