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
double Voyage::TempsTrajet() {
  double dis = 0;
  double temps = 0;
  Moyens *moyenTrans;
  std::string moyenName ;
  std::string m ;
  for(std::list<SuperLigne *>::iterator it = lignes.begin(); it != lignes.end(); it++)
  {
    dis = 0;
    /*Calculer la distance entre les deux villes reliées par une ligne*/
    dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(), ((*it)->getDestination())->getLongitude());
    /*additionner tous les temps moyen de correspondance des terminaux d'origine*/
    temps += (*it)->getOrigine()->getTempsCorrespondance();

    /* On doit savoir le moyen de transport emprunté entre deux villes données car la vitesse
     varie d'un moyende transport à un autre*/
       m= typeid(lignes).name();
       moyenTrans = getMoyen( m);
    /*calculer le temps du trajet en fonction de la vitesse du moyen de transport emprunté*/
    temps += (dis/moyenTrans->getVitesse()); /* le temps de correspondance sera rajouté au temps entre deux villes*/
  }
  return temps;
}


double Voyage::EmpreinteCarbone(){
  Moyens *moyenTrans;
  double empreinteCar = 0;
  double dis = 0;
  std::string moyenName ;
  std::string m ;
  for(std::list<SuperLigne *>::iterator it = lignes.begin(); it != lignes.end(); it++)
  {
    dis = 0;
    /*Calculer la distance entre les deux villes de chaque ligne*/
    dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(), ((*it)->getDestination())->getLongitude());
    /*calculer l'empreinte carbone qui correspond au flux de chaque ville reliée par chaque ligne*/
    m= typeid(lignes).name();
    moyenTrans = getMoyen( m);
    /*Si le flux de passagers depasse la capacite max du moyen de transport,celui ci ne prends que la quantité de Passagers
    qui lui permettra de ne pas depasser sa capacite */
    if((*it)->getFrequence() < moyenTrans->getCapacite())
    {
      // verifier s'il y a de la place
      int placeRestante =  moyenTrans->getCapacite() - (*it)->getFrequence();
      std::map<Terminal*, int>::iterator fx = (*it)->getOrigine()->getFlux();
      if(fx->second < placeRestante)
      {
        // embarquer tous les passagers s'il reste encore de la place
        (*it)->setFrequence(fx->second);
      }else{
        //dans le cas ou il ne reste pas de place pour transporter tous les Passagers
        // on ne transporte que le necessaire
        int aTransporter = fx->second - (*it)->getFrequence();
        (*it)->setFrequence(aTransporter);
        // mettre à jour le flux du terminal
        // !!!!!!!!!!! rajouter dans la classe terminal une methode pour mof=difier le flux ou bien directement addFlux

      }
      // calculer l'empreinte carbone = distance * empreinte du moyen de teransport * nombre de passagers
        empreinteCar += dis * moyenTrans->getEmpreinte() * (*it)->getFrequence();

    }else{
      // le moyen de transport est plein
      empreinteCar += dis * moyenTrans->getEmpreinte() * moyenTrans->getCapacite();
    }


}




}
