#ifndef SCENARIO_H
#define SCENARIO_H

#include <iostream>
#include <string>
#include "Voyage.h"


class Scenario {
private:
    std::string nom;
    std::list<Voyage *> voyages;

public:
    Scenario();

    Scenario(std::string nom);

    ~Scenario();


    std::string getNom() const;

    std::list<Voyage *> getVoyages() const;

    void addVoyage(Voyage *);

    void afficherVoyages();


};

#endif
