#pragma once
#include "Commun.h"

class SDD
{
public:
	SDD();
	~SDD();
	void lecture(std::string nomFichier);
	void affichage();
	void affichageTerminauxEtNon();
	void suppresionRecu();

private:
	std::vector< std::vector< std::string > > m_tabInit;/*Tableau initial sous la forme:
														Etat Initial | Regle | Regle ...
														Etat Initial | Regle | Regle | Regle ...
														...
														*/

};

