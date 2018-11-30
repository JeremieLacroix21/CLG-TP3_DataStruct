#pragma once
#include "Matrice.h"
#include <iostream>
#include <fstream>
#include <string>
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
	void TrouverChemin();
	void TrouverEntrer();
	void TrouverSortie();
	void AfficherChemin();
	vector<int> PosEntrer;
	vector<int> PosSortie;
	Matrice<bool> CaseVisite;
	Matrice<char> Matrice;
	int TailleGrille;

};

