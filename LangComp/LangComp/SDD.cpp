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

void SDD::trouverTerminauxEtNon()
{
	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
	    for (size_t j = 1; j < m_tabInit[i].size(); j++)
	    {
            for (size_t k = 0; k < m_tabInit[i][j].size(); k++)
            {
                for (size_t l = 0; l < m_tabInit[i].size(); l++)
                {
                    if (m_tabInit[i][j][k] == m_tabInit[l][0][0])
                        m_nonTerminaux.push_back( {1, m_tabInit[i][j][k]} );
                    else
                        m_terminaux.push_back( {1, m_tabInit[i][j][k]} );
                }
            }
	    }
	}

    cout << endl << "Affichage Terminaux:" << endl << endl;
	for (size_t i = 0; i < m_terminaux.size(); i++)
	{
		cout << m_terminaux[i] << endl;
	}
	cout << endl << "Affichage Non Terminaux:" << endl << endl;
	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		cout << m_nonTerminaux[i] << endl;
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
                    m_terminaux.push_back(nouveauTerminal);
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
