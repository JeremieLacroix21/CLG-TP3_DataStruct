#pragma once
#include "Matrice.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Liste.h"

using namespace std;
class Grille
{
public:

	Grille();
	~Grille();
	void AfficherGrille();
	void RemplirGrille(ifstream& fichier);
	void Solutionner();
	
private:
	/*void EtablirListe(Liste &laListe, int x, int y);*/
	bool Verifier(int x, int y) const;
	void EtablirListe(Liste &laListe, int x, int y);

	void TrouverChemin(int X, int Y);
	void TrouverEntrer();
	void TrouverSortie();
	void AfficherChemin();
	int CalculerNbCasesAccessibles(int x, int y) const;
	void Grille::PreparerListe(Liste &laListe);

	vector<int> PosEntrer;
	vector<int> PosSortie;
	Matrice<bool> CaseVisite;
	Matrice<char> Matrice;
	int meilleurtemps;
	int TailleGrille;
	unsigned int iMAXCASES;


};

