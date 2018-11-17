#ifndef LIGNE_H
#define LIGNE_H

#include <iostream>
#include "SuperLigne.h"
#include <list>
#include <stdexcept>
#include "Moyens.h"
#include <typeinfo>



template <class Moyens>
class Ligne: public SuperLigne{

public:
  Ligne():SuperLigne(){

  }

  Ligne(Terminal* orig, Terminal* dest, int freq): SuperLigne( orig, dest,freq){

  }

  ~Ligne()
  {
    std::cout << "Destructeur Ligne" << std::endl;
  }

  void afficher() const{

   std::string m = typeid(Moyens).name();
   std::string moyen;
   if(m.compare("5Train") == 0)
   {
     moyen  = "Train";
   }else{
     if(m.compare("5Avion") == 0){
       moyen= "Avion";
     }else{
       moyen = "AvionElectrique";
     }
   }
   std::cout<< "Ligne "<< moyen<< ":"; // permet d'afficher le moyen de transport (Train , Avion, AvionElectrique)
    SuperLigne::afficher();
   }


};








#endif
