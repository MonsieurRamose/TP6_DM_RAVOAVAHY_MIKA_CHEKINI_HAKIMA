#include "HubMultimodal.h"

HubMultimodal::HubMultimodal(std::string _nom): Terminal(_nom), MAX_LIAISON(12)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
}

HubMultimodal::HubMultimodal(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps), MAX_LIAISON(12)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
  this->afficher();
}
HubMultimodal::HubMultimodal(std::string _nom, double lat, double lng, double temps, Terminal* g)
:Terminal(_nom, lat, lng, temps), MAX_LIAISON(12)
{
  try{
    if(g == NULL)
    {
      throw std::string ("Terminal NULL");
    }else{
      if(!g->estUneGare())
      {
        throw std::string ("le Terminal doit etre une gare");
      }else{
        gare = g;
      }
    }
  }
  catch(std::string const& chaine)
  {
     std::cerr << chaine << std::endl;
  }


  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
  this->afficher();
}
const Terminal * HubMultimodal::getGare() const
{
  return gare;
}

void HubMultimodal::setGare(Gare* g)
{
  gare = g;
}
HubMultimodal::~HubMultimodal()
{
  std::cout << "destruction du HubMultimodal " << this->getNom()<< std::endl;
}
int HubMultimodal::ajouterLiaison(Terminal* terminal)
{
    bool present = false;
    int nbGare = 0;
    for (std::vector<Terminal*>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison)
    {
      if((*liaison)->getNom() == terminal->getNom())
      {
        present = true;
      }
      if((*liaison)->estUneGare())
      {
        nbGare += 1;
      }
    }
    /*si le hub a deja une gare et que le terminal en paramètre est une gare, on n'ajoute pas
    de liaison avec le terminal en paramètre*/
    if(nbGare != 0 && terminal->estUneGare())
    {
      /*Un HubMultimodal est muni que d'une seule gare*/
      return -4;
    }else{
      if( !present)
      {
        if(this->getNbLiaisons() < MAX_LIAISON)
        {
          this->liaisons.push_back(terminal);
          terminal->ajouterLiaison(this);
          return 0; // ajout du terminal
        }else{
          return -2; // complet
        }
      }else{
        return -1; // deja present
      }
    }

}


bool HubMultimodal::estUneGare() {
  return false;
}

void HubMultimodal::afficher() {
  std::cout << std::endl;
  std::cout << "HubMultimodal de " << this->nom << std::endl;
  Terminal::afficher();
  if(gare != NULL)
  std::cout << "HubMultimodal: " << this->nom << " a comme gare: "<< this->gare->getNom() << std::endl;

}
