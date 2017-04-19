#include "SDD.h"


int main()
{
	SDD mySDD;
	mySDD.lecture("test.txt");
	mySDD.affichage();
	mySDD.affichageTerminauxEtNon();
	mySDD.suppresionRecu();
	mySDD.affichage();
	system("pause");
	return 0;
}
