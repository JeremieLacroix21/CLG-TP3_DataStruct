// Liste.cpp: implementation of the Liste class.
//
//////////////////////////////////////////////////////////////////////
#include "Liste.h"
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Liste::Liste()
{
}

Liste::~Liste()
{

}

bool Liste::Ajouter(int ligne, int colonne)
{
	Coordonnee c;

	c.SetCoordonnee(ligne, colonne);
	liste_.push_back(c);
	return true;
}

bool Liste::Retirer(int &ligne, int &colonne)
{
	bool succes = false;

	if (!EstVide())
	{
		liste_.front().GetCoordonnee(ligne, colonne);
		liste_.pop_front();
		succes = true;
	}
	return succes;
}

bool Liste::EstVide()
{
	return liste_.empty();
}

void Liste::Trier()
{
	sort(liste_.begin(), liste_.end());
}

Coordonnee & Liste::GetCoordonnee(int rang)
{
	return liste_.at(rang);
}

int Liste::GetNombreDeCoordonnees() const
{
	return liste_.size();
}

