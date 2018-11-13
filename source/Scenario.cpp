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
  try{
    if(v == NULL)
    {
      throw std::string ("Voyage NULL");
    }else{

         voyages.push_back(v);
    }
  }
  catch(std::string const& chaine)
  {
     std::cerr << chaine << std::endl;
  }

}
