#pragma once
#include "Commun.h"
#include "SDD.h"

class Analyseur
{
public:
	Analyseur();
	~Analyseur();

	void initialisation();//Appel des méthodes de m_SDD
	void premiersSuivants();//Calculs des Premiers Suivants et sauvegarde de ces derniers dans les tableaux m_Premiers et m_Suivants
	void tableAnalyse();//Calcul de la table d'analyse et sauvegarde de cette dernière dans le m_tableAnalyse
	int analyse(std::string input);//utilisation des attributs pour savoir si le string en input satisfait la grammaire

private:
	SDD m_SDD;
	std::string m_nomFichiers;//Garde en mémoire le nom du fichier contenant la grammaire initiale (Debug)
	std::vector< std::string > m_premiers;
	std::vector< std::string > m_suivants;
	std::vector< std::vector< std::string > > m_tableAnalyse;
};

