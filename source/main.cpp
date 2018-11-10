#include <iostream>
#include "Gare.h"
#include"Terminal.h"
#include "AeroportRegional.h"
#include "AeroportInternational.h"
#include"Ligne.h"
#include"Train.h"
#include "Avion.h"
#include "SuperLigne.h"
#include "AvionElectrique.h"
#include "Voyage.h"


int main()
{
  Gare plymonth("Plymonth");
  Gare ermont("Ermont");
  AeroportRegional orly("Orly");

  AeroportInternational cdg("Charles de gaules");
  plymonth.ajouterLiaison(&ermont);
  plymonth.afficher();
  ermont.afficher();

  Terminal *paris = new Gare("paris", 22,45,20);
  Terminal *CDG = new AeroportInternational("CDG",23,48,10);
  Terminal *lyon = new Gare("lyon", 13,70,15);
  Moyens *train= new Train();
  //Moyens *avion= new Avion();
  Avion avion= Avion();
  SuperLigne *ll = new Ligne<AvionElectrique> (paris, lyon, 400);
  SuperLigne *l = new Ligne<Train> ( lyon,CDG, 400);

//  Ligne<Avion> l (paris, CDG, 400);
  Ligne<Train> l2(CDG, paris, 3300);
  Voyage v1 (paris, CDG);
  v1.setLignes(ll);
  v1.setLignes(l);
  double tempstrajet = v1.tempsTrajet();
  std::cout << "le temps de trajet est; " << tempstrajet << std::endl;
  //v1.afficherLignes();
  //l2.afficher();
  //train->afficher();

  //v1.popLignes(l);
  //v1.afficherLignes();

  // CDG->addFlux(paris, 1300);
  // CDG->addFlux(lyon, 1300);
  // CDG->afficher();




  return 0;
}
