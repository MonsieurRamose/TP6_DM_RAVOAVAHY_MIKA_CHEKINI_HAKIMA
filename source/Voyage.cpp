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

      /* On doit savoir le moyen de transport emprunté entre deux villes données car la vitesse
       varie d'un moyende transport à un autre*/
         m= typeid(*it).name();
         moyenTrans = getMoyen( m);
      /*calculer le temps du trajet en fonction de la vitesse du moyen de transport emprunté en minutes*/
      temps += (dis/(moyenTrans->getVitesse() * 60)); /* le temps de correspondance sera rajouté au temps entre deux villes*/
    }
  }

  return temps;
}

double Voyage::empreinteCarbone(){
  Moyens *moyenTrans;
  double empreinteCar = 0;
  double dis = 0;
  std::string moyenName ;
  std::string m ;
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
      /*calculer l'empreinte carbone qui correspond au flux de chaque ville reliée par chaque ligne*/
      m= typeid(*it).name();
      /*savoir le moyen de transport (train ou avion ou avion electrique)*/
      moyenTrans = getMoyen( m);
      /*Si le flux de passagers depasse la capacite max du moyen de transport,celui ci ne prends que la quantité de Passagers
      qui lui permettra de ne pas depasser sa capacite */
      if((*it)->getFrequence() < moyenTrans->getCapacite())
      {
        // verifier s'il y a de la place
        int placeRestante =  moyenTrans->getCapacite() - (*it)->getFrequence();

        /*recuperer le flux de passagers qui sont a l'origine de cette ligne et qui vont aller a la destination de cette ligne*/

        int nbFlux = (*it)->getOrigine()->getNbFluxPassagers((*it)->getDestination());

        if(nbFlux < placeRestante)
        {
          /*embarquer tous les passagers s'il reste encore de la place
          et metre a jour la frequence de cette ligne*/
          int freq = (*it)->getFrequence() + nbFlux;
          (*it)->setFrequence(freq);
          /*Mettre à jour le flux , ici, tous les passagers sont embarqués donc il ne reste personne qui attend*/
          (*it)->getOrigine()->addFlux((*it)->getDestination(), 0);



        }else{
          /*dans le cas ou il ne reste pas de place pour transporter tous les Passagers
           on ne transporte que le necessaire*/
          int freq = (*it)->getFrequence() + placeRestante;
          /*Mettre a jour la frequance de cette ligne*/
          (*it)->setFrequence(freq);
          /*mettre à jour le flux du terminal*/
          int passagersRestant = nbFlux - placeRestante;
          (*it)->getOrigine()->addFlux((*it)->getDestination(), passagersRestant);

        }
        // calculer l'empreinte carbone = distance * empreinte du moyen de teransport * nombre de passagers
          empreinteCar += dis * moyenTrans->getEmpreinte() * (*it)->getFrequence();

      }else{
        // le moyen de transport est plein
        empreinteCar += dis * moyenTrans->getEmpreinte() * moyenTrans->getCapacite();
      }


  }
  }

return empreinteCar;



}
