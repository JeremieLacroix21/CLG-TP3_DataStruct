// Coordonnee.h: interface for the Coordonnee class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class Coordonnee  
{
public:
	int  GetPoids();
	void SetPoids(int iPoids);
	int  GetSymbole();
	void SetSymbole(int symbole);
	void GetCoordonnee(int &ligne, int &colonne);
	void SetCoordonnee(int ligne, int colonne);
	Coordonnee();
	bool operator < (Coordonnee droite);

private:
	int poids_;
	int symbole_;
	int colonne_;
	int ligne_;
};
