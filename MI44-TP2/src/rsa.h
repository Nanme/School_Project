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

//Type pour les clé et le couple clé publique/privé
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

//Génération des clé
couple gen_cle();

//Cryptage
double encrypt_rsa(double message, int e, int n);

//Décryptage
double decrypt_rsa(double message, int d, int n);

//Uttilitaire
bool test_primalite(int p);
double expo_modul(int base, int expo, int modul); //Algorithmes d'exponentiation modulaire.
int pgcd(int a, int b);
int calcul_expo(int phi); //Génération aléatoire de l'exposant de cryptage.
//Algorithmes d'euclide généralisé pour
//déterminerl'exposant de décryptage.
int algo_euclide_gen(int inverse, int modulo); 
std::vector<int> itobin(int bin); //Conversion decimal => Binaire.
int bintoi(const std::vector<int>& bin);// Conversion Binaire => Décimal.