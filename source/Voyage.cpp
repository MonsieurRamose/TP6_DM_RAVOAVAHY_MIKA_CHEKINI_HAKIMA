#include <iostream>
#include "Voyage.h"


Voyage::Voyage(){
}

Voyage::Voyage(Terminal* _origine, Terminal* _destination)
:origine(_origine), destination(_destination)
{

}

Voyage::~Voyage(){
  std::cout << "destructeur Voyage " << std::endl;
  for(typename std::list<SuperLigne*>::iterator it = lignes.begin(); it != lignes.end(); it++)
{
  if((*it) != NULL)
  {
    delete (*it);
    (*it) = NULL;
  }
}
lignes.clear();
}

const Terminal*  Voyage::getOrigine()const{
  return origine;
}
const Terminal* Voyage::getDestination() const{
  return destination;
}
const std::list<SuperLigne*> Voyage::getLignes() const{
  return lignes;
}

void Voyage::setOrigine(Terminal* o)
{
  origine = o;
}

void Voyage::setDestination(Terminal* d){
  destination = d;
}

void Voyage::setLignes(SuperLigne * s){
  if(s != NULL)
  lignes.push_back(s);
}

bool Voyage::popLignes(SuperLigne * s){
  int taille = lignes.size();
  if(!lignes.empty())
  {
    lignes.remove(s);
  }else{
    return false;
  }
  if(taille == lignes.size())
  {
    //si la ligne n'a pas été retirée
    return false;
  }else{
    return true;
  }

}

void Voyage::afficherLignes(){
  std::cout <<"Les lignes du voyage entre "<< origine->getNom() << " et " << destination->getNom() << " sont: "<< std::endl;
  for(std::list<SuperLigne *>::iterator it = lignes.begin(); it != lignes.end(); it++)
  {
    (*it)->afficher();
  }
}
