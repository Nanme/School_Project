#include "rsa.h"

using namespace std;
//Cl�
couple gen_cle()
{
	couple res;
	int p, q, phi;
	
	//G�n�ration de p et q premier et al�atoire.
	srand(time(NULL));
	p = rand() % 12500;
	while (!test_primalite(p))
	{
		p = rand() % 12500;
	}
	q = rand() % 12500;
	while (!test_primalite(q))
	{
		q = rand() % 12500;
	}
	
	//Cr�ation de n.
	res.pl.n = p*q;
	res.pr.n = p*q;

	//Cr�ation de l'indicateur d'Euler.
	phi = (p - 1)*(q - 1);

	//Recherche de l'exposant de chiffrement e.
	res.pl.e_d = calcul_expo(phi);

	//Calcul de l'exposant de d�chiffrement d.
	res.pr.e_d = algo_euclide_gen(res.pl.e_d, phi);
	
	return res;
}

//Cryptage
//TODO : Eventuellement retourner une chaine de caract�re crypt� et en prendre une en param�tre.
double encrypt_rsa(double message, int e, int n)
{
	return expo_modul(message, e, n);
}

//D�cryptage
//TODO : Eventuellement retourner le message envoy�s et en prendre une en param�tre.
double decrypt_rsa(double message, int d, int n)
{
	return expo_modul(message, d, n);
}
//Uttilitaire
bool test_primalite(int p)
{
	if (p < 2) return false; //Exclusion de 0 et 1.
	if (p == 2) return true; //Cas 2 : vrai.
	if (p % 2 == 0) return false; //Exclusion des pairs.
	for (int i = 3; i <= sqrt(p); i+= 2) //Boucle avec esquive ces pairs, 0 et 1.
	{
		if (p % i == 0) //Test de divisibilit� par i.
		{
			return false;
		}
	}
}
int pgcd(int a, int b)
{
	if (b == 0) //Cas d'arr�t
	{
		return a;
	}
	else //Reccursivit� sur b et le raste de a par b.
	{
		pgcd(b, a % b);
	}
}
int calcul_expo(int phi)
{
	int e(0);
	//On g�n�re un al�atoire entre 1 et phi 
	//et on test s'il est premier avec phi.
	srand(time(NULL));
	e = rand() % phi;
	while (pgcd(e, phi) != 1)
	{
		e = rand() % phi;
	}
	
	return e;
}
int algo_euclide_gen(int inverse, int modulo)
{
	int r(inverse), r1(modulo), u(1), u1(0), q(0), rStack(0), uStack(0);

	//On s'arr�te des qu'on atteint un reste nul.
	while (r1 != 0)
	{
		//On r�cup�re le quotien q
		q = r / r1;
		
		//Echange de r et r1 ainsi que u et ui.
		rStack = r;
		uStack = u;
		r = r1;
		u = u1;
		
		//On calcule le r et le u suivant.
		r1 = rStack - q*r1;
		u1 = uStack - q*u1;
	}
	
	//Si u est n�gatif, on s'arrange pour l'obtenir positif.
	while (u < 0)
	{
		u = u + modulo;
	}
	return u;
}
double expo_modul(int message, int eOuD, int n)
{
	vector<int> bin(itobin(eOuD)); //Exposant e ou d en binaire.
	double res(1), base(message); //Le resultat et la base.
	
	//Parcours de l'exposant en binaire
	for (int i = bin.size() - 1; i >= 0; i--)
	{
		//S'il est �gal � 1 on calcul res,
		//si non on ne fait rien.
		if (bin[i] == 1)
		{
			res = res * base;
			res = fmod(res,n);
		}
		//On calcule la base� [n]
		base = base * base;
		base = fmod(base, n);
	}
	return res;
}
vector<int> itobin(int bin)
{
	vector<int> res;
	char buffer[50];
	
	//conversion de bin en un tableau de caact�re binaire.
	itoa(bin, buffer, 2);

	//Recup�ration du contenu des cases.
	for (int i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i]=='0')
		{
			res.push_back(0);
		}
		else
		{
			res.push_back(1);
		}
	}
	return res;
}
int bintoi(const vector<int>& bin)
{
	int res(0), base(1);

	//Conversion en d�cimal.
	for (int i = bin.size() - 1; i >= 0; i--)
	{
		res += bin[i] * base;
		base *= 2;
	}


	return res;
}