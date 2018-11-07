#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include "Moyens.h"

class Train : public Moyens{
	public:
	Train();
	~Train();
	void afficher() const;
};
#endif
