#include "SDD.h"
#include <fstream>

using namespace std;

SDD::SDD()
{
}


SDD::~SDD()
{
}

bool SDD::isIn2(std::vector<std::string> vectStr, std::string str)
{
	for (size_t i = 0; i < vectStr.size(); i++)
	{
		if (str == vectStr[i])
		{
			return true;
		}
	}
	return false;
}

void SDD::lecture(std::string nomFichier)
{
	std::ifstream fichier(nomFichier.c_str());

	if (!fichier)
		std::cout << "Fichier Introuvable" << endl;

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
	std::cout << "Affichage de la grammaire (contenu SDD):" << endl << endl;

	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		for (size_t j = 0; j < m_tabInit[i].size(); j++)
		{
			if (j == 0)//Etat Initial
			{
				std::cout << m_tabInit[i][j] << "=";
			}
			else if(j == m_tabInit[i].size() - 1)
			{
				std::cout << m_tabInit[i][j] << endl;
			}
			else
			{
				std::cout << m_tabInit[i][j] << "|";
			}
		}
	}
}

void SDD::affichageFirsts()
{
	std::cout << endl << endl << "Premiers : " << endl;
	for (size_t i = 0; i < m_premiers.size(); i++)
	{
		std::cout << m_premiers[i].initial << "  ";
		for (size_t j = 0; j < m_premiers[i].premiers.size(); j++)
		{
			std::cout << m_premiers[i].premiers[j];
		}
		std::cout << endl;
	}
	
}

void SDD::affichageSuivants()
{
	std::cout << endl << endl << "Suivants : " << endl;
	for (size_t i = 0; i < m_suivants.size(); i++)
	{
		std::cout << m_suivants[i].initial << "  ";
		for (size_t j = 0; j < m_suivants[i].premiers.size(); j++)
		{
			std::cout << m_suivants[i].premiers[j];
		}
		std::cout << endl;
	}

}

void SDD::trouverTerminauxEtNon()
{
	char apostrophe = 39;
	bool trouve;
	string tempStr;
	string tempChar;

	for (size_t i = 0; i < m_tabInit.size(); i++)
	{
		if (!isIn2(m_nonTerminaux, m_tabInit[i][0]))
		{
			m_nonTerminaux.push_back(m_tabInit[i][0]);
		}

	    for (size_t j = 1; j < m_tabInit[i].size(); j++)
	    {
			tempStr = m_tabInit[i][j];
            for (size_t k = 0; k < m_tabInit[i][j].size(); k++)
            {
				tempChar = tempStr[k];
				trouve = false;
				for (size_t neww = 0; neww < m_tabInit.size(); neww++)
				{
					
					
					if (tempChar == m_tabInit[neww][0])
					{
						trouve = true;
					}
				}

				if (!trouve)
				{
					if (tempChar[0] != apostrophe && !isIn2(m_terminaux, tempChar))
					{
						m_terminaux.push_back(tempChar);
					}
					
				}
				/*
                bool deter = false;
                do {
					m_nonTerminaux.push_back(m_tabInit[i][0]);
                        deter = true;
                    l++;
                } while (l < m_tabInit.size() && !deter);

                if (deter) m_nonTerminaux.push_back( m_tabInit[i][0]);
				else if (m_tabInit[i][j][k] != apostrophe)
				{
					m_terminaux.push_back({ 0, m_tabInit[i][j][k] });
				}
				*/
            }
			
	    }
	}

	std::cout << endl << "Affichage Terminaux:" << endl << endl;
	for (size_t i = 0; i < m_terminaux.size(); i++)
	{
		std::cout << m_terminaux[i] << endl;
	}
	std::cout << endl << "Affichage Non Terminaux:" << endl << endl;
	for (size_t i = 0; i < m_nonTerminaux.size(); i++)
	{
		std::cout << m_nonTerminaux[i] << endl;
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
                    //m_terminaux.push_back(nouveauTerminal);
                    nouvelleLigne.clear();
                    m_tabInit[m_tabInit.size()-1].push_back("#");
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


void SDD::tableAnalyse()
{
	vector< string > tempVect;
	string tempStr;
	string monTerminal;
	string monNonTerminal;
	string w;
	cout << endl;
	cout << endl;



	cout << "  ";

	for (size_t i = 0; i < m_terminaux.size(); i++)
	{
		tempVect.push_back(m_terminaux[i]);
	}
	m_tableAnalyse.push_back(tempVect);
	

	for (size_t i = 0; i < m_nonTerminaux.size(); i++)
	{
		tempVect.clear();
		for (size_t j = 0; j < m_nonTerminaux.size(); j++)
		{
			if(j==0)
				tempVect.push_back(m_nonTerminaux[i]);
			else
			{
				tempStr = "";
				tempVect.push_back(tempStr);
			}				
		}
		m_tableAnalyse.push_back(tempVect);
	}
	/*
	for (size_t terminal = 0; terminal < m_tableAnalyse[0].size(); terminal++)
	{
		monTerminal = m_tableAnalyse[0][terminal];
		numColonne = terminal;
		
		for (size_t i = 0; i < m_premiers.size(); i++)
		{
			for (size_t j = 0; j < m_premiers[i].premiers.size(); j++)
			{
				
				if (monTerminal == m_premiers[i].premiers[j])
				{
					w = m_premiers[i].initial;
					//looking for ligne
					for (size_t ligne = 0; ligne < m_tabInit.size(); ligne++)
					{
						for (size_t k = 0; k < m_tabInit[ligne].size(); k++)
						{
							found = m_tabInit[ligne][k].find(w);
							if (found != std::string::npos)
							{
								for (size_t z = 0; z < m_tableAnalyse.size(); z++)
								{
									if (m_tableAnalyse[z][0] == m_tabInit[ligne][0])
									{
										cout << "TRACE : " << w << endl;
										m_tableAnalyse[z][numColonne] += w;
									}
								}
							}
							
						}
					}
				}
			}
		}
	}
	*/
	string alpha;
	Premier premierAlpha;
	Premier suivantAlpha;
	string a;
	string b;
	string c;
	string premierDeAlpha;
	string alphaForSuivants;
	char apostrophe = 39;
	bool continuer, continuer2;
	size_t numA, numB;

	for (size_t regle = 0; regle < m_tabInit.size(); regle ++)
	{
		for (size_t regleNum = 1; regleNum < m_tabInit[regle].size(); regleNum++)
		{
			alpha = m_tabInit[regle][regleNum];
			continuer = true;
			numA = 0;
			while (continuer && numA < alpha.size())
			{
				b = alpha[numA];
				if (alpha[numA + 1] == apostrophe)
				{
					b += apostrophe;
				}

				if (isIn2(m_terminaux, b))
				{
					premierDeAlpha = b;
					continuer = false;
				}
				else
				{
					for (size_t z = 0; z < m_premiers.size(); z++)
					{
						if (m_premiers[z].initial == b)
						{
							for (size_t z2 = 1; z2 < m_premiers[z].premiers.size(); z2++)
							{
								premierDeAlpha += m_premiers[z].premiers[z2];
								continuer = false;
							}
						}
					}
				}
				numA++;
			}
			for (size_t premie = 0; premie < premierDeAlpha.size(); premie++)
			{
				a = premierDeAlpha[premie];
				if (premie + 1 < premierDeAlpha.size())
				{
					if (premierDeAlpha[premie + 1] == apostrophe)
					{
						a += apostrophe;
					}
				}
			}


			if (b == EPSILON)
			{
				continuer2 = true;
				numB = 0;
				while (continuer2 && numB < alpha.size())
				{
					c = alpha[numB];
					if (alpha[numB + 1] == apostrophe)
					{
						c += apostrophe;
					}

					if (isIn2(m_nonTerminaux, c))
					{
						alphaForSuivants = c;
						continuer2 = false;
					}
					numB++;
				}
				for (size_t suivan = 0; suivan < m_suivants.size(); suivan++)
				{
					if (alphaForSuivants == m_suivants[suivan].initial)
					{
						suivantAlpha = m_suivants[suivan];
					}
				}

				for (size_t suivan = 0; suivan < suivantAlpha.premiers.size(); suivan++)
				{
					for (size_t Ligne = 0; Ligne < m_tableAnalyse.size(); Ligne++)
					{
						if (m_tableAnalyse[Ligne][0] == m_tabInit[regle][0])
						{
							for (size_t Colonne = 0; Colonne < m_tableAnalyse[Ligne].size(); Colonne++)
							{
								if (m_tableAnalyse[0][Colonne] == suivantAlpha.premiers[suivan])
								{
									//cout<<"Debug" << m_tabInit[regle][0] << "->" << alpha<<endl;
									m_tableAnalyse[Ligne][Colonne] = m_tabInit[regle][0] + "->" + alpha;
								}
							}
						}
					}
				}

			}



			for (size_t Ligne = 0; Ligne < m_tableAnalyse.size(); Ligne++)
			{
				if (m_tableAnalyse[Ligne][0] == m_tabInit[regle][0])
				{
					for (size_t Colonne = 0; Colonne < m_tableAnalyse[Ligne].size(); Colonne++)
					{
						if (m_tableAnalyse[0][Colonne] == a)
						{
							//cout<<"Debug" << m_tabInit[regle][0] << "->" << alpha<<endl;
							m_tableAnalyse[Ligne][Colonne] = m_tabInit[regle][0] + "->" + alpha;
						}
					}
				}
			}

		}
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "   ";
	for (size_t i = 0; i < m_tableAnalyse.size(); i++)
	{
		for (size_t j = 0; j < m_tableAnalyse[i].size(); j++)
		{
			cout << m_tableAnalyse[i][j] << "                 ";
		}
		cout << endl;
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
