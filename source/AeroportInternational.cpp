#include "AeroportInternational.h"

AeroportInternational::AeroportInternational(std::string _nom): Terminal(_nom), MAX_LIAISON(4)
{
  std::cout << "Creation de l'aeroport international: " << this->nom << std::endl;
}

AeroportInternational::AeroportInternational(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps), MAX_LIAISON(4)
{
  std::cout << "Creation de l'aeroport international: " << this->nom << std::endl;
  this->afficher();
}

  AeroportInternational::~AeroportInternational()
  {
    std::cout << "destruction de l AeroportInternational  " << this->getNom() << std::endl;
  }
int AeroportInternational::ajouterLiaison(Terminal* terminal)
{
    bool present = false;

    for (std::vector<Terminal*>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison)
    {
      if((*liaison)->getNom() == terminal->getNom())
      {
        present = true;
      }
    }

    if(!terminal->estUneGare())
    {
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
    }else{
      return -5; //un aeroport international n est relie qu avec des aeroports
    }

  /*  if(!terminal->estUneGare() && !present && this->getNbLiaisons() < MAX_LIAISON) {
      this->liaisons.push_back(terminal);
      terminal->ajouterLiaison(this);
      std::cout << "Creation d'une liaison entre " << this->nom << " et "  << terminal->getNom() << std::endl;
      return true;
    }
    return false;*/
}


bool AeroportInternational::estUneGare() {
  return false;
}

bool AeroportInternational::estUnHubMultimodal(){
  return false;
}
void AeroportInternational::afficher() {
  std::cout << std::endl;
  std::cout << "AeroportInternational de " << this->nom << std::endl;
  Terminal::afficher();
}
