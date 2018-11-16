#include <iostream>
#include "source/Tests.h"
#include "source/Gare.h"
#include"source/Terminal.h"
#include "source/AeroportRegional.h"
#include "source/AeroportInternational.h"
#include"source/Ligne.h"
#include"source/Train.h"
#include "source/Avion.h"
#include "source/SuperLigne.h"
#include "source/AvionElectrique.h"
#include "source/Voyage.h"
#include "source/HubMultimodal.h"


int main() {
//   Gare plymonth("Plymonth");
//   Gare ermont("Ermont");
//   AeroportRegional orly("Orly");
//
//   AeroportInternational cdg("Charles de gaules");
//   plymonth.ajouterLiaison(&ermont);
//   plymonth.afficher();
//   ermont.afficher();
//
//   Terminal *paris = new HubMultimodal("paris", 22,45,20);
//   Terminal *CDG = new AeroportInternational("CDG",23,48,10);
//   Terminal *lyon = new Gare("lyon", 13,70,15);
//   Terminal *lehavre = new HubMultimodal("lehavre", 13,90,65);
//   Moyens *train= new Train();
//   Terminal *hub = new HubMultimodal("hub", 55,5,10, paris);
//   hub->ajouterLiaison(lyon);
//   //Moyens *avion= new Avion();
//   Avion avion= Avion();
//   SuperLigne *ll = new Ligne<AvionElectrique> (paris, lyon, 400);
//   SuperLigne *l = new Ligne<Train> ( lyon,lehavre, 400);
//   //SuperLigne *lignet = new Ligne<Train> ( lyon,lehavre, 300);
//   SuperLigne *lll = new Ligne<Avion> (lehavre ,CDG, 400);
//
// //  Ligne<Avion> l (paris, CDG, 400);
//   Ligne<Train> l2(CDG, paris, 3300);
//  Voyage v1 (paris, CDG);
//  v1.setLignes(ll);
//   v1.setLignes(l);
//   v1.setLignes(lll);


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

// Tests t;
// double empreinte ;
// empreinte = t.TestSenario1(345, "Avion");
// std::cout <<"empreinte test1 = " << empreinte << std::endl;
//



    /* Terminal *paris = new HubAeroport("Paris", 48, 2, 45);
    Terminal *rome = new AeroportInternational("Rome", 41, 12, 30);
    Terminal *lyon = new AeroportRegional("Lyon", 45, 4, 30);
    Terminal *naples = new AeroportRegional("Naples", 40, 14, 30);
    Terminal *bruxelles = new AeroportRegional("Bruxelles", 50, 4, 30); */

/*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
//FluxVilles(paris, rome, lyon, naples,bruxelles);

/*Ajout des liaisons de chaque ville*/
   /*  paris->ajouterLiaison(rome);
    paris->ajouterLiaison(lyon);
    paris->ajouterLiaison(bruxelles);
    rome->ajouterLiaison(naples); */

/*création d'un tablea de tous les terminaux du scenario*/
   /*  std::vector < SuperLigne * > lesLignes;
    Terminal *terminaux[5] = {paris, rome, lyon, naples, bruxelles};


    Tests t;
    Scenario *s = t.TestSenario1(345, "Avion"); */
//t.AfficherVoyagesScenario(s);
//t.TestPlusCourtChemin();
// std::list <Voyage*> voyages;
// //t.TousVoyagesPossibles( voyages,s, terminaux, 5, "scenario1");

//t.TestPl();

// std::cout<< voyages.size();
// for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
// {
//   //t.RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
//   //std::cout<< ((*it)->getOrigine())->getNom() << " to " <<((*it)->getDestination())->getNom()<<(*it)->getLignes().size()<<std::endl;
//
// }


    if (Tests::TestGare()) {
        std::cout << std::endl;
        std::cout << "Le test TestGare() a reussie" << std::endl;
        std::cout << std::endl;
    }

    
    return 0;
}
