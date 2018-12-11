#pragma once
#include "Matrice.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Liste.h"
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;
class Grille
{
public:

	Grille(ifstream& fichier);
	~Grille();
	void AfficherGrille();
	void RemplirGrille(ifstream& fichier);
	void Solutionner();
	system_clock::time_point tempsDeDepart_;
	system_clock::time_point tempsCumulatif_;
	void AfficherChemin();
private:
	/*void EtablirListe(Liste &laListe, int x, int y);*/
	int  noPasDuTrajet_;
	bool Verifier(int x, int y) const;
	void EtablirListe(Liste &laListe, int x, int y);
	bool OnPeutAtteindre(int i, int j) const;
	void TrouverChemin(int X, int Y);
	void TrouverEntrer();
	void TrouverSortie();
	
	int CalculerNbCasesAccessibles(int x, int y) const;
	void PreparerListe(Liste &laListe);
	Liste trajets;
	vector<int> PosEntrer;
	vector<int> PosSortie;
	Matrice<int> caseTrajet_;
	Matrice<bool> CaseVisite;
	Matrice<bool> MatricePluscourt;
	Matrice<string> Matrice;
	
	int meilleurtemps;
	int TailleGrille;
	unsigned int iMAXLIGNE;
	unsigned int iMAXCOLONNES;
	bool rechercheDoitContinuer_;
	void AfficherTrajetTrace() const;
	void AfficherTrajet(system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const;

	int Nopasdutrajetscourrant;
	int sommeplusbasse;
	int sommecourrante;
	bool premierchemin;
};

