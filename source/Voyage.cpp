#include <iostream>
#include "Voyage.h"


Voyage::Voyage(){
}

Voyage::Voyage(Terminal* _origine, Terminal* _destination)
:origine(_origine), destination(_destination)
{
}

Voyage::~Voyage(){
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

 Terminal*  Voyage::getOrigine()const{
  return origine;
}
Terminal* Voyage::getDestination() const{
  return destination;
}
 std::list<SuperLigne*> Voyage::getLignes() const{
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

/*Cette méthode permet de récupérer le type
 dynamique d’un voyage.(avion, avion électrique, train)*/
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

void Voyage::popBack()
{
  if (!lignes.empty())
  lignes.pop_back();
}


/*Cette méthode renvoie une liste triée des lignes d’un voyage, qui est utile au moment
du calcule du temps de trajet ainsi que l’empreinte carbone consommé.
*/
std::list<SuperLigne*> Voyage::sortLignes(){

  std::list<SuperLigne*> lignescopie;
  /*Copier les lignes dans une liste a part pour ne pas modifier une lignes de depart*/
  for(std::list<SuperLigne *>::iterator itera = lignes.begin(); itera != lignes.end(); itera++)
  {
    lignescopie.push_back(*itera);
  }
  /*Cette liste recevera les lignes triées selon l'odre de depart*/
  std::list<SuperLigne*> lignesTrie;
  std::list<SuperLigne*> ::iterator itTrie = lignesTrie.begin();
  const Terminal* org = this->origine;

  std::list<SuperLigne *> lignevide = {};
  bool present = false;
  for(auto it = lignescopie.begin(); it != lignescopie.end(); it++)
  {
    if((*it)->getOrigine() == this->origine)
    {
      present = true;
    }
  }
  if(!present)
  {
    // il n existe pas de ligne qui desservie la ville origine du voyage
    return lignevide;
  }

  /*Lidée est d'inserer dans la liste ligneTrie, les lignes en suivant l ordre de depart pour arriver a la distination finale,
  tant que la liste de lignes lignescopie n'est pas vide. et a chaque insertion d'une ligne, on enlève cette dernière de
  la liste lignescopie*/
  std::list<SuperLigne*> ::iterator it = lignescopie.begin();
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
    /*il n ya pas de lignes qui mene a la destinatin*/
    return lignescopie; // renvoyer une liste vide
  }
  return lignesTrie;

}

/*Cette méthode permet de calculer le temps de trajet à partir d’un flux de passagers.*/

double Voyage::tempsTrajet() {
  double dis = 0;
  double temps = 0;
  std::list<SuperLigne *>ligneTrie = sortLignes();
  /*s'il n existe pas de chemin qui mene a la destination finale*/
  if(ligneTrie.empty())
  {
    return -1;
  }else{
    std::list<SuperLigne *>::iterator i = ligneTrie.begin();
    if(!((*i)->getOrigine() == this->origine))
    {
      std::cout<<"problème sur origine du voyage"<< std::endl;
      return -1;
    }
    for(std::list<SuperLigne *>::iterator it = ligneTrie.begin(); it != ligneTrie.end(); it++)
    {
      dis = 0;
      /*Calculer la distance entre les deux villes reliées par une ligne*/
      dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(), ((*it)->getDestination())->getLongitude());
      /*additionner tous les temps moyen de correspondance des terminaux d'origine*/
      temps += (*it)->getOrigine()->getTempsCorrespondance();

      /*recuperer le flux de passagers */
      int nbFlux = (*it)->getOrigine()->getNbFluxPassagers((*it)->getDestination());

      /* On doit savoir le moyen de transport emprunté entre deux villes données car la vitesse
       varie d'un moyen de transport à un autre*/
        std::string m= typeid(*it).name();
        Moyens *moyenTrans = getMoyen( m);

      /*mettre a jour la frequence*/
      double freq = floor(nbFlux / moyenTrans->getCapacite());
      (*it)->setFrequence(freq);


      /*calculer le temps du trajet en fonction de la vitesse du moyen de transport emprunté en minutes*/
       /* le temps de correspondance sera rajouté au temps entre deux villes*/
      temps += (dis/(moyenTrans->getVitesse() * 60))  * (*it)->getFrequence();
     }
  }

  return temps;
}

/*Cette méthode permet de calculer l’empreinte carbone associé à un flux de passagers.*/
double Voyage::empreinteCarbone() {

  double empreinteCar = 0;
  double dis = 0;

  std::list<SuperLigne *>ligneTrie = sortLignes();
  if(ligneTrie.empty())
  {
    return -1;
  }else{
    for(std::list<SuperLigne *>::iterator it = ligneTrie.begin(); it != ligneTrie.end(); it++)
    {
      dis = 0;
      /*Calculer la distance entre les deux villes de chaque ligne*/
      dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(), ((*it)->getDestination())->getLongitude());

      /*recuperer le flux de passagers qui sont a l'origine de cette ligne et qui vont aller a la destination de cette ligne*/

      int nbFlux = (*it)->getOrigine()->getNbFluxPassagers((*it)->getDestination());

      /*calculer l'empreinte carbone qui correspond au flux de chaque ville reliée par chaque ligne*/
        std::string m = typeid(*it).name();
      /*savoir le moyen de transport (train ou avion ou avion electrique)*/

      Moyens *moyenTrans = getMoyen( m);

      /*mettre a jour la frequence*/
      double freq = floor(nbFlux / moyenTrans->getCapacite());
      (*it)->setFrequence(freq);


      /*calculer l'empreinte carbone = distance * empreinte du moyen de teransport * nombre de passagers * frequence(nombre de
      trajets par jour en tenant en compte du flux)*/
      empreinteCar += dis * moyenTrans->getEmpreinte() * nbFlux * (*it)->getFrequence();
  }
}

return empreinteCar;
}
/*Redéfinition de l’opérateur == qui renvoie true si deux voyages sont égaux, false sinon.*/

bool Voyage::operator== (Voyage* v){

  if((this->origine == v->getOrigine()) && (this->destination == v->getDestination()) )
  {
      for(std::list<SuperLigne *>::iterator it = this->lignes.begin(); it != this->lignes.end(); it++)
      {

        if ((std::find(v->getLignes().begin(), v->getLignes().end(), (*it))) != v->getLignes().end())
         {
           return false;
         }
      }
      return true;
  }
  return false;
}
