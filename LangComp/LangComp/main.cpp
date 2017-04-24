#include "SDD.h"
#include "Analyseur.h"
#include <cstdlib>


int main()
{
	SDD mySDD;
	
	Premier test;

	mySDD.lecture("test.txt");
	mySDD.affichage();
	mySDD.trouverTerminauxEtNon();
	mySDD.suppresionRecu();
	mySDD.trouverTerminauxEtNon();
	mySDD.affichage();
	
	Analyseur myAnalyseur(mySDD);
	for (size_t i = 0; i < mySDD.m_tabInit.size(); i++)
	{
		test = myAnalyseur.firsts(mySDD.m_tabInit[i][0]);

		mySDD.m_premiers.push_back(test);
	}

	mySDD.affichageFirsts();

	for (size_t i = 0; i < mySDD.m_tabInit.size(); i++)
	{
		test = myAnalyseur.follows(mySDD.m_tabInit[i][0]);

		mySDD.m_suivants.push_back(test);
	}

	mySDD.affichageSuivants();

	mySDD.tableAnalyse();

	system("pause");
	return 0;
}
