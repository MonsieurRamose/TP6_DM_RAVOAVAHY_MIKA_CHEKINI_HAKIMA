#include "Scenario.h"


Scenario::Scenario(){

}
Scenario::Scenario(std::string _nom):nom(_nom){

}


Scenario::~Scenario(){

}

std::string Scenario::getNom() const{
  return nom;
}
std::list <Voyage *> Scenario::getVoyages() const{
  return voyages;
}
void Scenario::addVoyage(Voyage * v){

  voyages.push_back(v);
}

/*Affiche tous les voyages d un scenario ainsi que ses lignes */
void Scenario::afficherVoyages () {

  std::cout <<"Les voyages du "<< this->getNom() << " sont: "<< std::endl;

  for(std::list<Voyage *>::iterator it = this->voyages.begin(); it != this->voyages.end(); it++)
  {
    (*it)->afficherLignes();
  }
}
