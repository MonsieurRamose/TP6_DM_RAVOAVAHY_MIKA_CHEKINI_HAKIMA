#ifndef GARE_H
#define GARE_H

#include "Terminal.h"
#include <iostream>

class Gare : public Terminal {
public:
    Gare(std::string _nom);

    Gare(std::string _nom, double lat, double lng, double temps);

    ~Gare();

    int ajouterLiaison(Terminal *terminal);

    bool estUneGare();

    bool estUnHubMultimodal();

    void afficher();
};

#endif
