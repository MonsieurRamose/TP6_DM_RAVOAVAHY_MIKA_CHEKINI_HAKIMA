#include <iostream>
#include "Gare.h"
#include "AeroportRegional.h"
#include "AeroportInternational.h"

int main()
{
  Gare plymonth("Plymonth");
  Gare ermont("Ermont");
  AeroportRegional orly("Orly");

  AeroportInternational cdg("Charles de gaules");
  plymonth.ajouterLiaison(&ermont);
  plymonth.afficher();
  ermont.afficher();
  return 0;
}
