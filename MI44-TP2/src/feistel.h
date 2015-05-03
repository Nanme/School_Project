/*******************************
*        R�seau Feistel        *
* Contient tout les fonctions  *
* Necessaire pour crypter avec *
*      le reseau Feistel.      *
********************************/
#include "msg.h"
#include <string>

//Cryptage
void round(msg& leftBlock, msg& rightBlock, const msg& key); //Un tour de cryptage.
std::string feistel(const std::string& message, const std::string& key); //Reseau feistel sur 4 tours

//D�cryptage
std::string decrypt_feistel(const std::string& message, const std::string& key); //R�seau de d�cryptage.
void decrypt_round(msg& leftBlock, msg& rightBlock, const msg& key); //Tour de d�cryptage.

//Uttilitaire
std::vector<msg> cutStr(const std::string& str); //D�coupe d'un message en bloc de 8 caract�re.
std::vector<msg> cutKey(const std::string& key); //D�coupe de la cl� en bloc.