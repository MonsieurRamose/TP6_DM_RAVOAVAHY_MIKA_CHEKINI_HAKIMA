#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <cmath>

class Terminal
{
  protected:
    double latitude;
    double longitude;
    double temps_correspondance;
    std::vector<Terminal*> liaisons; // a revoir selon la classe ligne
    std::string nom;
    std::map<Terminal*, int> flux;
  public:
    Terminal();
    Terminal(std::string _nom);
    Terminal(std::string _nom, double lat, double lng, double temps);
    ~Terminal();

  public:
    double getLatitude() const;
    double getLongitude() const;
    double getTempsCorrespondance() const;
    std::string getNom();
    int getNbLiaisons();
    std::map<Terminal*, int>getFlux() const;
    void setLatitude(double lat);
    void setLongitude(double lng);
    void setTempsCorrespondance(double temps);

    void setNom(std::string _nom);
    void addFlux(Terminal* t, int n);

    double distance(double lat, double lng) const;
    virtual void afficher() ;

    virtual bool ajouterLiaison(Terminal* terminal) = 0;
    virtual bool estUneGare() = 0;
};

#endif
