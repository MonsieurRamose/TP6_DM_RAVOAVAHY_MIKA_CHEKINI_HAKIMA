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
private:
    double empreintecar;
public:
    Tests();

    double getEmpreinte();

    void setEmpreinte(double empreintecar);

    // TEST SUR LES TYPES DE TERMINAL

    static bool TestGare();
    static bool TestAeroportInternational();
    static bool TestAeroportRegional();

    // FIN TEST TYPE TERMINAL

    static void FluxVilles(Terminal *paris, Terminal *rome, Terminal *lyon, Terminal *naples, Terminal *bruxelles);

    void
    TousVoyagesPossibles(std::list<Voyage *> &voyages, Scenario *s, Terminal *terminaux[], int n, std::string sceario);

    void ToutesLignesExistantes(std::vector<SuperLigne *> lignes, Terminal *terminaux[], int n);

    void RemplirLignes(Voyage *v, Terminal *org, Terminal *dest, std::vector<SuperLigne *> lignesEx);

    void AfficherVoyagesScenario(Scenario *s);

    Scenario *TestSenario1(double maxTemps, std::string moy);

    static bool TestSenario2();

    static double TestSenario3();

    static double TestSenario4();

    static double TestSenario5();

    static double TestSenario6();

    void TestPl();

};


#endif
