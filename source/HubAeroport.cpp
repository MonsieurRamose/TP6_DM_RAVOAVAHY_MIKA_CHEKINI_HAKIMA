#include "HubAeroport.h"

HubAeroport::HubAeroport(std::string _nom): Terminal(_nom)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
}

HubAeroport::HubAeroport(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps)
{
  std::cout << "Creation du hub aeroport: " << this->nom << std::endl;
  this->afficher();
}

bool HubAeroport::ajouterLiaison(Terminal* terminal)
{
    bool present = false;

    for (std::vector<Terminal*>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison)
    {
      if((*liaison)->getNom() == terminal->getNom())
      {
        present = true;
      }
    }

    if(!terminal->estUneGare() && !present && this->getNbLiaisons() < MAX_LIAISON) {
      this->liaisons.push_back(terminal);
      terminal->ajouterLiaison(this);
      std::cout << "Creation d'une liaison entre " << this->nom << " et "  << terminal->getNom() << std::endl;
      return true;
    }
    return false;
}


bool HubAeroport::estUneGare() {
  return false;
}

void HubAeroport::afficher() {
  std::cout << std::endl;
  std::cout << "HubAeroport de " << this->nom << std::endl;
  std::cout << "Latitude: " << this->latitude << std::endl;
  std::cout << "Longitude: " << this->longitude << std::endl;
  std::cout << "Temps d'attente: " << this->temps_correspondance << std::endl;
  std::cout << "Liaisons: (" << this->getNbLiaisons() << ")" << std::endl;
  for (std::vector<Terminal*>::iterator terminal = liaisons.begin(); terminal != liaisons.end(); ++terminal)
  {
    std::cout << (*terminal)->getNom() << std::endl;
  }
}
