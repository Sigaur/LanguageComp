#include "Analyseur.h"
using namespace std;

Analyseur::Analyseur()
{
}


Analyseur::Analyseur(SDD sdd)
{
	this->m_SDD = sdd;
}


Analyseur::~Analyseur()
{
}

void Analyseur::initialisation()//Appel des méthodes de m_SDD
{
	m_SDD.lecture(m_nomFichiers);
	m_SDD.affichage();
	m_SDD.suppresionRecu();
	m_SDD.affichage();
}

/*
Rules for First Sets

    If X is a terminal then First(X) is just X!
    If there is a Production X → ε then add ε to first(X)
    If there is a Production X → Y1Y2..Yk then add first(Y1Y2..Yk) to first(X)
    First(Y1Y2..Yk) is either
        First(Y1) (if First(Y1) doesn't contain ε)
        OR (if First(Y1) does contain ε) then First (Y1Y2..Yk) is everything in First(Y1) <except for ε > as well as everything in First(Y2..Yk)
        If First(Y1) First(Y2)..First(Yk) all contain ε then add ε to First(Y1Y2..Yk) as well.

Rules for Follow Sets

    First put $ (the end of input marker) in Follow(S) (S is the start symbol)
    If there is a production A → aBb, (where a can be a whole string) then everything in FIRST(b) except for ε is placed in FOLLOW(B).
    If there is a production A → aB, then everything in FOLLOW(A) is in FOLLOW(B)
    If there is a production A → aBb, where FIRST(b) contains ε, then everything in FOLLOW(A) is in FOLLOW(B)
*/


Premier Analyseur::firsts(std::string start)
{
	Premier temp;
	temp.initial = start;

	firstRule1(temp);
	firstRule2(temp);
	firstRule3(temp);

	
	return temp;
}

void Analyseur::firstRule1(Premier & tempPremier)
{
	bool trouve = false;
	for (size_t i = 0; i < this->m_SDD.m_tabInit.size(); i++)
	{
		if (this->m_SDD.m_tabInit[i][0] == tempPremier.initial)
		{
			trouve = true;
		}
	}
	if (!trouve)
	{
		if (!isIn(tempPremier.premiers, tempPremier.initial))
			tempPremier.premiers.push_back(tempPremier.initial);
	}
}

void Analyseur::firstRule2(Premier & tempPremier)
{
	for (size_t i = 0; i < this->m_SDD.m_tabInit.size(); i++)
	{
		if (this->m_SDD.m_tabInit[i][0] == tempPremier.initial)
		{
			for (size_t j = 1; j < this->m_SDD.m_tabInit[i].size(); j++)
			{
				if (this->m_SDD.m_tabInit[i][j] == EPSILON)
				{
					if (!isIn(tempPremier.premiers, EPSILON))
						tempPremier.premiers.push_back(EPSILON);
				}
			}
		}
	}
}

void Analyseur::firstRule3(Premier & tempPremier)
{
	string tempString;
	Premier recursivePremier;

	bool keepGoing;
	for (size_t i = 0; i < this->m_SDD.m_tabInit.size(); i++)
	{
		if (this->m_SDD.m_tabInit[i][0] == tempPremier.initial)
		{
			
			for (size_t j = 1; j < this->m_SDD.m_tabInit[i].size(); j++)//recupere une regle
			{
				//////////////////////////////
				tempString = this->m_SDD.m_tabInit[i][j];//regle
				keepGoing = true;

				for (size_t s = 0; s < tempString.size(); s++)//recupere un charactere de cette regle
				{
					
					if (keepGoing)
					{
						recursivePremier = firsts(string (1, tempString[s]));
						keepGoing = false;
						for (size_t t = 0; t < recursivePremier.premiers.size(); t++)//verifie si les premiers du caractere selectionner (premier) contient lepsilon
						{
							if (recursivePremier.premiers[t] == EPSILON)
							{
								keepGoing = true;
							}
						}
					}

					if (!keepGoing)
					{
						for (size_t t = 0; t < recursivePremier.premiers.size(); t++)
						{
							if (!isIn(tempPremier.premiers, recursivePremier.premiers[t]))
								tempPremier.premiers.push_back(recursivePremier.premiers[t]);
						}
					}
					else
					{
						for (size_t t = 0; t < recursivePremier.premiers.size(); t++)
						{
							if (!(recursivePremier.premiers[t] == EPSILON))
							{
								if (!isIn(tempPremier.premiers, recursivePremier.premiers[t]))
									tempPremier.premiers.push_back(recursivePremier.premiers[t]);/////////Combinaison rule 3.4
							}
								
						}
					}
				}
				////////////////////////////////
			}
		}
	}
}

Premier Analyseur::follows(std::string start)
{
	Premier temp;
	temp.initial = start;

	followRule1(temp);
	followRule2(temp);
	followRule3(temp);


	return temp;
}

void Analyseur::followRule1(Premier & tempPremier)
{
	if (this->m_SDD.m_suivants.size() == 0)
	{
		tempPremier.premiers.push_back("$");
	}
}

void Analyseur::followRule2(Premier & tempPremier)
{
	std::size_t found;
	string tempStr;
	Premier tempRecursive;

	bool isEpsilon = false;

	for (size_t i = 0; i < this->m_SDD.m_tabInit.size(); i++)
	{
		for (size_t j = 1; j < this->m_SDD.m_tabInit[i].size(); j++)
		{
			tempStr = this->m_SDD.m_tabInit[i][j];
			found = tempStr.find(tempPremier.initial);
			if (found != std::string::npos)
			{
				if (tempStr.substr(found + tempPremier.initial.size(), 1) != "'")
				{					
					if (found + tempPremier.initial.size() < this->m_SDD.m_tabInit[i][j].size() && found > 0)
					{
						tempStr = this->m_SDD.m_tabInit[i][j].substr(found + tempPremier.initial.size());
						tempRecursive = firsts(tempStr);
						//cout << "debug" << tempPremier.initial << " : " << this->m_SDD.m_tabInit[i][j] << endl;
						if (tempRecursive.premiers.size() == 1)
						{
								tempPremier.premiers.push_back(tempRecursive.premiers[0]);
						}
						for (size_t s = 1; s < tempRecursive.premiers.size(); s++)
						{
							if (tempRecursive.premiers[s] != EPSILON)
							{
								tempPremier.premiers.push_back(tempRecursive.premiers[s]);
								isEpsilon = true;
							}
						}
						if (isEpsilon)//Application de la regle 4
						{
							tempStr = this->m_SDD.m_tabInit[i][0];
							if (tempPremier.initial != tempStr)
							{
								tempRecursive = follows(tempStr);
							}							
						}

						for (size_t s = 1; s < tempRecursive.premiers.size(); s++)
						{
							if (tempRecursive.premiers[s] != EPSILON)
							{
								tempPremier.premiers.push_back(tempRecursive.premiers[s]);
								isEpsilon = true;
							}
						}
					}
				}
				
			}
		}
	}
}

void Analyseur::followRule3(Premier & tempPremier)
{
	std::size_t found;
	string tempStr;
	Premier tempRecursive;

	for (size_t i = 0; i < this->m_SDD.m_tabInit.size(); i++)
	{
		for (size_t j = 1; j < this->m_SDD.m_tabInit[i].size(); j++)
		{
			tempStr = this->m_SDD.m_tabInit[i][j];
			found = tempStr.find(tempPremier.initial);
			if (found != std::string::npos)
			{
				if (tempStr.substr(found + tempPremier.initial.size(), 1) != "'")
				{
					if (found + tempPremier.initial.size() == this->m_SDD.m_tabInit[i][j].size() && found > 0)
					{
						tempStr = this->m_SDD.m_tabInit[i][0];
						
						if (tempStr != tempPremier.initial)
						{
							tempRecursive = follows(tempStr);
							//cout << "debug" << tempPremier.initial << " : " << this->m_SDD.m_tabInit[i][j] << endl;
															
							for (size_t s = 1; s < tempRecursive.premiers.size(); s++)
							{							
									tempPremier.premiers.push_back(tempRecursive.premiers[s]);
							}
						}
						
					}
				}

			}
		}
	}
}



/*
void Analyseur::premiersSuivants()//Calculs des Premiers Suivants et sauvegarde de ces derniers dans les tableaux m_Premiers et m_Suivants
{
    for(size_t i = 1; i < m_tabInit.size(); i++)
    {
        bool ajout = false;
        std::string tmp = "";
        tmp += m_tabInit[i][0];
        size_t k = 0;
       
        do {
            if (m_tabInit[i][k] == "#")
            {
                tmp += "#";
                ajout = true;
            }
            k++;
        } while (!ajout && k < m_tabInit[i].size());

        if (ajout == true)
            m_premiers.push_back(tmp);
        else
            for(size_t j = 0; j < m_tabInit[j].size(); j++)
            {
                /*m_premiers.push_back(tmp);

                 // Si X est terminal alors First(X) est juste X
                if (m_tabInit[i][j][0] == m_tabInit[i][0])
                {
                    tmp += m_tabInit[i][j][0];
                }

                // Si X' est terminal alors First(X') est juste X'
                std::string tmp2 = m_tabInit[i][j][0];
                tmp2 += m_tabInit[i][j][1];
                if (tmp == m_tabInit[i][0])
                {
                    tmp += tmp2;
                }

                if (m_tabInit[i][j][0] == "#")
                {
                    tmp += "#";
                }
                m_premiers.push_back(tmp]);


                std::string tmp = m_tabInit[i][0];
                if (m_tabInit[i][j][0] == m_nonTerminaux[k])
                    premiersSuivants(k);
                else {

                    tmp += m_tabInit[i][j][0];
                    m_premiers.push_back(tmp);
                }

            }
        }
    }
}
/*
do {
if (m_terminaux[k] == m_tabInit[i][0])
{
tmp += m_tabInit[i][0];
ajout = true;
}
k++;
} while (!ajout && k < m_terminaux.size());
k = 0;
*/


/*void Analyseur::premiersSuivants(size_t i)//Calculs des Premiers Suivants et sauvegarde de ces derniers dans les tableaux m_Premiers et m_Suivants
{
    for(size_t j = 1; j < m_tabInit[i].size(); j++)
    {
        for(size_t k = 0; k < m_terminaux.size(); k++)
        {
            std::string tmp = m_tabInit[i][0];
            if (m_tabInit[i][j][0] == m_nonTerminaux[k])
                premiersSuivants(k);
            else {

                tmp += m_tabInit[i][j][0];
                m_premiers.push_back(tmp);
            }
        }
    }

}*/
void Analyseur::tableAnalyse()//Calcul de la table d'analyse et sauvegarde de cette dernière dans le m_tableAnalyse
{

}

int Analyseur::analyse(std::string input)//utilisation des attributs pour savoir si le string en input satisfait la grammaire
{
	return 0;//temporaire
}

bool Analyseur::isIn(std::vector<std::string> vectStr, std::string str)
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

