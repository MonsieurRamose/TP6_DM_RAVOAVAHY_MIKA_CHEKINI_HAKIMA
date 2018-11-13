#include "Tests.h"




Tests::Tests(): empreintecar(0){

}
double Tests::getEmpreinte() {
  return empreintecar;
}
void Tests::setEmpreinte(double emp){
  empreintecar = emp;
}

void Tests::FluxVilles(Terminal * paris, Terminal *rome, Terminal *lyon, Terminal *naples, Terminal *bruxelles )
{
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

double Tests::TestSenario1(double maxTemps, std::string moyenTrans){

  /* Instanciation des terminaux du scénario1*/

  Terminal * paris = new HubAeroport("Paris", 48 , 2, 45);
  Terminal * rome = new AeroportInternational("Rome",41 ,12 ,30 );
  Terminal * lyon= new AeroportRegional("Lyon", 45, 4 , 30);
  Terminal * naples= new AeroportRegional("Naples", 40, 14 ,30 );
  Terminal * bruxelles= new AeroportRegional("Bruxelles", 50, 4, 30);

  /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
  FluxVilles(paris, rome, lyon, naples,bruxelles);

  /*Ajout des liaisons de chaque ville*/
  paris->ajouterLiaison(rome);
  paris->ajouterLiaison(lyon);
  paris->ajouterLiaison(bruxelles);
  rome->ajouterLiaison(naples);

  //setEmpreinte(0);
  /*instanciation des lignes entre les villes*/
  double empreinte = 0;
  std::string leMoy;
  /*premier test: les lignes entre les villes sont des avions*/

  SuperLigne * parisRome_L;
  SuperLigne * parisLyon_L ;
  SuperLigne * parisBruxelles_L ;
  SuperLigne * romeNaples_L;

  if( moyenTrans.compare("Avion") == 0)
  {
    parisRome_L = new Ligne<Avion> ( paris, rome, 0);
    parisLyon_L = new Ligne<Avion> ( paris, lyon, 0);
    parisBruxelles_L = new Ligne<Avion> ( paris, bruxelles, 0);
    romeNaples_L = new Ligne<Avion> ( rome, naples, 0);
  }else{
    parisRome_L = new Ligne<AvionElectrique> ( paris, rome, 0);
    parisLyon_L = new Ligne<AvionElectrique> ( paris, lyon, 0);
    parisBruxelles_L = new Ligne<AvionElectrique> ( paris, bruxelles, 0);
    romeNaples_L = new Ligne<AvionElectrique> ( rome, naples, 0);
  }


  /*Creation des voyages et ajouts des lignes*/

  Voyage parisNaples_V(paris, naples);
  parisNaples_V.setLignes(parisRome_L);
  parisNaples_V.setLignes(romeNaples_L);

  Voyage parisLyon_V(paris, lyon);
  parisLyon_V.setLignes(parisLyon_L);

  Voyage parisBruxelles_V(paris, bruxelles);
  parisBruxelles_V.setLignes(parisBruxelles_L);

  double empreinteCar = 0;
  double temps;
  temps = parisNaples_V.tempsTrajet() ;
  empreintecar = parisNaples_V.empreinteCarbone() ;

  /*Si le temps max n a pas été atteint, on calcule le temps des autres trajets*/

  if(temps < maxTemps)
  {
    temps += parisLyon_V.tempsTrajet();
    empreintecar += parisLyon_V.empreinteCarbone();
  }else{
    return empreintecar;
  }

  /*Si toujours le temps max n est pas encore atteint, on continu*/

  if( temps < maxTemps)
  {
    temps += parisBruxelles_V.tempsTrajet();
    empreintecar += parisLyon_V.empreinteCarbone();
  }else{
    return empreintecar;
  }
  return empreintecar;

  delete rome;
  delete lyon;
  delete bruxelles;
  delete naples;
  delete paris;




}


static void TestSenario2(){

}
static void TestSenario3(){

}
static void TestSenario4(){

}
static void TestSenario5(){

}
static void TestSenario6(){

}
