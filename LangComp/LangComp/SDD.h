#pragma once
#include "Commun.h"

class SDD
{
public:
	SDD();
	~SDD();
	void lecture(std::string nomFichier);
	void affichage();
	void affichageFirsts();
	void trouverTerminauxEtNon();
	void suppresionRecu();

	std::vector< std::vector<std::string > > m_tabInit;/*Tableau sous la forme:
														Etat Initial | Regle | Regle ...
														Etat Initial | Regle | Regle | Regle ...
														...
														*/
    std::vector< std::string > m_terminaux;
    std::vector< std::string > m_nonTerminaux;
	std::vector< Premier > m_premiers;
	std::vector< Premier > m_suivants;
};

