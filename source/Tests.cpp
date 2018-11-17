#include "Tests.h"


Tests::Tests(){}

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

void Tests::TousVoyagesPossibles(std::list <Voyage*>& voyages, Scenario* s1, Terminal* terminaux[],int n)
{
  /*instanciation de tous les voyages possibles entre les villes
  */
  for(int i = 0; i < n; i ++)
  {
    for(int j= 0; j< n; j++)
    {
      if(i != j)
      {
        Voyage* v = new Voyage(terminaux[i], terminaux[j]);
        voyages.push_back(v);
      }
    }
  }
}



/*Cette methode  rempli le voyage en parametre avec les lignes necessaires pour pour atteindre sa destination*/

 void Tests::RemplirLignes(Voyage* v, Terminal* org, Terminal* dest, std::vector<SuperLigne*> lignesEx)
{
  bool arrive = false;
//while(!arrive)
//  {

    for(std::vector<SuperLigne *>::iterator it = lignesEx.begin(); it != lignesEx.end(); it++)
    {
      /*chercher la ligne qui a comme origine, l origine du voyage donne en parametre*/
      if(org ==  (*it)->getOrigine())
      {
        if(dest == (*it)->getDestination())
        {
          arrive = true;
          /*ajouter la ligne au voyage*/
          v->setLignes((*it));
          return; // sortit de la boucle
        }//else{
          /*ajouter la ligne et passer a la prochaine ligne en mettant la distination de cette derniere comme origine*/
             v->setLignes((*it));

          /*changer l origine du voyage et appler recursivement */
             org = (*it)->getDestination();

        }
      }

    }

/*Cette méthode permet de calculer l’empreinte carbone d’un scenario, elle parcourt tous les voyages
d’un scenario et calcule l’empreinte carbone, tout en tenant en compte un temps maximal à ne pas dépasser.*/
double Tests::calculerEmpreinteVoyages(double maxTemps, Scenario* scenario, std::list <Voyage*> voyages)
{
  double tempsTrj = 0;
  double empreinteCarbone = 0;
  double tt = 0;
  while(tt < maxTemps)
  {
    for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
    {
      double t = tempsTrj + (*it)->tempsTrajet();
      if(t >= maxTemps)
      {
        break;
      }
      empreinteCarbone += (*it)->empreinteCarbone();
      tempsTrj += (*it)->tempsTrajet();
      tt += tempsTrj;
    }
  }

//std::cout << scenario->getNom()<< ", temps de trajet: "<< tempsTrj << " minutes, empreinte carbone consommée: " << empreinteCarbone << " kg/km" << std::endl;
return empreinteCarbone;
}


double Tests::TestSenario1(double maxTemps, std::string scenario){

  /* Instanciation des terminaux du scénario1*/

  Terminal * paris = new HubAeroport("Paris", 48 , 2, 45);
  Terminal * rome = new AeroportInternational("Rome",41 ,12 ,30 );
  Terminal * lyon= new AeroportRegional("Lyon", 45, 4 , 30);
  Terminal * naples= new AeroportRegional("Naples", 40, 14 ,30 );
  Terminal * bruxelles= new AeroportRegional("Bruxelles", 50, 4, 30);

  /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
  FluxVilles(paris, rome, lyon, naples,bruxelles);


    SuperLigne* parisRome_L = new Ligne<AvionElectrique> ( paris,rome, 0);
    SuperLigne* parisLyon_L = new Ligne<Avion> ( paris, lyon, 0);
    SuperLigne* parisBruxelles_L = new Ligne<AvionElectrique> ( paris,bruxelles, 0);
    SuperLigne* romeNaples_L = new Ligne<Avion> ( rome, naples, 0);

    SuperLigne* romeParis_L = new Ligne<AvionElectrique> ( rome, paris,0);
    SuperLigne* lyonParis_L = new Ligne<Avion> (lyon, paris, 0);
    SuperLigne* bruxellesParis_L = new Ligne<AvionElectrique> (bruxelles,paris, 0);
    SuperLigne* naplesRome_L = new Ligne<Avion> (naples,rome, 0);

    /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */

    std::vector<SuperLigne*> lesLignes;
    lesLignes.push_back(parisRome_L);
    lesLignes.push_back(parisLyon_L);
    lesLignes.push_back(parisBruxelles_L);
    lesLignes.push_back(romeNaples_L);

    lesLignes.push_back(romeParis_L);
    lesLignes.push_back(lyonParis_L);
    lesLignes.push_back(bruxellesParis_L);
    lesLignes.push_back(naplesRome_L);


  /*création d'un tablea de tous les terminaux du scenario*/

   Terminal* terminaux [5] = { paris, rome, lyon, naples, bruxelles};

  /*methode qui instancie tous les voyages possibles entre les villes
  et les ajoute a un scenario*/

  Scenario* scenario1 = new Scenario("scenario1");
  std::list <Voyage*> voyages;
  TousVoyagesPossibles(voyages,scenario1, terminaux, 5);

  /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
   de lignes avec les lignes necessaires pour pour atteindre sa destination */

  for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
  {
    RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
    scenario1->addVoyage(*it);

   return calculerEmpreinteVoyages(maxTemps,  scenario1, voyages);

}

}

double Tests::TestSenario2(double maxTemps, std::string scenario){

  /* Instanciation des terminaux du scénario1*/

  Terminal * paris = new HubMultimodal("Paris", 48 , 2, 45);
  Terminal * rome = new AeroportInternational("Rome",41 ,12 ,30 );
  Terminal * lyon= new AeroportRegional("Lyon", 45, 4 , 30);
  Terminal * naples= new AeroportRegional("Naples", 40, 14 ,30 );
  Terminal * bruxelles= new Gare("Bruxelles", 50, 4, 30);

  /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
  FluxVilles(paris, rome, lyon, naples,bruxelles);

    SuperLigne* parisRome_L = new Ligne<Avion> ( paris,rome, 0);
    SuperLigne* lyonNaples_L = new Ligne<AvionElectrique> ( lyon, naples, 0);
    SuperLigne* parisBruxelles_L = new Ligne<Train> ( paris,bruxelles, 0);

    SuperLigne* romeParis_L = new Ligne<Avion> ( rome,paris, 0);
    SuperLigne* naplesLyon_L = new Ligne<AvionElectrique> (  naples,lyon, 0);
    SuperLigne* bruxellesParis_L = new Ligne<Train> (bruxelles, paris, 0);

    /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */
    std::vector<SuperLigne*> lesLignes;

    lesLignes.push_back(parisRome_L);
    lesLignes.push_back( lyonNaples_L);
    lesLignes.push_back(parisBruxelles_L);

    lesLignes.push_back(romeParis_L);
    lesLignes.push_back(naplesLyon_L);
    lesLignes.push_back(bruxellesParis_L );

  /*création d'un tablea de tous les terminaux du scenario*/

   Terminal* terminaux [5] = { paris, rome, lyon, naples, bruxelles};

  /*methode qui instancie tous les voyages possibles entre les villes
  et les ajoute a un scenario*/

  Scenario* scenario2 = new Scenario("scenario2");

  std::list <Voyage*> voyages;
  TousVoyagesPossibles(voyages,scenario2, terminaux, 5);

  /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
   de lignes avec les lignes necessaires pour pour atteindre sa destination */

  for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
  {
    RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
    scenario2->addVoyage(*it);

  }

  double empreinteCarbone = calculerEmpreinteVoyages(maxTemps,  scenario2, voyages);
  return empreinteCarbone;
}


double Tests::TestSenario3(double maxTemps, std::string scenario){

  /* Instanciation des terminaux du scénario1*/

  Terminal * lyon= new Gare("Lyon", 45, 4 , 30);
  Terminal * naples= new Gare("Naples", 40, 14 ,30 );
  Terminal * bruxelles= new Gare("Bruxelles", 50, 4, 30);
  Terminal * paris = new HubMultimodal("Paris", 48 , 2, 45, lyon);
  Terminal * rome = new HubMultimodal("Rome",41 ,12 ,30, naples );

  /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
  FluxVilles(paris, rome, lyon, naples,bruxelles);


    SuperLigne* parisLyon_L = new Ligne<Train> ( paris,lyon, 0);
    SuperLigne* lyonRome_L = new Ligne<Train> ( lyon, rome, 0);
    SuperLigne* romeNaples_L = new Ligne<Train> ( rome,naples, 0);
    SuperLigne* parisBruxelles_L = new Ligne<Train> (paris, bruxelles, 0);

    SuperLigne* lyonParis_L = new Ligne<Train> ( lyon, paris,0);
    SuperLigne* romeLyon_L = new Ligne<Train> ( rome, lyon, 0);
    SuperLigne* naplesRome_L = new Ligne<Train> ( naples,rome, 0);
    SuperLigne* bruxellesParis_L = new Ligne<Train> (bruxelles,paris,  0);


    /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */

    std::vector<SuperLigne*> lesLignes;

    lesLignes.push_back(parisLyon_L);
    lesLignes.push_back( lyonRome_L);
    lesLignes.push_back(romeNaples_L);
    lesLignes.push_back(parisBruxelles_L );

    lesLignes.push_back(lyonParis_L);
    lesLignes.push_back(romeLyon_L  );
    lesLignes.push_back(naplesRome_L  );
    lesLignes.push_back(bruxellesParis_L );

  /*création d'un tablea de tous les terminaux du scenario*/

   Terminal* terminaux [5] = { paris, rome, lyon, naples, bruxelles};

  /*methode qui instancie tous les voyages possibles entre les villes
  et les ajoute a un scenario*/

  Scenario* scenario3 = new Scenario("scenario3");

  std::list <Voyage*> voyages;
  TousVoyagesPossibles(voyages,scenario3, terminaux, 5);

  /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
   de lignes avec les lignes necessaires pour pour atteindre sa destination */

  for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
  {
    RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
    scenario3->addVoyage(*it);
  }
  double empreinteCarbone = calculerEmpreinteVoyages(maxTemps,  scenario3, voyages);
  return empreinteCarbone;
}



double Tests::TestSenario5(double maxTemps, std::string scenario){

  /* Instanciation des terminaux du scénario1*/

  Terminal * lyon= new Gare("Lyon", 45, 4 , 30);
  Terminal * naples= new Gare("Naples", 40, 14 ,30 );
  Terminal * bruxelles= new Gare("Bruxelles", 50, 4, 30);
  Terminal * paris = new Gare("Paris", 48 , 2, 45);
  Terminal * rome = new Gare("Rome",41 ,12 ,30);

  /*appler la methode FluxVilles qui ajoute le flux des passagers a chaque ville*/
  FluxVilles(paris, rome, lyon, naples,bruxelles);

    SuperLigne* bruxellesParis_L = new Ligne<Train> ( bruxelles,paris, 0);
    SuperLigne* parisLyon_L = new Ligne<Train> ( paris, lyon, 0);
    SuperLigne* lyonRome_L = new Ligne<Train> ( lyon, rome, 0);
    SuperLigne* romeNaples_L = new Ligne<Train> (rome, naples, 0);

    SuperLigne* parisBruxelles_L = new Ligne<Train> ( paris ,bruxelles,0);
    SuperLigne* lyonParis_L = new Ligne<Train> (  lyon,paris, 0);
    SuperLigne* romeLyon_L = new Ligne<Train> ( rome, lyon, 0);
    SuperLigne* naplesrome_L = new Ligne<Train> ( naples,rome, 0);

    /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */

    std::vector<SuperLigne*> lesLignes;

    lesLignes.push_back(bruxellesParis_L);
    lesLignes.push_back( parisLyon_L);
    lesLignes.push_back(lyonRome_L);
    lesLignes.push_back(romeNaples_L );

    lesLignes.push_back(parisBruxelles_L);
    lesLignes.push_back(lyonParis_L  );
    lesLignes.push_back(romeLyon_L  );
    lesLignes.push_back(naplesrome_L );

  /*création d'un tablea de tous les terminaux du scenario*/

   Terminal* terminaux [5] = { paris, rome, lyon, naples, bruxelles};

  /*methode qui instancie tous les voyages possibles entre les villes
  et les ajoute a un scenario*/

  Scenario* scenario5 = new Scenario("scenario5");

  std::list <Voyage*> voyages;
  TousVoyagesPossibles(voyages,scenario5, terminaux, 5);

  /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
   de lignes avec les lignes necessaires pour pour atteindre sa destination */

  for(std::list <Voyage*>::iterator it= voyages.begin(); it != voyages.end(); it++)
  {
    RemplirLignes((*it), (*it)->getOrigine(),(*it)->getDestination(), lesLignes);
    scenario5->addVoyage(*it);
  }

  double empreinteCarbone = calculerEmpreinteVoyages(maxTemps,  scenario5, voyages);
  return empreinteCarbone;
}



double Tests::TestSenario4(double maxTemps, std::string scenario){

}

double Tests::TestSenario6(double maxTemps, std::string scenario){

}


void Tests::TestPl(){
  std::list<SuperLigne *> chemin;

  Terminal *edimbourg = new AeroportInternational("edimbourg ",26,48,10);
  Terminal *douvres = new AeroportInternational("douvres",23,49,30);
  Terminal *calais = new AeroportInternational("calais",17,48,20);
  Terminal *paris = new AeroportInternational("paris",23,15,19);
  Terminal *londres= new AeroportInternational("londres",23,98,16);

  Voyage* v1 = new Voyage(edimbourg, calais);

  SuperLigne *l1 = new Ligne<AvionElectrique> (edimbourg, douvres, 0);
  SuperLigne *l2 = new Ligne<AvionElectrique> ( douvres,calais,0);
  SuperLigne *l3 = new Ligne<AvionElectrique> ( calais,paris ,0);
  SuperLigne *l4 = new Ligne<AvionElectrique> (edimbourg ,londres,0);
  SuperLigne *l5 = new Ligne<AvionElectrique> (londres ,paris,0);

  std::vector<SuperLigne *> leslignes;
  leslignes.push_back(l1);
  leslignes.push_back(l2);
  leslignes.push_back(l3);
  leslignes.push_back(l4);
  leslignes.push_back(l5);

   Terminal* terminaux [5] = {edimbourg, douvres, calais, paris, londres};
   Tests t;
   RemplirLignes(v1, v1->getOrigine(), v1->getDestination(), leslignes);

     v1->afficherLignes();

}

void Tests::scenarioGagant(int indice)
{
  switch (indice)
  {
    case 1: std::cout << "Le Scenario 1 " ;
    break;
    case 2: std::cout << "Le Scenario 2 " ;
    break;
    case 3: std::cout << "Le Scenario 3 " ;
    break;
    case 4: std::cout << "Le Scenario 4 " ;
    break;
    case 5: std::cout << "Le Scenario 5 " ;
    break;
    case 6: std::cout << "Le Scenario 6 " ;
    break;
  }
}

/*Cette méthode permet de renvoyer le minimum d’un tableau de doubles.*/
 double Tests::minEmpreinteScenario(double empScenario[], int n, int& scenario)
 {
   double min = empScenario[0];
   int indice = 0;
   for (int i = 0; i < n; i++)
   {
     if(empScenario[i] < min)
     {
       min = empScenario[i];
       indice = i+1;
     }
   }
   scenario = indice;
   return min;
 }
/*Cette méthode prends en paramètre un temps max, un entier qui représente le nombre de scenarios,
 ainsi qu’un autre entier passé en référence afin de récupérer l’indice du scenario, pour l’utiliser
  par la suite pour savoir le scenario ayant consommant le minimum d’empreinte carbone. Et permet
   de choisir le scenario de plus petite empreinte carbone consommée.*/

double Tests::ChoisirScenario(int maxTemps, int n, int& scenario)
{
  /*convertir les heures en minutes*/

  double tempsMinute = maxTemps * 60;
  /*Pour chaque temps de trajet maximum, calculer l'empreinte carbone, et choisir le scenario qui minimise l'empreite carbone*/
  double empScenario[n]{
                        TestSenario1(tempsMinute, "scenario 1"),  TestSenario2(tempsMinute,"scenario 2"),
                        TestSenario3(tempsMinute,"scenario 3"),TestSenario4(tempsMinute,"scenario 4"),
                        TestSenario5(tempsMinute,"scenario 5"), TestSenario6(tempsMinute,"scenario 6")
                      };

  return minEmpreinteScenario(empScenario, n, scenario);

}

void Tests::EtudeDeCas()
{
  int scenario; // variable qui recupère l indice du sénario qui consomme le moins d empeinte carbone
  for (int i = 4; i < 9; i++ )
  {
    double empreinte = ChoisirScenario(i, 6, scenario);
    scenarioGagant(scenario);
    std::cout << " "<<std::endl;
    std::cout << "    est le scenario qui minimise l'empeinte carbone globale : "<<empreinte << " pour un temps de trajet max " <<i << "h" << std::endl;
  }

}
