#include "AeroportRegional.h"

AeroportRegional::AeroportRegional(std::string _nom): Terminal(_nom), MAX_LIAISON(1)
{
  std::cout << "Creation de l'aeroport regional: " << this->nom << std::endl;
}

AeroportRegional::AeroportRegional(std::string _nom, double lat, double lng, double temps)
: Terminal(_nom, lat, lng, temps), MAX_LIAISON(1)
{
  std::cout << "Creation de l'aeroport regional: " << this->nom << std::endl;
  this->afficher();
}
AeroportRegional::~AeroportRegional()
  {
    std::cout << "destruction de l AeroportRegional  " << this->getNom() << std::endl;
  }

int AeroportRegional::ajouterLiaison(Terminal* terminal)
{
    if (!terminal->estUneGare())
    {
      if(liaisons.empty())
      {
          this->liaisons.push_back(terminal);
          terminal->ajouterLiaison(this);
          return 0; // liaison ajoutée
      }else{
        return -2; // Un areoport régional est relié qu'avec un seul autre aeroport
      }
    }else{
      return -3; //un aeroport régional n est relié qu avec des aeroports
    }

}


bool AeroportRegional::estUneGare() {
  return false;
}

void AeroportRegional::afficher() {
  std::cout << std::endl;
  std::cout << "AeroportRegional de " << this->nom << std::endl;
  Terminal::afficher();

}
