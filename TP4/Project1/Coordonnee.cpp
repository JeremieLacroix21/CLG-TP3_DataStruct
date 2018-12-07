// Coordonnee.cpp: implementation of the Coordonnee class.
//
//////////////////////////////////////////////////////////////////////
#include "Coordonnee.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Coordonnee::Coordonnee()
{
	ligne_ = -1;
	colonne_ = -1;
	symbole_ = 0255;
}

void Coordonnee::SetCoordonnee(int xin, int yin)
{
	ligne_ = xin;
	colonne_ = yin;
}

void Coordonnee::GetCoordonnee(int &xout, int &yout)
{
	xout = ligne_;
	yout = colonne_;
}

void Coordonnee::SetSymbole(int symbole)
{
	symbole_ = symbole;
}

int Coordonnee::GetSymbole()
{
	return symbole_;
}

void Coordonnee::SetPoids(int iPoids)
{
	poids_ = iPoids;
}

int Coordonnee::GetPoids()
{
	return poids_;
}

bool Coordonnee::operator < (Coordonnee droite)
{
	return poids_ < droite.poids_;
}

