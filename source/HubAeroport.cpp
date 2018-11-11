#include "HubAeroport.h"

HubAeroport::HubAeroport(std::string _nom): Terminal(_nom), MAX_LIAISON(12)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
}

HubAeroport::HubAeroport(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps), MAX_LIAISON(12)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
  this->afficher();
}

HubAeroport::~HubAeroport()
{
  std::cout << "Destruction du HubAeroport" << this->getNom() << std::endl;
}

int HubAeroport::ajouterLiaison(Terminal* terminal)
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
      return -3; //un aeroport international n est relie qu avec des aeroports
    }
  /*  if(!terminal->estUneGare() && !present && this->getNbLiaisons() < MAX_LIAISON) {
      this->liaisons.push_back(terminal);
      terminal->ajouterLiaison(this);
      std::cout << "Creation d'une liaison entre " << this->nom << " et "  << terminal->getNom() << std::endl;
      return true;
    }
    return false;*/
}


bool HubAeroport::estUneGare() {
  return false;
}

void HubAeroport::afficher() {
  std::cout << std::endl;
  std::cout << "HubAeroport de " << this->nom << std::endl;
  Terminal::afficher();
}
