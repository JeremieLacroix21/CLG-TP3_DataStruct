//Jérémie Lacroix - décembre 2018
//Grille.cpp
//Définition de la classe grille.
#include "Grille.h"

Grille::Grille(ifstream& fichier)
{
	RemplirGrille(fichier);
	for (int i = 0; i<iMAXLIGNE; i++)
		for (int j = 0; j<iMAXCOLONNES; j++)
		{
			CaseVisite[i][j] = false;
			caseTrajet_[i][j] = -1;
		}
	noPasDuTrajet_ = 0;
	rechercheDoitContinuer_ = true;
	
	
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
		CaseVisite.SetNbLignes(Matrice.GetNbLignes());
		CaseVisite.SetNbColonnes(ValeurDeBiblio.size());
		caseTrajet_.SetNbLignes(Matrice.GetNbLignes());
		caseTrajet_.SetNbColonnes(ValeurDeBiblio.size());
		iMAXCOLONNES = ValeurDeBiblio.size();
		iMAXLIGNE = Matrice.GetNbLignes();
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

	CaseVisite[X][Y] = true;
	caseTrajet_[X][Y] = noPasDuTrajet_;
	noPasDuTrajet_++;

	if (sommeplusbasse != NULL)
	{
		if (sommecourrante > sommeplusbasse)
		{
			//backtrack
		}
		else
		{
			sommeplusbasse = sommecourrante;
		}
	}

	if (Matrice[X][Y] != "B" && Matrice[X][Y] != "E" && Matrice[X][Y] != "R")
	{
		sommecourrante = sommecourrante + stoi(Matrice[X][Y]);
	}

	
	if (Matrice[X][Y] == "B")
	{

		auto stop = system_clock::now();
		auto tempsEcoule = stop - tempsDeDepart_;
		auto tempsEcouleCumulatif = stop - tempsCumulatif_;
		system("cls");
		tempsDeDepart_ = system_clock::now();
		AfficherTrajet(tempsEcoule, tempsEcouleCumulatif);
		sommeplusbasse = sommecourrante;
	}
	if (Matrice[X][Y] == "R")
	{

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
	caseTrajet_[X][Y] = -1;
	noPasDuTrajet_--;
	if (Matrice[X][Y] != "B" && Matrice[X][Y] != "E" && Matrice[X][Y] != "R")
	{
		sommecourrante = sommecourrante - stoi(Matrice[X][Y]);
	}
}


void Grille::TrouverEntrer()
{
	for (int ligne = 0; ligne < Matrice.GetNbLignes(); ligne++)
	{
		for (int collone = 0; collone < Matrice.GetNbColonnes(); collone++)
		{
			if (Matrice[ligne][collone] == "E")
			{
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
			if (Matrice[ligne][collone] == "B")
			{
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
	if (Verifier(x, y - 1)) laListe.Ajouter(x, y - 1);
	if (Verifier(x, y + 1)) laListe.Ajouter(x, y + 1);
	if (Verifier(x + 1, y)) laListe.Ajouter(x + 1, y);
	if (Verifier(x - 1, y)) laListe.Ajouter(x - 1, y);
	PreparerListe(laListe);
}

bool Grille::Verifier(int x, int y) const
{
	bool bOk = false;

	if (x >= 0 && y >= 0)
		if (x < iMAXLIGNE && y < iMAXCOLONNES )
			if (!CaseVisite[x][y])
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

	if (Verifier(x - 1, y)) iNb++;
	if (Verifier(x, y - 1)) iNb++;
	if (Verifier(x + 1, y)) iNb++;
	if (Verifier(x, y + 1)) iNb++;
	return iNb;
}

bool Grille::OnPeutAtteindre(int x, int y) const
{
	int i = 0;

	if (Verifier(x - 1, y)) i++;
	if (Verifier(x, y - 1)) i++;
	if (Verifier(x + 1, y)) i++;
	if (Verifier(x, y + 1)) i++;
	return (i > 0);
}

void Grille::AfficherTrajetTrace() const
{
	system("cls");
	cout << string(41, '-') << endl;
	for (int i = 0; i<iMAXLIGNE; i++)
	{
		cout << "| ";
		for (int j = 0; j<iMAXCOLONNES; j++)
		{
			if (caseTrajet_[i][j] != 0 && caseTrajet_[i][j] != -1)
			{
				cout.width(2);
				cout << caseTrajet_[i][j] << "  | ";
			}
			else if (caseTrajet_[i][j] == -1)
			{
				cout <<Matrice[i][j]<< "   | ";
			}
			else
			{
				cout << "E   |";
			}
		}
		cout << endl;
		cout << string(41, '-') << endl;
	}
	// Wait(500);  // millisecondes dont 0,5 seconde
	//system("pause");
}

void Grille::AfficherTrajet( system_clock::duration tempsRequis, system_clock::duration tempsRequisCumulatif) const
{
	
	cout << string(7 * iMAXCOLONNES + 1, '-') << endl;
	for (int i = 0; i<iMAXLIGNE; i++)
	{
		cout << "| ";
		for (int j = 0; j < iMAXCOLONNES; j++)
		{
			if (CaseVisite[i][j] == true)
			{
				cout.width(4);
				cout << Matrice[i][j] << " | ";
			}
			else
			{
				cout << "     | ";
			}
		}
		cout << endl;
		cout << string(7 * iMAXCOLONNES + 1, '-') << endl;
	}
	
	cout << "en " << duration_cast<microseconds>(tempsRequis).count() << " microsecondes" << endl;
	cout << "ou si vous preferez en " << duration_cast<nanoseconds>(tempsRequis).count() << " nanosecondes" << endl;
	cout << endl << "temps requis cumulatif : " << duration_cast<microseconds>(tempsRequisCumulatif).count() << " microsecondes" << endl;
	cout << sommecourrante << endl;
	// pour ne pas avoir à faire des enter quand on écrit dans un fichier de sortie...
	if (&cout == &cout) system("pause");

}