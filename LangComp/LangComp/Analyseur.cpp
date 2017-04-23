#include "Analyseur.h"


Analyseur::Analyseur()
{
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


void Analyseur::premiersSuivants()//Calculs des Premiers Suivants et sauvegarde de ces derniers dans les tableaux m_Premiers et m_Suivants
{
    for(size_t i = 1; i < m_tabInit.size(); i++)
    {
        bool ajout = false;
        std::string tmp = "";
        tmp += m_tabInit[i][0];
        size_t k = 0;
        do {
            if (m_terminaux[k] == m_tabInit[i][0])
            {
                tmp += m_tabInit[i][0];
                ajout = true;
            }
            k++;
        } while (!ajout && k < m_terminaux.size());
        k = 0;
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

            }*/
        }
    }
}
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
