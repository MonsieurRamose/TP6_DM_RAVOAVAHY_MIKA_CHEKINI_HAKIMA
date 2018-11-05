#ifndef HUB_MULTIMODAL_H
#define HUB_MULTIMODAL_H

#include <iostream>
#include "Terminal.h"
#include "Gare.h"


class HubMultimodal: public Terminal
{
  private:
    const int MAX_LIAISON = 12;
    Gare* gare;

  public:
    HubMultimodal(std::string _nom);
    HubMultimodal(std::string _nom, double lat, double lng, double temps);
    HubMultimodal(std::string _nom, double lat, double lng, double temps, Gare* g);
    ~HubMultimodal();
    const Gare* getGare() const;
    void setGare(Gare* g);
    bool ajouterLiaison(Terminal* terminal);
    bool estUneGare();
    void afficher();
};
#endif
