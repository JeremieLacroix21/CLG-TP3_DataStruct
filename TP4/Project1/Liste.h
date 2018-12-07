// Liste.h: interface for the Liste class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "coordonnee.h"
#include <deque>
using namespace std;

class Liste  
{
public:
	void Trier();
	bool EstVide();
	bool Retirer(int &, int &);
	bool Ajouter (int x, int y);

	// bris d'encapsulation volontaire; il aurait fallu 
	Coordonnee & GetCoordonnee(int rang); 
	int GetNombreDeCoordonnees() const;
	Liste();
	virtual ~Liste();

protected:
	deque<Coordonnee> liste_;
};
