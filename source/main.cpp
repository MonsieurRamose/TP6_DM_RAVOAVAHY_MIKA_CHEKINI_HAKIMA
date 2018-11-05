#include <iostream>
#include "Gare.h"

int main()
{
  Gare plymonth("Plymonth");
  Gare ermont("Ermont");
  plymonth.ajouterLiaison(&ermont);
  plymonth.afficher();
  return 0;
}
