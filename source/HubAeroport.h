#ifndef HUB_AEROPORT_H
#define HUB_AEROPORT_H

#include <iostream>
#include "Terminal.h"


class HubAeroport: public Terminal
{
  private:
    const int MAX_LIAISON = 12;

  public:
    HubAeroport(std::string _nom);
    HubAeroport(std::string _nom, double lat, double lng, double temps);
    ~HubAeroport();
    bool ajouterLiaison(Terminal* terminal);
    bool estUneGare();
    void afficher();
};
#endif
