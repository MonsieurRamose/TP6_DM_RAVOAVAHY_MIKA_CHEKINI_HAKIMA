#ifndef AEROPORT_INTERNATIONAL_H
#define AEROPORT_INTERNATIONAL_H

#include <iostream>
#include "Terminal.h"


class AeroportInternational : public Terminal {
private:
    const int MAX_LIAISON;

public:
    AeroportInternational(std::string _nom);

    AeroportInternational(std::string _nom, double lat, double lng, double temps);

    ~AeroportInternational();

    int ajouterLiaison(Terminal *terminal);

    bool estUneGare();

    void afficher();

    bool estUnHubMultimodal();
};

#endif
