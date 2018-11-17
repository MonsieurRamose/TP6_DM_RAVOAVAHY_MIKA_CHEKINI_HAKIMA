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
# include <vector>
#include "Voyage.h"


class Tests {

public:
  Tests();
   double getEmpreinte();
   void setEmpreinte(double empreintecar);
  static void FluxVilles(Terminal * paris, Terminal *rome, Terminal *lyon, Terminal *naples, Terminal *bruxelles );
  void TousVoyagesPossibles(std::list <Voyage*> &voyages,Scenario* s, Terminal* terminaux[],int n);
  void ToutesLignesExistantes( std::vector<SuperLigne*>lignes, Terminal* terminaux[], int n) ;
  void RemplirLignes(Voyage* v , Terminal* org,Terminal* dest, std::vector<SuperLigne*> lignesEx);
  double TestSenario1(double maxTemps, std::string scenario);
  double TestSenario2(double maxTemps, std::string scenario);
  double TestSenario3(double maxTemps, std::string scenario);
  double TestSenario4(double maxTemps, std::string scenario);
  double TestSenario5(double maxTemps, std::string scenario);
  double TestSenario6(double maxTemps, std::string scenario);
  double calculerEmpreinteVoyages(double maxTemps, Scenario* scenario1, std::list <Voyage*> voyages);
  double ChoisirScenario(int Maxtemps, int n, int& scenario);
   double minEmpreinteScenario(double empScenario[], int n, int& scenario);
  void scenarioGagant(int indice);
  void EtudeDeCas();
  void TestPl();

};


#endif
