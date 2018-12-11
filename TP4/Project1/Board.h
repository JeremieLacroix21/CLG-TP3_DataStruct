// Board.h: interface for the Board class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "Matrice.h"
#include "liste.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Board
{
public:
	//--- Constructeur et destructeur
	Board(int ligne, int colonne, ostream & = cout, bool veutTrace=false);

	//--- M�thode utilis�e par le client pour lancer la recherche de solution
	void Solutionner();

private:
	static const int iMAXCASES;  // Nombre de cases de l'�chiquier
	ostream & rOut;
	bool rechercheDoitContinuer_;
	bool traceDemandee_;
	int  noPasDuTrajet_;
	int  nombreDeSolutions_;
	int  ligneDepart_;
	int  colonneDeDepart_;
	Matrice<bool> caseVisitee_;  
	Matrice<int>  caseTrajet_; 
	system_clock::time_point tempsDeDepart_;
	system_clock::time_point tempsCumulatif_;

private:
	//--- M�thode lanc�e par le PlacerCavalier public
	void PlacerCavalier(unsigned int i, unsigned int j);

	//--- Autres m�thodes utiles
	void AfficherNoSolution(int) const;
	void AfficherTrajet(int iNoSolution, system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const;
	void AfficherTrajetTrace() const;
	int  CalculerNbCasesAccessibles(int x, int y) const;
	void EtablirListe(Liste &laListe, int x, int y);
	bool OnPeutAtteindre(int i, int j) const;
	void PreparerListe(Liste & laListe);
	bool SolutionEncorePossible() const;
	bool ToutEstVisite() const;
	bool Verifier(int x, int y) const;
	void Wait(int iNbMillisec) const;
};
