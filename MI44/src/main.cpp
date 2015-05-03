#include "menu.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	couple c(gen_cle());
	double n(c.pl.n), e(c.pl.e_d), d(c.pr.e_d);
	int option;

	cout << "--------------MI44--------------" << endl;
	cout << "-----Securite Informatique------" << endl;
	cout << "-------Par Renaud ALLIOT--------" << endl;
	do
	{
		cout << "--------------Menu--------------" << endl;
		cout << " 1. Reseau Feistel." << endl;
		cout << " 2. Cryptage RSA." << endl;
		cout << " 3. Quitter." << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			menuFeistel();
			break;
		case 2:
			menuRSA();
			break;
		case 3:
			cout << "Au revoir !" << endl;
		default:
			cout << "Mauvaise entrée veuillez recommencer." << endl;
			break;
		}
	} while (option != 3);

	system("PAUSE");
	return 0;
}

