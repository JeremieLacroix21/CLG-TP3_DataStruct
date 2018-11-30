#include "Grille.h"
#include <iostream> 
#include <fstream> 
#include <ostream>
#include <string>
using namespace std;

unsigned int AfficherMenu();
string DemanderFichier();
int main()
{	
	system("color f0");
	ifstream fichier("Matrice.txt");
	Grille Magrille;

	Magrille.RemplirGrille(fichier);

	Magrille.AfficherGrille();


	Magrille.Solutionner();
	system("pause");
	fichier.close();
	return 0; 
}

string DemanderFichier()
{
		string Nomfichier;
		cout << "Veuillez entrer Un nom de fichier :" << endl;
		cin >> Nomfichier;
		return Nomfichier;
}
unsigned int AfficherMenu()
{		unsigned int choix;
		cout << "***************************************" << endl << "1. Afficher la matrice originale" << endl <<
			"2. Ajouter un ‘x’ dans la matrice" << endl << "0. Quitter" << endl << "***************************************" << endl;
		cin >> choix;
		return choix;
}