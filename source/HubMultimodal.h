#ifndef HUB_MULTIMODAL_H
#define HUB_MULTIMODAL_H

#include <iostream>
#include "Terminal.h"
#include "Gare.h"


class HubMultimodal : public Terminal {
private:
    const int MAX_LIAISON;
    Terminal *gare;

public:
    HubMultimodal(std::string _nom);

    HubMultimodal(std::string _nom, double lat, double lng, double temps);

    HubMultimodal(std::string _nom, double lat, double lng, double temps, Terminal *g);

    ~HubMultimodal();

    const Terminal *getGare() const;

    void setGare(Gare *g);

    int ajouterLiaison(Terminal *terminal);

    bool estUneGare();

    bool estUnHubMultimodal();

    void afficher();
};

#endif
