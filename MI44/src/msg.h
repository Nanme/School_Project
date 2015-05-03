/********************************
*           Objet msg           *
* Tout les methodes et fonction *
*   pour utiliser l'objet msg   *
********************************/

#include <iostream>
#include <vector>

#pragma once
class msg
{
private:
	std::vector<int> firstChar;  //Bloc de poids faible (possède les bits les plus faible).
	std::vector<int> secondChar; //Bloc de poids fort (possède les bits les plus fort).

public:
	//Constructeur
	msg();
	msg(std::vector<int> a, std::vector<int>);
	msg(char a, char b);
	msg(const msg& copy);

	//Operateur
	msg& operator=(const msg& c)
	{
		firstChar = c.firstChar;
		secondChar = c.secondChar;
		return *this;
	}
	bool isEqual(const msg& b) const;
	msg& operator^=(const msg& b);

	//Accesseur
	std::vector<int> getFirstChar() const;
	void setFirstChar(std::vector<int> value);
	void setFirstChar(char c); //Avec conversion.
	void setFirstChar(int value, int pos);
	std::vector<int> getSecondChar()const;
	void setSecondChar(std::vector<int> value);
	void setSecondChar(int value, int pos);
	void setSecondChar(char c); 

	//Manipulation
	msg shiftLeftMsg(int shiftValue) const;
	msg msg::shiftRightMsg(int shiftValue) const;
	msg function(const msg& key) const;

	//Conversion.
	void encrypt_binaire(char a, char b);
	void decrypt_binaire(char& a, char& b) const;

	//Affichage console.
	void displayMsg(std::ostream& stream);
};

//Operateur
bool operator==(const msg& a, const msg& b);
bool operator!=(const msg& a, const msg& b);
msg operator^(const msg& a, const msg& b);
std::ostream& operator<<(std::ostream& stream, msg& a);