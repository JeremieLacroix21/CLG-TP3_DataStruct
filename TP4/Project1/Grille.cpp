#include "Grille.h"

Grille::Grille()
{

}

Grille::~Grille()
{
}

void Grille::AfficherGrille()
{ 
	for (int ligne = 0; ligne < Matrice.GetNbLignes(); ligne++)
	{
		
		for (int collone = 0; collone < Matrice.GetNbColonnes(); collone++)
		{
			cout << Matrice[ligne][collone] << "  ";
		}
		cout << endl;
	}

}


void Grille::RemplirGrille(ifstream& fichier)
{
	int ligne = 0;
	do {
		string ValeurDeBiblio;
		getline(fichier, ValeurDeBiblio);
		Matrice.SetNbLignes(Matrice.GetNbLignes() + 1);
		Matrice.SetNbColonnes(ValeurDeBiblio.size());
		for (int colonne = 0; colonne < Matrice.GetNbColonnes(); colonne++)
		{
			
			Matrice[ligne][colonne] = ValeurDeBiblio[colonne];
		}
		ligne++;
		
	} while (!fichier.eof());
}


void Grille::Solutionner()
{
	TrouverEntrer();
	TrouverSortie();
	//pour l'affichage des case visité on dit que l'entré et la sortie sont déja visité.
	CaseVisite.SetNbLignes(Matrice.GetNbLignes());
	CaseVisite.SetNbColonnes(Matrice.GetNbColonnes());
	CaseVisite[PosEntrer[0]][PosEntrer[1]] = true;
	TrouverChemin(PosEntrer[0],PosEntrer[1]);

}

void Grille::TrouverChemin(int X, int Y)
{
	if (X == 0)//mouvement possible : haut,bas,droite
	{

	}
	if (Y == Matrice.GetNbLignes())//mouvement possible : 
	{

	}
	
	if (X == Matrice.GetNbColonnes())//mouvement possible : haut,bas,gauche.
	{

	}
	if (Y == 0)//mouvement possible : gauche,droite,bas
	{

	}
	if (Matrice[X][Y] == 'B')
	{

	}


}

void Grille::TrouverEntrer()
{
	for (int ligne = 0; ligne < Matrice.GetNbLignes(); ligne++)
	{
		for (int collone = 0; collone < Matrice.GetNbColonnes(); collone++)
		{
			if (Matrice[ligne][collone] == 'E')
			{
				cout << "Ligne de la entree : " << ligne << endl;
				cout << "Colonne de la entree : " << collone << endl;

				PosEntrer.push_back(ligne);
				PosEntrer.push_back(collone);
			}
		}
	}
}
void Grille::TrouverSortie()
{
	for (int ligne = 0; ligne < Matrice.GetNbLignes(); ligne++)
	{
		for (int collone = 0; collone < Matrice.GetNbColonnes(); collone++)
		{
			if (Matrice[ligne][collone] == 'B')
			{
				cout << "Ligne de la sortie : " << ligne << endl;
				cout << "Colonne de la sortie : " << collone << endl;
				PosSortie.push_back(ligne);
				PosSortie.push_back(collone);
			}
		}
	}
}


void Grille::AfficherChemin()
{
	for (int ligne = 0; ligne < Matrice.GetNbLignes(); ligne++)
	{
		for (int collone = 0; collone < Matrice.GetNbColonnes(); collone++)
		{
			if (CaseVisite[ligne][collone] == true)
			{
				cout << Matrice[ligne][collone] << "  ";
			}
			cout << endl;
		}
	}
}


void Grille::EtablirListe(Liste &laListe, int x, int y)
{
	// A partir de la coordonnee x y, établir quelles sont les
	// cases que l'on doit aller visiter.
	if (Verifier(x - 2, y - 1)) laListe.Ajouter(x - 2, y - 1);
	if (Verifier(x - 2, y + 1)) laListe.Ajouter(x - 2, y + 1);
	if (Verifier(x + 2, y - 1)) laListe.Ajouter(x + 2, y - 1);
	if (Verifier(x + 2, y + 1)) laListe.Ajouter(x + 2, y + 1);
	if (Verifier(x - 1, y - 2)) laListe.Ajouter(x - 1, y - 2);
	if (Verifier(x - 1, y + 2)) laListe.Ajouter(x - 1, y + 2);
	if (Verifier(x + 1, y - 2)) laListe.Ajouter(x + 1, y - 2);
	if (Verifier(x + 1, y + 2)) laListe.Ajouter(x + 1, y + 2);
	PreparerListe(laListe);
}

bool Board::Verifier(int x, int y) const
{
	bool bOk = false;

	if (x >= 0 && y >= 0 &&
		x < iMAXCASES && y < iMAXCASES &&
		!caseVisitee_[x][y])
	{
		bOk = true;
	}
	return bOk;
}
