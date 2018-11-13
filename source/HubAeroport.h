#ifndef HUB_AEROPORT_H
#define HUB_AEROPORT_H

#include <iostream>
#include "Terminal.h"


class HubAeroport: public Terminal
{
  private:
    const int MAX_LIAISON;

  public:
    HubAeroport(std::string _nom);
    HubAeroport(std::string _nom, double lat, double lng, double temps);
    ~HubAeroport();
    int ajouterLiaison(Terminal* terminal);
    bool estUneGare();
    bool estUnHubMultimodal();
    void afficher();
};
#endif
