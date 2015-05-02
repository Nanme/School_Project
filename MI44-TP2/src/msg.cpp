#include "msg.h"

using namespace std;

//Constructeur
msg::msg() : secondChar({ 0, 0, 0, 0, 0 }), firstChar({ 0, 0, 0, 0, 0 })
{
	
}
msg::msg(vector<int> a, vector<int> b) : firstChar(a), secondChar(b)
{

} 
msg::msg(char a, char b)
{
	secondChar.resize(5);
	firstChar.resize(5);
	encrypt_binaire(a, b);
}
msg::msg(const msg& copy) : firstChar(copy.firstChar), secondChar(copy.secondChar)
{
	
}

//Operateur
bool msg::isEqual(const msg& b) const
{
	return (firstChar == b.firstChar && secondChar == b.secondChar);
}
bool operator==(const msg& a, const msg& b)
{
	return a.isEqual(b);
}
bool operator!=(const msg& a, const msg& b)
{
	return !(a.isEqual(b));
}
msg& msg::operator^=(const msg& b)
{
	//XOR pour chaque bloc de poids faible.
	for (int i = 4; i >= 0; i--)
	{
		firstChar[i] += b.firstChar[i];
		if (firstChar[i] == 2)
		{
			firstChar[i] = 0;
		}
	}
	//XOR pour chaque bloc de poids fort.
	for (int i = 4; i >= 0; i--)
	{
		secondChar[i] += b.secondChar[i];
		if (secondChar[i] == 2)
		{
			secondChar[i] = 0;
		}
	}
	return *this;
}
msg operator^(const msg& a, const msg& b)
{
	msg copy(a);
	copy ^= b;
	return copy;
}

//Accesseur
vector<int> msg::getFirstChar() const
{
	return firstChar;
}
void msg::setFirstChar(vector<int> value)
{
	firstChar = value;
	while (firstChar.size() < 5)
	{
		firstChar.insert(firstChar.begin(), 0);
	}
}
void msg::setFirstChar(int value, int pos)
{
	if (pos < 5)
	{
		firstChar[pos] = value;
	}
}
void msg::setFirstChar(char c)
{
	int bin;
	if (isalpha(c))
	{
		bin = c - 65;
		for (int i = 4; i >= 0; i--)
		{
			firstChar[i] = bin % 2;
			bin /= 2;
		}
	}
	else
	{
		//For the special character.
		switch (c)
		{
		case 33:
			firstChar = { 1, 1, 1, 1, 0 };
			break;
		case 39:
			firstChar = { 1, 1, 1, 0, 1 };
			break;
		case 44:
			firstChar = { 1, 1, 1, 0, 0 };
			break;
		case 46:
			firstChar = { 1, 1, 0, 1, 1 };
			break;
		case 63:
			firstChar = { 1, 1, 1, 1, 1 };
			break;
		case 32:
			firstChar = { 1, 1, 0, 1, 0 };
			break;
		default:
			break;
		}
	}
}
vector<int> msg::getSecondChar() const
{
	return secondChar;
}
void msg::setSecondChar(vector<int> value)
{
	secondChar = value;
	while (secondChar.size() < 5)
	{
		secondChar.insert(secondChar.begin(), 0);
	}
}
void msg::setSecondChar(int value, int pos)
{
	if (pos < 5)
	{
		secondChar[pos] = value;
	}
}
void msg::setSecondChar(char c)
{
	int bin;

	if (isalpha(c))
	{
		//If it's an alpha character
		bin = c - 65;
		for (int i = 4; i >= 0; i--)
		{
			secondChar[i] = bin % 2;
			bin /= 2;
		}
	}
	else
	{
		//For the special character.
		switch (c)
		{
		case 33:
			secondChar = { 1, 1, 1, 1, 0 };
			break;
		case 39:
			secondChar = { 1, 1, 1, 0, 1 };
			break;
		case 44:
			secondChar = { 1, 1, 1, 0, 0 };
			break;
		case 46:
			secondChar = { 1, 1, 0, 1, 1 };
			break;
		case 63:
			secondChar = { 1, 1, 1, 1, 1 };
			break;
		case 32:
			secondChar = { 1, 1, 0, 1, 0 };
			break;
		default:
			break;
		}
	}
}

//Manipulation
msg msg::shiftLeftMsg(int shiftValue) const
{
	
	int stack;
	msg copy(firstChar, secondChar);
	/*On effectue shiftValue iteration pour effectuer
	  le décalage de shift value. on uttiliser le bits
	  bit de poids faible comme support.               */
	for (int i = 0; i < shiftValue; i++)
	{
		for (int i = 3; i >= 0; i--)
		{
			stack = copy.firstChar[4];
			copy.firstChar[4] = copy.firstChar[i];
			copy.firstChar[i] = stack;
		}
		for (int i = 4; i >= 0; i--)
		{
			stack = copy.firstChar[4];
			copy.firstChar[4] = copy.secondChar[i];
			copy.secondChar[i] = stack;
		}
	}
	return copy;
}
msg msg::shiftRightMsg(int shiftValue) const
{
	int stack;
	msg copy(firstChar, secondChar);
	/*On effectue shiftValue iteration pour effectuer
	le décalage de shift value. on uttiliser le bits
	bit de poids fort comme support.               */
	for (int i = 0; i < shiftValue; i++)
	{
		for (int i = 1; i <= 4; i++)
		{
			stack = copy.secondChar[0];
			copy.secondChar[0] = copy.secondChar[i];
			copy.secondChar[i] = stack;
		}
		for (int i = 0; i <= 4; i++)
		{
			stack = copy.secondChar[0];
			copy.secondChar[0] = copy.firstChar[i];
			copy.firstChar[i] = stack;
		}

	}
	return copy;
}
msg msg::function(const msg& key) const
{
	//On effectue un décalage puis un XOR avec la clé.
	msg copy(firstChar, secondChar);
	copy = copy.shiftLeftMsg(1);
	copy ^= key;
	return copy;
}

//Conversion
void msg::encrypt_binaire(char a, char b)
{
	int bin;
	
	//Char a
	if (isalpha(a))
	{
		//Si c'est une lettre.
		bin = a - 65;
		for (int i = 4; i >= 0; i--)
		{
			secondChar[i] = bin % 2;
			bin /= 2;
		}
	}
	else
	{
		//Pour les caractère spéciaux.
		switch (a)
		{
		case 33:
			secondChar = { 1, 1, 1, 1, 0 };
			break;
		case 39:
			secondChar = { 1, 1, 1, 0, 1 };
			break;
		case 44:
			secondChar = { 1, 1, 1, 0, 0 };
			break;
		case 46:
			secondChar = { 1, 1, 0, 1, 1 };
			break;
		case 63:
			secondChar = { 1, 1, 1, 1, 1 };
			break;
		case 32:
			secondChar = { 1, 1, 0, 1, 0 };
			break;
		default:
			break;
		}
	}
	if (isalpha(b))
	{
		//Si c'est une lettre.
		bin = b - 65;
		for (int i = 4; i >= 0; i--)
		{
			firstChar[i] = bin % 2;
			bin /= 2;
		}
	}
	else
	{
		//Pour les caractère spéciaux.
		switch (b)
		{
		case 33:
			firstChar = { 1, 1, 1, 1, 0 };
			break;
		case 39:
			firstChar = { 1, 1, 1, 0, 1 };
			break;
		case 44:
			firstChar = { 1, 1, 1, 0, 0 };
			break;
		case 46:
			firstChar = { 1, 1, 0, 1, 1 };
			break;
		case 63:
			firstChar = { 1, 1, 1, 1, 1 };
			break;
		case 32:
			firstChar = { 1, 1, 0, 1, 0 };
			break;
		default:
			break;
		}
	}
}
void msg::decrypt_binaire(char& a, char& b) const
{
	//Les caractère spéciaux.
	vector<int> excl = { 1, 1, 1, 1, 0 };
	vector<int> app = { 1, 1, 1, 0, 1 };
	vector<int> vir = { 1, 1, 1, 0, 0 };
	vector<int> pts = { 1, 1, 0, 1, 1 };
	vector<int> inter = { 1, 1, 1, 1, 1 };
	vector<int> space = { 1, 1, 0, 1, 0 };
	
	//Test des caractère spéciaux.
	if (firstChar == excl)
	{
		b = '!';
	}
	else if (firstChar == app)
	{
		b = '\'';
	}
	else if (firstChar == vir)
	{
		b = ',';
	}
	else if (firstChar == pts)
	{
		b = '.';
	}
	else if (firstChar == inter)
	{
		b = '?';
	}
	else if (firstChar == space)
	{
		b = ' ';
	}
	else
	{
		//On convertis le binaire en décimal et on ajoute 65 pour obtenir le code ASCII de la lettre.
		b = 65 + firstChar[0] * 16 + firstChar[1] * 8 + firstChar[2] * 4 + firstChar[3] * 2 + firstChar[4];
	}

	//Caractère Spéciaux
	if (secondChar == excl)
	{
		a = '!';
	}
	else if (secondChar == app)
	{
		a = '\'';
	}
	else if (secondChar == vir)
	{
		a = ',';
	}
	else if (secondChar == pts)
	{
		a = '.';
	}
	else if (secondChar == inter)
	{
		a = '?';
	}
	else if (secondChar == space)
	{
		a = ' ';
	}
	else
	{
		//Conversion en ASCII
		a = 65 + secondChar[0] * 16 + secondChar[1] * 8 + secondChar[2] * 4 + secondChar[3] * 2 + secondChar[4];
	}
}

//Flux
void msg::displayMsg(std::ostream& stream)
{
	for (int i = 0; i < 5; i++)
	{
		stream << secondChar[i];
	}
	for (int i = 0; i < 5; i++)
	{
		stream << firstChar[i];
	}
}
std::ostream& operator<<(std::ostream& stream, msg& a)
{
	a.displayMsg(stream);
	return stream;
}