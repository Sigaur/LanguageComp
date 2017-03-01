#pragma once
#include "Commun.h"

class SDD
{
public:
	SDD();
	~SDD();
	void lecture(std::string fichier);
	void affichage();
	void suppresionRecu();

private:
	std::vector< std::vector< std::string > > m_tabInit;/*Tableaun initial sous la forme:
														Etat Initial | Regle | Regle ...
														Etat Initial | Regle | Regle | Regle ...
														...
														*/
	
};

