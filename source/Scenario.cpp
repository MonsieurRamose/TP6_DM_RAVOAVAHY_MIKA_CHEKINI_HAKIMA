#include "Scenario.h"


Scenario::Scenario() {

}

Scenario::Scenario(std::string _nom) : nom(_nom) {

}


Scenario::~Scenario() {

}

std::string Scenario::getNom() const {
    return nom;
}

std::list<Voyage *> Scenario::getVoyages() const {
    return voyages;
}

void Scenario::addVoyage(Voyage *v) {
    bool found = false;
    try {
        if (v == NULL) {
            throw std::string("Voyage NULL");
        } else {
            for (std::list<Voyage *>::iterator it = this->getVoyages().begin(); it != this->getVoyages().end(); it++) {
                if ((*it) == v)
                    found = true;
            }
            if (!found)
                voyages.push_back(v);
        }
    }
    catch (std::string const &chaine) {
        std::cerr << chaine << std::endl;
    }

}

/*Affiche tous les voyages d un scenario ainsi que ses lignes */
void Scenario::afficherVoyages() {

    std::cout << "Les voyages du " << this->getNom() << " sont: " << std::endl;

    for (std::list<Voyage *>::iterator it = this->voyages.begin(); it != voyages.end(); it++) {
        (*it)->afficherLignes();
    }
}
