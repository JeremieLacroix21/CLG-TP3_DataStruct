// Board.cpp: implementation of the Board class.
//
//////////////////////////////////////////////////////////////////////
#include "Board.h"
#include "liste.h"
#include <string>
using namespace std;

const int Board::iMAXCASES = 8;

Board::Board(int ligne, int colonne, ostream & sortie, bool veutTrace)
:ligneDepart_(ligne), colonneDeDepart_(colonne), rOut(sortie), traceDemandee_(veutTrace),
 caseVisitee_(iMAXCASES, iMAXCASES), caseTrajet_(iMAXCASES, iMAXCASES)
{
	for (int i=0; i<iMAXCASES; i++)
		for (int j=0; j<iMAXCASES; j++)
		{
			caseVisitee_[i][j] = false;
			caseTrajet_[i][j] = -1;
		}
	noPasDuTrajet_ = 0;
	rechercheDoitContinuer_ = true;
	nombreDeSolutions_ = 0;
}

void Board::Solutionner()
{
	tempsCumulatif_ = tempsDeDepart_ = system_clock::now();
	PlacerCavalier (ligneDepart_, colonneDeDepart_);
}

/*	
	Etablir les cases que l'on peut aller visiter à partir de la position reçue
	Pour chaque case que l'on peut visiter à partir de cette position
		visiter cette case
		si (toutes les cases sont visitées)
			C'est fini
		sinon
			PlacerCavalier(coordonnées de cette case)
		finsi
		dévisiter cette case
	finpour
*/
void Board::PlacerCavalier(unsigned int i, unsigned int j)
{
	caseVisitee_[i][j] = true;
	caseTrajet_[i][j] = noPasDuTrajet_;
	noPasDuTrajet_++;

	if (traceDemandee_) AfficherTrajetTrace();
	if (ToutEstVisite())
	{
		// Afficher à l'écran
		auto stop = system_clock::now();
		auto tempsEcoule = stop - tempsDeDepart_;
		auto tempsEcouleCumulatif = stop - tempsCumulatif_;
		system("cls");
		AfficherTrajet(++nombreDeSolutions_, tempsEcoule, tempsEcouleCumulatif);
		tempsDeDepart_ = system_clock::now();
	}
	else
	{
			Liste ListeAVisiter;
			int x, y;
			
			EtablirListe(ListeAVisiter, i, j);
			while ( ! ListeAVisiter.EstVide() && rechercheDoitContinuer_ )
			{
				ListeAVisiter.Retirer(x, y);
				PlacerCavalier(x, y);
			}
	}
	caseVisitee_[i][j] = false;
	caseTrajet_[i][j] = -1;
	noPasDuTrajet_ --;
}

void Board::AfficherNoSolution(int iNbSolution) const
{
	rOut << endl 
		<< "Solution #" << iNbSolution << endl;
}

void Board::EtablirListe(Liste &laListe, int x, int y)
{
	// A partir de la coordonnee x y, établir quelles sont les
	// cases que l'on doit aller visiter.
	if (Verifier(x,y-1)) laListe.Ajouter(x,y-1);
	if (Verifier(x,y+1)) laListe.Ajouter(x,y+1);
	if (Verifier(x+1,y)) laListe.Ajouter(x+1,y);
	if (Verifier(x-1,y)) laListe.Ajouter(x-1,y);
	PreparerListe(laListe);
}

bool Board::Verifier(int x, int y) const
{
	bool bOk = false;

	if (x >=0 && y >=0 && 
		x < iMAXCASES && y < iMAXCASES &&
		! caseVisitee_[x][y])
	{
		bOk = true;
	}
	return bOk;
}

void Board::AfficherTrajet(int iNoSolution, system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const
{
	rOut << "Cavalier en (" << ligneDepart_ << ", " << colonneDeDepart_ << ")" << endl;
	rOut << string(7*iMAXCASES+1,'-') << endl;
	for (int i=0; i<iMAXCASES; i++)
	{
		rOut << "| ";
		for (int j = 0; j < iMAXCASES; j++)
		{
			if (caseTrajet_[i][j] != 0)
			{
				rOut.width(4);
				rOut << caseTrajet_[i][j] << " | ";
			}
			else
			{
				rOut << "   C | ";
			}
		}
		rOut << endl;
		rOut << string(7*iMAXCASES+1,'-') << endl;
	}
	AfficherNoSolution( iNoSolution );
	rOut << "en " << duration_cast<microseconds>(tempsRequis).count() << " microsecondes" << endl;
	rOut << "ou si vous preferez en " << duration_cast<nanoseconds>(tempsRequis).count() << " nanosecondes" << endl;
	rOut << endl << "temps requis cumulatif : " << duration_cast<microseconds>(tempsRequisCumulatif).count() << " microsecondes" << endl;

	// pour ne pas avoir à faire des enter quand on écrit dans un fichier de sortie...
	if (&rOut == &cout) system("pause");

}

void Board::AfficherTrajetTrace() const
{
	system("cls");
	rOut << string(41,'-') << endl;
	for (int i=0; i<iMAXCASES; i++)
	{
		rOut << "| ";
		for (int j=0; j<iMAXCASES; j++)
		{
			if (caseTrajet_[i][j] != 0 && caseTrajet_[i][j] != -1)
			{
				rOut.width(2);
				rOut << caseTrajet_[i][j] << " | ";
			}
			else if (caseTrajet_[i][j] == -1)
			{
				rOut << "   | ";
			}
			else
			{
				rOut << " C | ";
			}
		}
		rOut << endl;
		rOut << string(41,'-') << endl;
	}
	// Wait(500);  // millisecondes dont 0,5 seconde
	system("pause");
}

void Board::Wait(int iNbMilliSec) const
{
	auto start = system_clock::now();
	auto stop = system_clock::now();
	auto tempsEcoule = stop - start;

	while (duration_cast<milliseconds>(tempsEcoule).count() < iNbMilliSec)
	{
		stop = system_clock::now();
		tempsEcoule = stop - start;
	}
}

bool Board::ToutEstVisite() const
{
	return (noPasDuTrajet_ >= ((iMAXCASES * iMAXCASES)));
}

// Doit établir si la solution est encore possible à partir
// de la grille actuelle
bool Board::SolutionEncorePossible() const
{
	bool bOk = true;
	int iNbCasesNonVisitees = 0;

	for (int i=0; i < iMAXCASES && bOk; i++)
		for (int j=0; j < iMAXCASES && bOk; j++)
			if (!caseVisitee_[i][j])
			{
				iNbCasesNonVisitees ++;
				bOk = bOk && OnPeutAtteindre(i,j);
			}
	return (bOk || (iNbCasesNonVisitees == 1));
}

bool Board::OnPeutAtteindre(int x, int y) const
{
	int i = 0;

	if (Verifier(x - 1, y)) i++;
	if (Verifier(x, y - 1)) i++;
	if (Verifier(x + 1, y)) i++;
	if (Verifier(x, y + 1)) i++;
	return (i > 0);
}

// reçoit une liste et doit mettre en premier 
// les positions les plus difficiles à atteindre
void Board::PreparerListe(Liste &laListe)
{
	int x, y;

	//	Etablir un poids pour chaque coordonnee
	for (int indice = 0; indice < laListe.GetNombreDeCoordonnees(); ++indice)
	{
		// note : GetCoordonnee retourne une référence sur une coordonnée ce 
		// qui permet de modifier le poids de cette Coordonnée dans la liste
		// via SetPoids(); une alternative aurait été de mettre la classe Liste
		// sous la forme d'une structure interne à la classe Board, ce qui aurait 
		// donné accès à ses membres. Ou encore mettre une relation friend entre
		// une classe et l'autre pour permettre le bris d'encapsulation
		laListe.GetCoordonnee(indice).GetCoordonnee(x, y);
		laListe.GetCoordonnee(indice).SetPoids(CalculerNbCasesAccessibles(x, y));
	}
	// Trier cette liste ...
	laListe.Trier();

	//  Pour débuggage...
	//AfficherListe(laListe);
	//system("pause");
}

int Board::CalculerNbCasesAccessibles(int x, int y) const
{
	int iNb = 0;

	if (Verifier(x-1,y)) iNb++;
	if (Verifier(x,y-1)) iNb++;
	if (Verifier(x+1,y)) iNb++;
	if (Verifier(x,y+1)) iNb++;
	return iNb;
}
