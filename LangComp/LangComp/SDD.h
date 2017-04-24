#pragma once
#include "Commun.h"
#define EPSILON "#"

class SDD
{
public:
	SDD();
	~SDD();
	void lecture(std::string nomFichier);
	void affichage();
	void affichageFirsts();
	void affichageSuivants();
	void trouverTerminauxEtNon();
	void suppresionRecu();
	bool isIn2(std::vector<std::string> vectStr, std::string str);

	void tableAnalyse();

	std::vector< std::vector<std::string > > m_tabInit;/*Tableau sous la forme:
														Etat Initial | Regle | Regle ...
														Etat Initial | Regle | Regle | Regle ...
														...
														*/
    std::vector< std::string > m_terminaux;
    std::vector< std::string > m_nonTerminaux;
	std::vector< Premier > m_premiers;
	std::vector< Premier > m_suivants;

	std::vector< std::vector <std::string > > m_tableAnalyse;
};

