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
#include "HubMultimodal.h"
#include "Tests.h"


int main()
{
  Gare plymonth("Plymonth");
  Gare ermont("Ermont");
  AeroportRegional orly("Orly");

  AeroportInternational cdg("Charles de gaules");
  plymonth.ajouterLiaison(&ermont);
  plymonth.afficher();
  ermont.afficher();

  Terminal *paris = new HubMultimodal("paris", 22,45,20);
  Terminal *CDG = new AeroportInternational("CDG",23,48,10);
  Terminal *lyon = new Gare("lyon", 13,70,15);
  Terminal *lehavre = new HubMultimodal("lehavre", 13,90,65);
  Moyens *train= new Train();
  Terminal *hub = new HubMultimodal("hub", 55,5,10, paris);
  hub->ajouterLiaison(lyon);
  //Moyens *avion= new Avion();
  Avion avion= Avion();
  SuperLigne *ll = new Ligne<AvionElectrique> (paris, lyon, 400);
  SuperLigne *l = new Ligne<Train> ( lyon,lehavre, 400);
  //SuperLigne *lignet = new Ligne<Train> ( lyon,lehavre, 300);
  SuperLigne *lll = new Ligne<Avion> (lehavre ,CDG, 400);

//  Ligne<Avion> l (paris, CDG, 400);
  Ligne<Train> l2(CDG, paris, 3300);
  Voyage v1 (paris, CDG);
  v1.setLignes(ll);
  v1.setLignes(l);
  v1.setLignes(lll);
  //double tempstrajet = v1.tempsTrajet();
  //double empreintecar = v1.empreinteCarbone();
  //std::cout << "le temps de trajet est; " << tempstrajet << std::endl;
  //std::cout << "l'empreinte carbone est; " << empreintecar << std::endl;
  //v1.afficherLignes();
  //l2.afficher();
  //train->afficher();

  //v1.popLignes(l);
  //v1.afficherLignes();

  // CDG->addFlux(paris, 1300);
  // CDG->addFlux(lyon, 1300);
  // CDG->afficher();

Tests t;
double empreinte ;
empreinte = t.TestSenario1(345, "Avion");
std::cout <<"empreinte test1 = " << empreinte << std::endl;




  return 0;
}
