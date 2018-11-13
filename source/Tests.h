#ifndef TESTS_H
#define  TESTS_H
#include "Terminal.h"
#include "AeroportRegional.h"
#include "AeroportInternational.h"
#include "Gare.h"
#include "HubAeroport.h"
#include "HubMultimodal.h"
#include "Scenario.h"
#include "Moyens.h"
#include "SuperLigne.h"
#include "Ligne.h"
#include "Train.h"
#include "Avion.h"
#include "AvionElectrique.h"


class Tests {
private:
  double empreintecar ;
public:
  Tests();
   double getEmpreinte();
   void setEmpreinte(double empreintecar);
  static void FluxVilles(Terminal * paris, Terminal *rome, Terminal *lyon, Terminal *naples, Terminal *bruxelles );
  double TestSenario1(double maxTemps, std::string moy);
  static double TestSenario2();
  static double TestSenario3();
  static double TestSenario4();
  static double TestSenario5();
  static double TestSenario6();


};


#endif
