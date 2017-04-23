#include "SDD.h"
#include <cstdlib>


int main()
{
	SDD mySDD;
	mySDD.lecture("test.txt");
	mySDD.affichage();
	mySDD.trouverTerminauxEtNon();
	mySDD.suppresionRecu();
	mySDD.affichage();
	system("pause");
	return 0;
}
