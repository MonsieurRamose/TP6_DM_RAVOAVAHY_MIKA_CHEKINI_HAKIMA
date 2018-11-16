#include "Gare.h"

Gare::Gare(std::string _nom) : Terminal(_nom) {
    std::cout << "Creation de la gare: " << this->nom << std::endl;
}

Gare::Gare(std::string _nom, double lat, double lng)
        : Terminal(_nom, lat, lng, 0) {
    std::cout << "Creation de la gare: " << this->nom << std::endl;
    this->afficher();
}

Gare::Gare(std::string _nom, double lat, double lng, double temps)
        : Terminal(_nom, lat, lng, temps) {
    std::cout << "Creation de la gare: " << this->nom << std::endl;
    this->afficher();
}

Gare::~Gare() {
    for (std::vector<Terminal *>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison) {
        (*liaison) = NULL;
    }
    liaisons.clear();
    std::cout << "destruction de la gare  " << this->getNom() << std::endl;
}

int Gare::ajouterLiaison(Terminal *terminal) {
    bool present = false;

    for (std::vector<Terminal *>::iterator liaison = liaisons.begin(); liaison != liaisons.end(); ++liaison) {
        if ((*liaison)->getNom() == terminal->getNom()) {
            present = true;
        }
    }
    /*une gare permet de circuler que des train;
    vérifier que le terminal qu'on veut ajouter est une gare et qu'il n'est pas lié à la gare*/

    if (terminal->estUneGare() || terminal->estUnHubMultimodal()) {
        if (!present) {
            this->liaisons.push_back(terminal);
            terminal->ajouterLiaison(this);
            return 1; // ajout d une liaison avec le terminal donné en paramètre
        } else {
            return 0; // la gare est deja ete liee au terminal passé en paramètre
        }
    } else {
        return -1; // une gare ne peut etre liée qu'avec des gares ou des HubMultimodal
    }
}


bool Gare::estUneGare() {
    return true;
}

bool Gare::estUnHubMultimodal() {
    return false;
}

void Gare::afficher() {
    std::cout << std::endl;
    std::cout << "Gare de " << this->nom << std::endl;
    Terminal::afficher();
}
