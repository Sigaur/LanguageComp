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
	std::ifstream fichier(nomFichier.c_str());

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

	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		for (size_t j = 0; j < m_tabInit[i].size(); j++)
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

	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		cout << m_tabInit[i][0] << endl;
	}

	cout << endl << "Affichage Non Terminaux:" << endl << endl;

	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		for (size_t j = 0; j < m_tabInit[i].size(); j++)
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
    for (size_t i = 0; i < m_tabInit.size(); i++)
    {
        bool recur = false;
        size_t j = 1;
        while (j < m_tabInit[i].size())
        {
            if (m_tabInit[i][0][0] == m_tabInit[i][j][0])
            {
                recur = true;
                /// AJOUTE TERMINAL
                string nouveauTerminal = m_tabInit[i][0] + "'";
                if (m_tabInit[m_tabInit[i].size()-1][0] != nouveauTerminal)
                {
                    vector<string> nouvelleLigne;
                    nouvelleLigne.push_back(nouveauTerminal);
                    m_tabInit.push_back(nouvelleLigne);
                    nouvelleLigne.clear();
                    m_tabInit[m_tabInit.size()-1].push_back("$");
                }
                /// CREE REGLE ET SUPPRIME ANCIENNE
                string temp;
                for (size_t k = 1; k < m_tabInit[i][j].length(); k++)
                {
                    temp += m_tabInit[i][j][k];
                }
                temp += nouveauTerminal;
                m_tabInit[m_tabInit.size()-1].push_back(temp);
                m_tabInit[i].erase(m_tabInit[i].begin() + j);
            }
            else
            {
                if (recur == true)
                    m_tabInit[i][j] += (m_tabInit[i][0] + "'");

                j++;
            }
        }
    }
}
/*
cd path, ls lister, cd.. dossier parent
git status
git add *.c *.hpp
git commit -m "NOM"
git pull http://GitHub.com/Sigaur/LanguageComp.git
git push http://GitHub.com/Sigaur/LanguageComp.git master
git status
*/
