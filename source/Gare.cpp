#include "Gare.h"

Gare::Gare(std::string _nom): Terminal(_nom)
{
  std::cout << "Creation de la gare: " << this->nom << std::endl;
}

bool Gare::ajouterLiaison(Terminal* terminal)
{
    if(terminal->estUneGare()) {
      this->liaisons.push_back(terminal);
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
  std::cout << "Latitude: " << this->latitude << std::endl;
  std::cout << "Longitude: " << this->longitude << std::endl;
  std::cout << "Liaisons: " << std::endl;
  for (std::vector<Terminal*>::iterator terminal = liaisons.begin(); terminal != liaisons.end(); ++terminal)
  {
    std::cout << (*terminal)->getNom() << std::endl;
  }
}
