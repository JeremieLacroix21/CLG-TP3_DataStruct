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
		iMAXCASES = ValeurDeBiblio.size();
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
		bool rechercheDoitContinuer_ = true;
		if (Matrice[X][Y] == 'B')
		{
			rechercheDoitContinuer_ = false;
			
		}
		else
		{
			Liste ListeAVisiter;
			int x, y;

			EtablirListe(ListeAVisiter, X, Y);
			while (!ListeAVisiter.EstVide() && rechercheDoitContinuer_)
			{
				ListeAVisiter.Retirer(x, y);
				TrouverChemin(x, y);
			}
		}
		CaseVisite[X][Y] = false;
		
		
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

bool Grille::Verifier(int x, int y) const
{
	bool bOk = false;

	if (x >= 0 && y >= 0 &&
		x < iMAXCASES && y < iMAXCASES &&
		!CaseVisite[x][y])
	{
		bOk = true;
	}
	return bOk;
}


void Grille::PreparerListe(Liste &laListe)
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


int Grille::CalculerNbCasesAccessibles(int x, int y) const
{
	int iNb = 0;

	if (Verifier(x - 2, y - 1)) iNb++;
	if (Verifier(x - 2, y + 1)) iNb++;
	if (Verifier(x + 2, y - 1)) iNb++;
	if (Verifier(x + 2, y + 1)) iNb++;
	if (Verifier(x - 1, y - 2)) iNb++;
	if (Verifier(x - 1, y + 2)) iNb++;
	if (Verifier(x + 1, y - 2)) iNb++;
	if (Verifier(x + 1, y + 2)) iNb++;
	return iNb;
}