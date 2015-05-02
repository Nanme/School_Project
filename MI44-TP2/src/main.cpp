#include "rsa.h"
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>

using namespace std;

int main()
{
	int option(0), e_d(0), n(0);
	double M_C(0);
	couple c;
	string message, stack;
	vector<msg> msgBin;
	vector<double> crypted;
	char yn, a, b;
	msg mStack;
	/*do
	{
		cout << "----------Cryptage RSA---------" << endl;
		cout << "-------Par Renaud Alliot-------" << endl;
		cout << "Menu :" << endl;
		cout << " 1. Générer un clé publique et une clé privé." << endl;
		cout << " 2. Crypter un message." << endl;
		cout << " 3. Décrypter un message." << endl;
		cout << " 4. Simulation d'un protocole." << endl;
		cout << " 5. Quitter." << endl;
		cin >> option;

		switch (option)
		{
		case 1:
			c = gen_cle();
			cout << "Clé publique : (" << c.pl.n << ", " << c.pl.e_d << ")" << endl;
			cout << "Clé privée : (" << c.pr.n << ", " << c.pr.e_d << ")" << endl;
			break;
		case 2:
			cout << "Message à décrypté :" << endl;
			cin >> message;
			cout << "n = ";
			cin >> n;
			cout << "e = ";
			cin >> e_d;

			msgBin = cutStr(message); //Découpe en binaire.

			//Cryptage
			for (int i = 0; i < msgBin.size(); i++)
			{
				//On récupère le (2*i)ème caractère qu'on 
				//transforme en double.
				M_C = bintoi(msgBin[i].getSecondChar());

				//On le crypte en RSA avec les clé de l'uttilisateur
				//et on l'ajouter au tableau des caractère crypté.
				crypted.push_back(encrypt_rsa(M_C, e_d, n));

				//On récupère le (2*i+1)ème caractère qu'on 
				//transforme en double.
				M_C = bintoi(msgBin[i].getFirstChar());

				//On le crypte en RSA avec les clé de l'uttilisateur
				//et on l'ajouter au tableau des caractère crypté.
				crypted.push_back(encrypt_rsa(M_C, e_d, n));
			}

			//Test de conformité
			cout << "Voulez-vous testez le cryptage ? (O/N)" << endl;
			cin >> yn;
			if (yn == 'O')
			{
				cout << "d = ";
				cin >> e_d;
				for (int i = 0; i < msgBin.size(); i++)
				{
					//Décryptage et conversion en char.
					M_C = decrypt_rsa(crypted[2 * i], e_d, n);
					mStack.setSecondChar(itobin(M_C));
					M_C = decrypt_rsa(crypted[2 * i + 1], e_d, n);
					mStack.setFirstChar(itobin(M_C));
					mStack.decrypt_binaire(a, b);

					if (msgBin[i] != mStack)
					{
						cout << "Problème de cryptage." << endl;
					}
				}
				cout << "Cryptage conforme." << endl;
			}

			//On affiche le message crypté.
			cout << "Message crypté :" << endl;
			for (int i = 0; i < crypted.size(); i++)
			{
				cout << crypted[i] << " ";
			}
			cout << endl;
			crypted.clear();
			message.clear();
			break;
		case 3:
			cout << "Votre clé privée." << endl;
			cout << "n = ";
			cin >> n;
			cout << "d = ";
			cin >> e_d;
			cout << "Combien de caractère ?" << endl;
			cin >> option;
			for (int i = 0; i < option; i += 2)
			{
				//ième caractère.
				cout << "Caractère " << i << " : ";
				cin >> M_C;
				M_C = decrypt_rsa(M_C, e_d, n);
				mStack.setSecondChar(itobin(M_C));

				//(i+1)ème caractère.
				cout << "Caractère " << i + 1 << " : ";
				cin >> M_C;
				M_C = decrypt_rsa(M_C, e_d, n);
				mStack.setFirstChar(itobin(M_C));

				//Ajout des caractère au message.
				mStack.decrypt_binaire(a, b);
				message.push_back(a);
				message.push_back(b);
			}

			cout << message << endl;
			message.clear();
		case 4:

			break;
		default:
			break;
		}
	} while (option != 5);*/
	
	QApplication app();

	QWidget fenetre;
	fenetre.setFixedSize(300, 400);

	QPushButton bouton("Test", &fenetre);

	bouton.setFont(QFont("Courrier", 14));
	bouton.setCursor(Qt::PointingHandCursor);
	bouton.setIcon(QIcon("smile.png"));

	fenetre.show();

	system("PAUSE");
	return 0;
}

