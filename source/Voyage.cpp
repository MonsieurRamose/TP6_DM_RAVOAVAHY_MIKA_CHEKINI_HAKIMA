#include <iostream>
#include "Voyage.h"


Voyage::Voyage() {
}

Voyage::Voyage(Terminal *_origine, Terminal *_destination)
        : origine(_origine), destination(_destination) {
}

Voyage::~Voyage() {
    for (typename std::list<SuperLigne *>::iterator it = lignes.begin(); it != lignes.end(); it++) {
        if ((*it) != NULL) {
            delete (*it);
            (*it) = NULL;
        }
    }
    lignes.clear();
}

Terminal *Voyage::getOrigine() const {
    return origine;
}

Terminal *Voyage::getDestination() const {
    return destination;
}

std::list<SuperLigne *> Voyage::getLignes() const {
    return lignes;
}

void Voyage::setOrigine(Terminal *o) {
    origine = o;
}

void Voyage::setDestination(Terminal *d) {
    destination = d;
}

void Voyage::setLignes(SuperLigne *s) {
    if (s != NULL)
        lignes.push_back(s);
}

bool Voyage::popLignes(SuperLigne *s) {
    int taille = lignes.size();
    if (!lignes.empty()) {
        lignes.remove(s);
    } else {
        return false;
    }
    if (taille == lignes.size()) {
        //si la ligne n'a pas été retirée
        return false;
    } else {
        return true;
    }

}

void Voyage::afficherLignes() {
    std::cout << "Les lignes du voyage entre " << origine->getNom() << " et " << destination->getNom() << " sont: "
              << std::endl;

    for (std::list<SuperLigne *>::iterator it = lignes.begin(); it != lignes.end(); it++) {
        (*it)->afficher();
    }
}

Moyens *Voyage::getMoyen(std::string &m) const {
    if (m.compare("5Train") == 0) {
        return new Train();
    } else {
        if (m.compare("5Avion") == 0) {
            return new Avion();
        } else {
            return new AvionElectrique();
        }
    }
}

std::list<SuperLigne *> Voyage::sortLignes() {

    std::list < SuperLigne * > lignescopie;
    /*Copier les lignes dans une liste a part pour ne pas modifier une lignes de depart*/
    for (std::list<SuperLigne *>::iterator itera = lignes.begin(); itera != lignes.end(); itera++) {
        lignescopie.push_back(*itera);
    }
    /*Cette liste recevera les lignes triées selon l'odre de depart*/
    std::list < SuperLigne * > lignesTrie;
    std::list<SuperLigne *>::iterator itTrie = lignesTrie.begin();
    const Terminal *org = this->origine;

    std::list < SuperLigne * > lignevide;
    bool present = false;
    for (std::list< SuperLigne * >::iterator it = lignescopie.begin(); it != lignescopie.end(); it++) {
        if ((*it)->getOrigine() == this->origine) {
            present = true;
        }
    }
    if (!present) {
        // il n existe pas de ligne qui desservie la ville origine du voyage
        return lignevide;
    }

    /*Lidée est d'inserer dans la liste ligneTrie, les lignes en suivant l ordre de depart pour arriver a la distination finale,
    tant que la liste de lignes lignescopie n'est pas vide. et a chaque insertion d'une ligne, on enlève cette dernière de
    la liste lignescopie*/
    std::list<SuperLigne *>::iterator it = lignescopie.begin();
    while (!lignescopie.empty()) {
        if (it == lignescopie.end()) {
            it = lignescopie.begin();
        }
        if ((*it)->getOrigine() == org) {
            lignesTrie.push_back(*it);
            itTrie++;
            org = (*it)->getDestination();
            /*supprimer la ligne de la liste lignescopie*/
            lignescopie.remove(*it);
            it--;
        } else {
            it++;
        }
    }

    if (org != this->destination) {
        std::cout << "Il n ya pas de ligne qui ramène à " << this->destination->getNom() << std::endl;
        return lignescopie; // renvoyer une liste vide
    }
    return lignesTrie;

}


double Voyage::tempsTrajet() {
    double dis = 0;
    double temps = 0;
    Moyens *moyenTrans;
    std::string moyenName;
    std::string m;
    std::list < SuperLigne * > ligneTrie = sortLignes();
    /*s'il n existe pas de chemin qui mene a la destination finale*/
    if (ligneTrie.empty()) {
        return -1;
    } else {
        std::list<SuperLigne *>::iterator i = ligneTrie.begin();
        if (!((*i)->getOrigine() == this->origine)) {
            std::cout << "problème sur origine du voyage" << std::endl;
            return -1;
        }
        for (std::list<SuperLigne *>::iterator it = ligneTrie.begin(); it != ligneTrie.end(); it++) {
            dis = 0;
            /*Calculer la distance entre les deux villes reliées par une ligne*/
            dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(),
                                                 ((*it)->getDestination())->getLongitude());
            /*additionner tous les temps moyen de correspondance des terminaux d'origine*/
            temps += (*it)->getOrigine()->getTempsCorrespondance();

            /*recuperer le flux de passagers */
            int nbFlux = (*it)->getOrigine()->getNbFluxPassagers((*it)->getDestination());

            /* On doit savoir le moyen de transport emprunté entre deux villes données car la vitesse
             varie d'un moyen de transport à un autre*/
            m = typeid(*it).name();
            moyenTrans = getMoyen(m);

            /*mettre a jour la frequence*/
            double freq = floor(nbFlux / moyenTrans->getCapacite());
            (*it)->setFrequence(freq);


            /*calculer le temps du trajet en fonction de la vitesse du moyen de transport emprunté en minutes*/
            /* le temps de correspondance sera rajouté au temps entre deux villes*/
            temps += (dis / (moyenTrans->getVitesse() * 60)) * (*it)->getFrequence();
        }
    }

    return temps;
}

double Voyage::empreinteCarbone() {

    double empreinteCar = 0;
    double dis = 0;

    std::list < SuperLigne * > ligneTrie = sortLignes();
    if (ligneTrie.empty()) {
        return -1;
    } else {
        for (std::list<SuperLigne *>::iterator it = ligneTrie.begin(); it != ligneTrie.end(); it++) {
            dis = 0;
            /*Calculer la distance entre les deux villes de chaque ligne*/
            dis += (*it)->getOrigine()->distance(((*it)->getDestination())->getLatitude(),
                                                 ((*it)->getDestination())->getLongitude());

            /*recuperer le flux de passagers qui sont a l'origine de cette ligne et qui vont aller a la destination de cette ligne*/

            int nbFlux = (*it)->getOrigine()->getNbFluxPassagers((*it)->getDestination());

            /*calculer l'empreinte carbone qui correspond au flux de chaque ville reliée par chaque ligne*/
            std::string m = typeid(*it).name();
            /*savoir le moyen de transport (train ou avion ou avion electrique)*/

            Moyens *moyenTrans = getMoyen(m);

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


bool Voyage::operator==(Voyage *v) {

    if ((this->origine == v->getOrigine()) && (this->destination == v->getDestination())) {
        for (std::list<SuperLigne *>::iterator it = this->lignes.begin(); it != this->lignes.end(); it++) {

            if ((std::find(v->getLignes().begin(), v->getLignes().end(), (*it))) != v->getLignes().end()) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/*
int Voyage::position(Terminal *t, Terminal* terminaux[])
{
  for (int i = 0; i < 5; i++) {
    if(t == terminaux[i])
    {
      return i;
    }
  }
  return -1;
}
void Voyage::PlusCourtChemin(std::list<SuperLigne *> chemin, std::string moyen, Terminal* terminaux[], int n, std::list<SuperLigne *> leslignes)
{

    Terminal* start = this->getOrigine();

    std::queue<std::pair<Terminal*, long> > file;
    file.push(std::make_pair(start, 1));

    //double n = this->getLignes().size()-1;

    std::vector<bool> visited(n) ;
    for (int i=0; i < n; i++)
      {
        visited.at(i)= false;
      }

      //std::cout<<" visited size "<< this->getLignes().size()<<std::endl;

    long maxDis = 10000000;

    while (!file.empty())
    {
        Terminal* u = file.front().first;
        long dis = file.front().second;
        file.pop();
        visited.at(position(u, terminaux)) = true;

          std::cout << "dejjjjjjjjjjjjon  "<< u->getNom() << " " << position(u, terminaux)<< std::endl;
        for(std::vector<Terminal*>::iterator it = u->getLiasons().begin(); it != u->getLiasons().end(); it++)
        {
          std::cout << "destination " << (*it)->getNom() << std::endl;
            Terminal* destination = (*it);
            if (!visited.at(position(destination, terminaux)))
            {

                if ((*it)->getNom().compare(this->getDestination()->getNom()) == 0)
                    {
                      maxDis = std::min(maxDis, dis);
                      SuperLigne* ligne = existeLigne(start, *it, moyen, leslignes);
                      if(ligne != NULL)
                      {
                        chemin.push_back(ligne);
                        start = (*it);
                      }

                    }
                file.push(std::make_pair(destination, dis + 1));
            }
        }

}
}

 SuperLigne* Voyage::existeLigne(Terminal* start,Terminal* l, std::string moyen, std::list<SuperLigne *> leslignes) {

    for(std::list<SuperLigne *>::iterator it = leslignes.begin(); it != leslignes.end(); it++)
    {
     if( (*it)->getOrigine()->getNom().compare(start->getNom()) == 0 && (*it)->getDestination()->getNom().compare(l->getNom()) == 0)
     {
       return (*it);
     }
      /*{
        if(moyen.compare("Avion") == 0)
        {
          return new Ligne<Avion> (this->origine,l,0 );
        }else
          if(moyen.compare("AvionElectrique") == 0)
          {
            return new Ligne<AvionElectrique> (this->origine,l,0 );
          }else{
            return new Ligne<Train> (this->origine,l,0 );
          }
      }*/

/*
    }
    return NULL;
}
*/
