#include <iostream>
#include "Gare.h"
#include"Terminal.h"
#include "AeroportRegional.h"
#include "AeroportInternational.h"
#include"Ligne.h"
#include"Train.h"
#include "Avion.h"


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
  Moyens *train= new Train();
  //Moyens *avion= new Avion();
  Avion avion= Avion();
  Ligne<Avion> l (paris, CDG, 400);
  Ligne<Train> l2(CDG, paris, 400);


  return 0;
}
