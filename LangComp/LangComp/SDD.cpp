#include "SDD.h"
#include <fstream>

using namespace std;

SDD::SDD()
{
}


SDD::~SDD()
{
}


void SDD::lecture(std::string nomFichier)
{
	ifstream fichier(nomFichier);

	if (!fichier)
		cout << "Fichier Introuvable" << endl;

	bool estInitial = true;
	int nbLigne = 0;
	string ligne;

	vector <string> nouvelleLigne;

	while (!fichier.eof())
	{
		std::getline(fichier, ligne);
		if (ligne == "")
		{
			estInitial = true;
			nbLigne++;
		}
		else if (estInitial)
		{
			estInitial = false;
			nouvelleLigne.push_back(ligne);
			this->m_tabInit.push_back(nouvelleLigne);
			nouvelleLigne.clear();
		}
		else
		{
			this->m_tabInit[nbLigne].push_back(ligne);
		}
	}
}

void SDD::affichage()
{
	cout << "Affichage de la grammaire (contenu SDD):" << endl << endl;

	for (int i = 0; i < m_tabInit.size(); i++)
	{
		for (int j = 0; j < m_tabInit[i].size(); j++)
		{
			if (j == 0)//Etat Initial
			{
				cout << m_tabInit[i][j] << "=";
			}
			else if(j == m_tabInit[i].size() - 1)
			{
				cout << m_tabInit[i][j] << endl;
			}
			else
			{
				cout << m_tabInit[i][j] << "|";
			}
		}
	}
}

void SDD::affichageTerminauxEtNon()
{
	cout << endl << "Affichage Terminaux:" << endl << endl;

	for (int i = 0; i < m_tabInit.size(); i++)
	{
		cout << m_tabInit[i][0] << endl;
	}
	
	cout << endl << "Affichage Non Terminaux:" << endl << endl;

	for (int i = 0; i < m_tabInit.size(); i++)
	{
		for (int j = 0; j < m_tabInit[i].size(); j++)
		{
			if (j == 0)//Etat Initial
			{
			}
			else
			{
				cout << m_tabInit[i][j] << endl;
			}
		}
	}
}

void SDD::suppresionRecu()
{

}
