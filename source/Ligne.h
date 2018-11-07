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
   std::cout<< "      Ligne "<< typeid(Moyens).name()<< ":"; // permet d'afficher le moyen de transport (Train , Avion, AvionElectrique)
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
