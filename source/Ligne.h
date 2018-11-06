#ifndef LIGNE_H
#define LIGNE_H

#include <iostream>
#include "SuperLigne.h"
#include <list>
#include <stdexcept>
#include "Moyens.h"
template <class Moyens>
class Ligne: public SuperLigne{
/*private:
  std::list<Moyens> moyens;*/
public:
  Ligne():SuperLigne(){

  }

  Ligne(Terminal* orig, Terminal* dest, int freq): SuperLigne( orig, dest,freq){

  }

  ~Ligne()
  {
    std::cout << "Destructeur Ligne" << std::endl;
  /*	for(typename std::list<Moyens >::iterator it = moyens.begin(); it != moyens.end(); it++)
    {
      if((*it) != NULL)
      {
        delete (*it);
        (*it) = NULL;
      }
    }*/
  //  moyens.clear();
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
