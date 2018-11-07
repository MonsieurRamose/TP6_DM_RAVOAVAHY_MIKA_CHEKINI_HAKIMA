#include "Gare.h"

Gare::Gare(std::string _nom): Terminal(_nom)
{
  std::cout << "Creation de la gare: " << this->nom << std::endl;
}

Gare::Gare(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps)
{
  std::cout << "Creation de la gare: " << this->nom << std::endl;
  this->afficher();
}

  Gare::~Gare()
  {
    std::cout << "destruction de la gare  " << this->getNom() << std::endl;
     }

bool Gare::ajouterLiaison(Terminal* terminal)
{
    bool present = false;

    for (std::vector<Terminal*>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison)
    {
      if((*liaison)->getNom() == terminal->getNom())
      {
        present = true;
      }
    }

    if(terminal->estUneGare() && !present) {
      this->liaisons.push_back(terminal);
      terminal->ajouterLiaison(this);
      std::cout << "Creation d'une liaison entre " << this->nom << " et "  << terminal->getNom() << std::endl;
      return true;
    }
    return false;
}


bool Gare::estUneGare() {
  return true;
}

void Gare::afficher() {
  std::cout << std::endl;
  std::cout << "Gare de " << this->nom << std::endl;
  Terminal::afficher();
}
