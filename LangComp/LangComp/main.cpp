#include "SDD.h"


int main()
{
	SDD mySDD;
	mySDD.lecture("test.txt");
	mySDD.affichage();
	mySDD.affichageTerminauxEtNon();
	system("pause");
	return 0;
}