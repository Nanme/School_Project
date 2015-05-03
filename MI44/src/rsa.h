/*************************************************
*				  Cryptage en RSA  	 	 		 *
*           Contient tout les fonctions          *
*   Necessaire pour crypter en RSA un nombre.    *
**************************************************/

#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "msg.h"
#include "feistel.h"

//Type pour les cl� et le couple cl� publique/priv�
typedef struct
{
	int n;
	int e_d;
} clef;
typedef struct
{
	clef pl;
	clef pr;
} couple;

//G�n�ration des cl�
couple gen_cle();

//Cryptage
double encrypt_rsa(double message, int e, int n);

//D�cryptage
double decrypt_rsa(double message, int d, int n);

//Uttilitaire
bool test_primalite(int p);
double expo_modul(int base, int expo, int modul); //Algorithmes d'exponentiation modulaire.
int pgcd(int a, int b);
int calcul_expo(int phi); //G�n�ration al�atoire de l'exposant de cryptage.
//Algorithmes d'euclide g�n�ralis� pour
//d�terminerl'exposant de d�cryptage.
int algo_euclide_gen(int inverse, int modulo); 
std::vector<int> itobin(int bin); //Conversion decimal => Binaire.
int bintoi(const std::vector<int>& bin);// Conversion Binaire => D�cimal.