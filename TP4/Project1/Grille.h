#pragma once
#include "Matrice.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
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
	void TrouverChemin(int X, int Y);
	void TrouverEntrer();
	void TrouverSortie();
	void AfficherChemin();
	vector<int> PosEntrer;
	vector<int> PosSortie;
	Matrice<bool> CaseVisite;
	Matrice<char> Matrice;
	int meilleurtemps;
	int TailleGrille;

};

