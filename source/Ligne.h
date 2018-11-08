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

  /* const Moyens& getMoyensTransport(string& moyen)const
  {
    //Méthode qui permet de récuperer le moyen de transort de la ligne
    //std::string moyen = typeid(Moyens).name();

    if(moyen.compare("5Train") == 0)
    {
      return new Train();
    }else{
      if(moyen.compare("5Avion") == 0){
        return new Avion();
      }else{
        return new AvionElectrique();
      }
    }
  }*/
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
   std::cout<< "      Ligne "<< moyen<< ":"; // permet d'afficher le moyen de transport (Train , Avion, AvionElectrique)
    SuperLigne::afficher();
   }
/*
  void push(Moyens  m){
  	moyens.push_back(m);
  }


  void pop(Moyens m){
  	if(!moyens.empty())
  	moyens.remove(m);
  }


  bool empty(){
    return moyens.empty();
  }

  void afficher(){}*/

};








#endif
