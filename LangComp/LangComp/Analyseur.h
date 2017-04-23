#pragma once
#include "Commun.h"
#include "SDD.h"

#define EPSILON "#"

class Analyseur : public SDD
{
public:	

	Analyseur();
	Analyseur(SDD sdd);
	~Analyseur();

	void initialisation();//Appel des mehodes de m_SDD
	void tableAnalyse();//Calcul de la table d'analyse et sauvegarde de cette derniere dans le m_tableAnalyse
	int analyse(std::string input);//utilisation des attributs pour savoir si le string en input satisfait la grammaire

	bool isIn(std::vector<std::string> vectStr, std::string str);

	Premier firsts(std::string start);//Fonction recursive prenant en entrée les états initiaux
	void firstRule1(Premier & tempPremier);
	void firstRule2(Premier & tempPremier);
	void firstRule3(Premier & tempPremier);

	Premier follows(std::string start);//Fonction recursive prenant en entrée les états initiaux
	void followRule1(Premier & tempPremier);
	void followRule2(Premier & tempPremier);
	void followRule3(Premier & tempPremier);

	

private:
	SDD m_SDD;
	std::string m_nomFichiers;//Garde en meoire le nom du fichier contenant la grammaire initiale (Debug)
	std::vector< Premier > m_premiers;
	std::vector< std::string > m_suivants;
	std::vector< std::vector< std::string > > m_tableAnalyse;
};

