// MI44-TP1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "msg.h"
#include "feistel.h"

using namespace std;

int main()
{
	string encrypted(feistel("AAAA??BB", "KXCX"));
	string decrypted = decrypt_feistel(encrypted, "KXCX");
	
	cout << "AAAA??BB donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;

	encrypted = feistel("??BBAAAA", "KXCX");
	decrypted = decrypt_feistel(encrypted, "KXCX");

	cout << "??BBAAAA donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;

	encrypted = feistel("BBAABBAA", "KXCX");
	decrypted = decrypt_feistel(encrypted, "KXCX");

	cout << "BBAABBAA donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;

	encrypted = feistel("AABBAABB", "KXCX");
	decrypted = decrypt_feistel(encrypted, "KXCX");

	cout << "AABBAABB donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;

	encrypted = feistel("FEISTEL", "KXCX");
	decrypted = decrypt_feistel(encrypted, "KXCX");

	cout << "FEISTEL donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;

	encrypted = feistel("CRYPTOGRAPHIE", "KXCX");
	decrypted = decrypt_feistel(encrypted, "KXCX");

	cout << "CRYPTOGRAPHIE donne avec la clé KXCX : " << encrypted << endl;
	cout << encrypted << " une fois décrypté avec la clé KXCX donne : " << decrypted << endl;
	
	system("PAUSE");
	return 0;
}