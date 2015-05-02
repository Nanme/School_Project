#include "feistel.h"
using namespace std;

//Cryptage
void round(msg& leftBlock, msg& rightBlock, const msg& key)
{
	msg stack(rightBlock);
	rightBlock = leftBlock ^ rightBlock.function(key);
	leftBlock = stack;
}
string feistel(const string& message, const string& key)
{
	vector<msg> keyTab(cutKey(key)), msgTab(cutStr(message));
	msg stackRight, stackLeft;
	string res;
	char cStack1, cStack2;
	
	for (int i = 0; i < msgTab.size(); i+=2)
	{
		stackLeft = msgTab[i];
		stackRight = msgTab[i + 1];
		for (int j = 0; j < 4; j++)
		{
			round(stackLeft, stackRight, keyTab[i]);
		}
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
	vector<msg> keyTab(cutKey(key)), msgTab(cutStr(message));
	msg stackRight, stackLeft;
	string res;
	char cStack1, cStack2;

	for (int i = 0; i < msgTab.size(); i += 2)
	{
		stackLeft = msgTab[i];
		stackRight = msgTab[i + 1];
		for (int j = 4; j >= 0; j--)
		{
			decrypt_round(stackLeft, stackRight, keyTab[i]);
		}
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
	msg stack(leftBlock);
	leftBlock = rightBlock;
	leftBlock = stack ^ rightBlock.function(key);
}

//Uttilitaire
vector<msg> cutStr(const string& str)
{
	vector<msg> res;
	msg stack;
	int size = str.size();
	switch (size % 4)
	{
	case 0:
		for (int i = 0; i < size; i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		break;
	case 1:
		for (int i = 0; i < size - 1; i += 2)
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
	case 2:
		for (int i = 0; i < size - 1; i += 2)
		{
			stack.setFirstChar(str[i + 1]);
			stack.setSecondChar(str[i]);
			res.push_back(stack);
		}
		stack.setSecondChar(' ');
		stack.setFirstChar(' ');
		res.push_back(stack);
		break;
	case 3:
		for (int i = 0; i < size - 1; i += 2)
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