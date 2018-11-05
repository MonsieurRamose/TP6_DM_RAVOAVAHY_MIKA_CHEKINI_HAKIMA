#ifndef HUB_MULTIMODAL_H
#define HUB_MULTIMODAL_H

#include <iostream>
#include "Terminal.h"


class HubMultimodal: public Terminal
{
  private:
    const int MAX_LIAISON = 12;

  public:
    HubMultimodal(std::string _nom);
    HubMultimodal(std::string _nom, double lat, double lng, double temps);
    bool ajouterLiaison(Terminal* terminal);
    bool estUneGare();
    void afficher();
};
#endif
