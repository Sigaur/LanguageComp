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

void Analyseur::premiersSuivants()//Calculs des Premiers Suivants et sauvegarde de ces derniers dans les tableaux m_Premiers et m_Suivants
{
    for (size_t i; i < m_tabInit.size(); i++) {
        for(size_t j = 0; j < m_terminaux.size(); j++)
        {
            /*if (m_tabInit[i][0] == m_terminaux[k])
                term = "t0";*/
        }
    }
}

void Analyseur::tableAnalyse()//Calcul de la table d'analyse et sauvegarde de cette dernière dans le m_tableAnalyse
{

}

int Analyseur::analyse(std::string input)//utilisation des attributs pour savoir si le string en input satisfait la grammaire
{
	return 0;//temporaire
}
