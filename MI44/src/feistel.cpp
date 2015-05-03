#include "feistel.h"
using namespace std;

//Cryptage
void round(msg& leftBlock, msg& rightBlock, const msg& key)
{
	msg stack(leftBlock); //G(i)
	msg resFunction;

	leftBlock = rightBlock; //G(i+1) = D(i)
	resFunction = rightBlock.function(key);
	rightBlock = stack ^ resFunction; //D(i+1) = G(i) + function(D(i), K(i))
}
string feistel(const string& message, const string& key)
{
	vector<msg> keyTab(cutKey(key)), msgTab(cutStr(message)); //Découpe de la clé et du message.
	msg stackRight, stackLeft; //Bloc Droit | Bloc Gauche
	string res; //Resultat
	char cStack1, cStack2; //stockage des caractère décrypté

	//Boucle de parcours du message.
	for (int i = 0; i < msgTab.size(); i += 2)
	{
		stackLeft = msgTab[i];
		stackRight = msgTab[i + 1];
		//Boucle des 4 tours de cryptages.
		for (int j = 0; j < 4; j++)
		{
			round(stackLeft, stackRight, keyTab[j]);
		}
		//Ajout des caractère au message.
		stackLeft.decrypt_binaire(cStack1, cStack2);
		res.push_back(cStack1);
		res.push_back(cStack2);
		stackRight.decrypt_binaire(cStack1, cStack2);
		res.push_back(cStack1);
		res.push_back(cStack2);
	}
	return res;
}

//Décryptage
string decrypt_feistel(const string& message, const string& key)
{
	vector<msg> keyTab(cutKey(key)), msgTab(cutStr(message));//Découpe de la clé et du message.
	msg stackRight, stackLeft; //Bloc Droit | Bloc Gauche
	string res; //Résultat 
	char cStack1, cStack2; //Stockage des caractère décrypté

	//Boucle de parcours du message.
	for (int i = 0; i < msgTab.size(); i += 2)
	{
		stackLeft = msgTab[i];
		stackRight = msgTab[i + 1];
		//Boucle des 4 tours de décryptages.
		for (int j = 3; j >= 0; j--)
		{
			decrypt_round(stackLeft, stackRight, keyTab[j]);
		}
		
		//Ajout des caractère au message.
		stackLeft.decrypt_binaire(cStack1, cStack2);
		res.push_back(cStack1);
		res.push_back(cStack2);
		stackRight.decrypt_binaire(cStack1, cStack2);
		res.push_back(cStack1);
		res.push_back(cStack2);
	}
	return res;
}
void decrypt_round(msg& leftBlock, msg& rightBlock, const msg& key)
{
	msg stack(rightBlock);// D(i+1)
	msg resFunction;

	rightBlock = leftBlock; //D(i) = G(i+1)
	resFunction = leftBlock.function(key);
	leftBlock = stack ^ resFunction; //G(i) = D(i+1) + function(D(i), K(i))
}

//Uttilitaire
vector<msg> cutStr(const string& str)
{
	vector<msg> res;
	msg stack;
	int size = str.size();
	
	//On vérifie s'il faut compléter par des espace la chaine str.
	switch (str.size() % 4)
	{
	case 0: //Cas sans complétion
		for (int i = 0; i < str.size(); i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		break;
	case 1: //On complete de 3 ' '
		for (int i = 0; i < str.size() - 1; i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		stack.setSecondChar(str[size - 1]);
		stack.setFirstChar(' ');
		res.push_back(stack);
		stack.setSecondChar(' ');
		stack.setFirstChar(' ');
		res.push_back(stack);
		break;
	case 2: //On complète de 2 ' '.
		for (int i = 0; i < str.size(); i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		stack.setSecondChar(' ');
		stack.setFirstChar(' ');
		res.push_back(stack);
		break;
	case 3:// On complete de 1 ' '
		for (int i = 0; i < str.size() - 1; i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		stack.setSecondChar(str[size - 1]);
		stack.setFirstChar(' ');
		res.push_back(stack);

	}
	return res;
}
vector<msg> cutKey(const string& key)
{
	msg stack;
	vector<msg> keyTab;
	//Parcours du message avec découpe.
	for (int i = 0; i < 4; i++)
	{
		if (i != 3)
		{
			stack.setFirstChar(key[i + 1]);
			stack.setSecondChar(key[i]);
			keyTab.push_back(stack);
		}
		else
		{
			stack.setFirstChar(key[0]);
			stack.setSecondChar(key[3]);
			keyTab.push_back(stack);
		}
	}
	return keyTab;
}