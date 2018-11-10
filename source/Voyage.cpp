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

 Moyens* Voyage::getMoyen(std::string& m) const{
  if(m.compare("5Train")== 0)
  {
    return new Train();
  }else{
    if(m.compare("5Avion")== 0)
    {
      return new Avion();
    }else{
      return new AvionElectrique();
    }
}
}

std::list<SuperLigne*> Voyage::sortLignes(Terminal* t){

  std::list<SuperLigne*> lignescopie;
  /*Copier les lignes dans une liste a part pour ne pas modifier une lignes donnée*/
  for(std::list<SuperLigne *>::iterator itera = lignes.begin(); itera != lignes.end(); itera++)
  {
    lignescopie.push_back(*itera);
  }
  /*Cette liste recevera les lignes triées selon l'odre de depart*/
  std::list<SuperLigne*> lignesTrie;
  std::list<SuperLigne*> ::iterator itTrie = lignesTrie.begin();
  const Terminal* org = t;

  std::list<SuperLigne*> ::iterator it = lignescopie.begin();

  /*Lidée est d'inserer dans la liste ligneTrie, les lignes en suivant l ordre de depart pour arriver a la distination finale,
  tant que la liste de lignes lignescopie n'est pas vide. et a chaque insertion d'une ligne, on enlève cette dernière de
  la liste lignescopie*/

  while( !lignescopie.empty())
  {
    if(it == lignescopie.end())
    {
      it = lignescopie.begin();
    }
    if((*it)->getOrigine() == org)
    {
      lignesTrie.push_back (*it);
      itTrie ++;
      org = (*it)->getDestination();
      /*supprimer la ligne de la liste lignescopie*/
      lignescopie.remove(*it);
      it--;
    }else{
      it++;
    }
  }

  if(org != this->destination)
  {
    std::cout<< "Il n ya pas de ligne qui ramène à " << this->destination->getNom()<< std::endl;
    return lignescopie; // renvoyer une liste vide
  }
  return lignesTrie;

}
double Voyage::tempsTrajet() {
  double dis = 0;
  double temps = 0;
  Moyens *moyenTrans;
  std::string moyenName ;
  std::string m ;
  std::list<SuperLigne *>ligneTrie = sortLignes(this->origine);
  if(ligneTrie.empty())
  {
    return -1;
  }else{
    for(std::list<SuperLigne *>::iterator it = ligneTrie.begin(); it != ligneTrie.end(); it++)
    {
      dis = 0;
      /*Calculer la distance entre les deux villes reliées par une ligne*/
      dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(), ((*it)->getDestination())->getLongitude());
      /*additionner tous les temps moyen de correspondance des terminaux d'origine*/
      temps += (*it)->getOrigine()->getTempsCorrespondance();

      /* On doit savoir le moyen de transport emprunté entre deux villes données car la vitesse
       varie d'un moyende transport à un autre*/
         m= typeid(*it).name();
         moyenTrans = getMoyen( m);
      /*calculer le temps du trajet en fonction de la vitesse du moyen de transport emprunté*/
      temps += (dis/moyenTrans->getVitesse()); /* le temps de correspondance sera rajouté au temps entre deux villes*/
    }
  }

  return temps;
}
