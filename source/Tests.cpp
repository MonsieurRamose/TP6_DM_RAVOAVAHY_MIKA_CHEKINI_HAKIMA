#include "Tests.h"


Tests::Tests() : empreintecar(0) {

}

double Tests::getEmpreinte() {
    return empreintecar;
}

void Tests::setEmpreinte(double emp) {
    empreintecar = emp;
}

void Tests::FluxVilles(Terminal *paris, Terminal *rome, Terminal *lyon, Terminal *naples, Terminal *bruxelles) {
    bruxelles->addFlux(paris, 13000);
    bruxelles->addFlux(lyon, 5500);
    bruxelles->addFlux(rome, 4500);
    bruxelles->addFlux(naples, 2000);

    paris->addFlux(bruxelles, 12500);
    paris->addFlux(lyon, 18000);
    paris->addFlux(rome, 10000);
    paris->addFlux(naples, 4000);

    lyon->addFlux(bruxelles, 6000);
    lyon->addFlux(paris, 19000);
    lyon->addFlux(rome, 6500);
    lyon->addFlux(naples, 2500);

    rome->addFlux(bruxelles, 5000);
    rome->addFlux(paris, 9000);
    rome->addFlux(lyon, 6000);
    rome->addFlux(naples, 11000);

    naples->addFlux(bruxelles, 2500);
    naples->addFlux(paris, 5000);
    naples->addFlux(lyon, 3000);
    naples->addFlux(rome, 10000);

}

void Tests::TousVoyagesPossibles(std::list<Voyage *> &voyages, Scenario *s1, Terminal *terminaux[], int n,
                                 std::string scenario) {
    /*instanciation de tous les voyages possibles entre les villes
    et l ajout a un scenario*/
    //Scenario* s1 = new Scenario(scenario);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                Voyage *v = new Voyage(terminaux[i], terminaux[j]);
                //  std::cout << "okokoko"<< v->getOrigine()->getNom() << " to " << v->getDestination()->getNom();
                //ajouetr les lignes
                //  s1->addVoyage(v);
                voyages.push_back(v);
                //std::cout <<v->getLignes().size() << std::endl;
                std::cout << voyages.size() << std::endl;
            }
        }
    }
    //return s1; /*****************/
}



/*void Tests::remplirTerminaux(std::vector<SuperLigne*> lignesEx, terminal* [])
{
    for(std::vector<SuperLigne *>::iterator it = lignesEx.begin(); it != lignesEx.end(); it++)
    {

    }
}
*/

/*Cette methode renvoi un voyage rempli avec les lignes necessaires pour pour atteindre sa destination*/

void Tests::RemplirLignes(Voyage *v, Terminal *org, Terminal *dest, std::vector<SuperLigne *> lignesEx) {
    bool arrive = false;
    //Voyage* v = new Voyage(org, dest);
//while(!arrive)
//  {

    for (std::vector<SuperLigne *>::iterator it = lignesEx.begin(); it != lignesEx.end(); it++) {
        /*chercher la ligne qui a comme origine, l origine du voyage donne en parametre*/
        if (org == (*it)->getOrigine()) {
            if (dest == (*it)->getDestination()) {
                arrive = true;
                /*ajouter la ligne au voyage*/
                v->setLignes((*it));
                return; // sortit de la boucle
            }//else{
            /*ajouter la ligne et passer a la prochaine ligne en mettant la distination de cette derniere comme origine*/
            v->setLignes((*it)); /* !!!!!!!!!!!!!!!!!! ça c est un probleme il faut d abord verifier qu il y a un chemin puis l inserer

          /*changer l origine du voyage et appler recursivement */
            org = (*it)->getDestination();

        }
    }


}


Scenario *Tests::TestSenario1(double maxTemps, std::string moyenTrans) {

    /* Instanciation des terminaux du scénario1*/

    Terminal *paris = new HubAeroport("Paris", 48, 2, 45);
    Terminal *rome = new AeroportInternational("Rome", 41, 12, 30);
    Terminal *lyon = new AeroportRegional("Lyon", 45, 4, 30);
    Terminal *naples = new AeroportRegional("Naples", 40, 14, 30);
    Terminal *bruxelles = new AeroportRegional("Bruxelles", 50, 4, 30);

    /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
    FluxVilles(paris, rome, lyon, naples, bruxelles);


    SuperLigne *parisRome_L = new Ligne<Avion>(paris, rome, 0);
    SuperLigne *parisLyon_L = new Ligne<Avion>(paris, lyon, 0);
    SuperLigne *parisBruxelles_L = new Ligne<Avion>(paris, bruxelles, 0);
    SuperLigne *romeNaples_L = new Ligne<Avion>(rome, naples, 0);
    //ToutesLignesExistantes(lesLignes, terminaux,5);
    /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */

    std::vector < SuperLigne * > lesLignes;
    lesLignes.push_back(parisRome_L);
    lesLignes.push_back(parisLyon_L);
    lesLignes.push_back(parisBruxelles_L);
    lesLignes.push_back(romeNaples_L);

    /*création d'un tablea de tous les terminaux du scenario*/

    Terminal *terminaux[5] = {paris, rome, lyon, naples, bruxelles};

    /*methode qui instancie tous les voyages possibles entre les villes
    et les ajoute a un scenario*/

    Scenario *scenario1;
    std::list < Voyage * > voyages;
    TousVoyagesPossibles(voyages, scenario1, terminaux, 5, "scenario1");


    //std::list <Voyage*>::iterator it= voyages.begin();
    //std::advance(it, 5);
    //scenario1->getVoyages().push_back(*it);
    std::cout << " dans la methode testscenario1 " << voyages.size() << std::endl;

    for (std::list<Voyage *>::iterator it = voyages.begin(); it != voyages.end(); it++) {
        //(*it)->setLignes();
        //scenario1->addVoyage(*it);
        //scenario1->getVoyages().push_back(*it);
        RemplirLignes((*it), (*it)->getOrigine(), (*it)->getDestination(), lesLignes);
        std::cout << "voyage" << ((*it)->getOrigine())->getNom() << " to " << ((*it)->getDestination())->getNom()
                  << (*it)->getLignes().size() << std::endl;

    }



    /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
     de lignes avec les lignes necessaires pour pour atteindre sa destination */

    // for(std::list<Voyage *>::iterator it = scenario1->getVoyages().begin(); it != scenario1->getVoyages().end(); it++)
    // {
    //   RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
    // }
    return scenario1;
}


static void TestSenario2() {

}

static void TestSenario3() {

}

static void TestSenario4() {

}

static void TestSenario5() {

}

static void TestSenario6() {

}


void Tests::TestPl() {
    std::list < SuperLigne * > chemin;

    Terminal *edimbourg = new AeroportInternational("edimbourg ", 26, 48, 10);
    Terminal *douvres = new AeroportInternational("douvres", 23, 49, 30);
    Terminal *calais = new AeroportInternational("calais", 17, 48, 20);
    Terminal *paris = new AeroportInternational("paris", 23, 15, 19);
    Terminal *londres = new AeroportInternational("londres", 23, 98, 16);

    Voyage *v1 = new Voyage(edimbourg, calais);

    SuperLigne *l1 = new Ligne<AvionElectrique>(edimbourg, douvres, 0);
    SuperLigne *l2 = new Ligne<AvionElectrique>(douvres, calais, 0);
    SuperLigne *l3 = new Ligne<AvionElectrique>(calais, paris, 0);
    SuperLigne *l4 = new Ligne<AvionElectrique>(edimbourg, londres, 0);
    SuperLigne *l5 = new Ligne<AvionElectrique>(londres, paris, 0);
    // v1->setLignes(l1);
    // v1->setLignes(l2);
    // v1->setLignes(l3);
    // v1->setLignes(l4);
    // v1->setLignes(l5);
    std::vector < SuperLigne * > leslignes;
    leslignes.push_back(l1);
    leslignes.push_back(l2);
    leslignes.push_back(l3);
    leslignes.push_back(l4);
    leslignes.push_back(l5);

    Terminal *terminaux[5] = {edimbourg, douvres, calais, paris, londres};
    Tests t;
    RemplirLignes(v1, v1->getOrigine(), v1->getDestination(), leslignes);
    // v1->PlusCourtChemin(chemin, "AvionElectrique", terminaux, 5, leslignes);
    std::cout << "nombre de lignes recuperees " << v1->getLignes().size() << std::endl;
    v1->afficherLignes();


}
