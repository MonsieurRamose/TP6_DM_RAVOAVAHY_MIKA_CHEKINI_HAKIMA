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

Scenario* Tests::TousVoyagesPossibles(Terminal* terminaux[],int n, std::string scenario)
{
  /*instanciation de tous les voyages possibles entre les villes
  et l ajout a un scenario*/
  Scenario* s1 = new Scenario(scenario);
  for(int i = 0; i < n; i ++)
  {
    for(int j= 0; j< n; j++)
    {
      if(i != j)
      {
        Voyage* v = new Voyage(terminaux[i], terminaux[j]);
        s1->addVoyage(v);
      }
    }
  }
  return s1; /*****************/
}

std::vector<SuperLigne*>  Tests::ToutesLignesExistantes(Terminal* terminaux[], int n)
{
  /*cette méthode cree les lignes entre les villes, tout en suivant les liaison d une ville donnee
  puis, elle les stocke dans une liste de lignes*/

  std::vector<SuperLigne*> toutesLignes;
  SuperLigne * lig;
  for(int ter = 0; ter < n; ter++)
  {
    if(terminaux[ter]->getNbLiaisons() != 0)
    {
      /*creation d'une ligne pour chauque liaison d'un terminal*/

      for(std::vector<Terminal *>::iterator it = (terminaux[ter]-> getLiasons()).begin(); it != (terminaux[ter]-> getLiasons()).end(); it++)
      {
        lig = new Ligne<Avion> ( terminaux[ter], (*it), 0);
        toutesLignes.push_back(lig);
      }
    }
  }
  return toutesLignes;
}

/*Cette methode renvoi un voyage rempli avec les lignes necessaires pour pour atteindre sa destination*/

Voyage* Tests::RemplirLignes( Terminal* org, Terminal* dest, std::vector<SuperLigne*> lignesEx)
{

  Voyage* v = new Voyage(org, dest);
    for(std::vector<SuperLigne *>::iterator it = lignesEx.begin(); it != lignesEx.end(); it++)
    {
      /*chercher la ligne qui a comme origine, l origine du voyage donne en parametre*/
      if(org ==  (*it)->getOrigine())
      {
        if(dest == (*it)->getDestination())
        {
          /*ajouter la ligne au voyage*/
          v->setLignes((*it));
        }else{
          /*ajouter la ligne et passer a la prochaine ligne en mettant la distination de cette derniere comme origine*/
          v->setLignes((*it));





                  /* redefinir operateur =*/






          /*changer l origine du voyage et appler recursivement */
          org = (*it)->getDestination();
          v = RemplirLignes(org, dest,lignesEx);
        }
      }
    }
    return v;
}

Scenario* Tests::TestSenario1(double maxTemps, std::string moyenTrans){

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

  /*création d'un tablea de tous les terminaux du scenario*/

   Terminal* terminaux [5] = { paris, rome, lyon, naples, bruxelles};

  /*methode qui instancie tous les voyages possibles entre les villes
  et les ajoute a un scenario*/

  Scenario* scenario1 = TousVoyagesPossibles(terminaux, 5,"scenario1");

  /*le tableau leslignes contient toutes les lignes entre les villes comme indique dans l ennonce */

  std::vector<SuperLigne*> lesLignes = ToutesLignesExistantes(terminaux,5);

  /*Pour cahque voyage du scenario, on fait appel a la methode remplirLignes qui rempli sa liste
   de lignes avec les lignes necessaires pour pour atteindre sa destination */

  for(std::list<Voyage *>::iterator it = scenario1->getVoyages().begin(); it != scenario1->getVoyages().end(); it++)
  {
    (*it) = RemplirLignes((*it)->getOrigine(),(*it)->getDestination(), lesLignes);
  }
return scenario1;
}

void Tests::AfficherVoyagesScenario(Scenario *s)
{
  /*Affiche tous les voyages d un scenario ainsi que ses lignes */
  for(std::list<Voyage *>::iterator it = s->getVoyages().begin(); it != s->getVoyages().end(); it++)
  {
    (*it)->afficherLignes();
  }
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
