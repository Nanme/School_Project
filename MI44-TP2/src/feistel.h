/*******************************
*        Réseau Feistel        *
* Contient tout les fonctions  *
* Necessaire pour crypter avec *
*      le reseau Feistel.      *
********************************/
#include "msg.h"
#include <string>

//Cryptage
void round(msg& leftBlock, msg& rightBlock, const msg& key); //Un tour de cryptage.
std::string feistel(const std::string& message, const std::string& key); //Reseau feistel sur 4 tours

//Décryptage
std::string decrypt_feistel(const std::string& message, const std::string& key); //Réseau de décryptage.
void decrypt_round(msg& leftBlock, msg& rightBlock, const msg& key); //Tour de décryptage.

//Uttilitaire
std::vector<msg> cutStr(const std::string& str); //Découpe d'un message en bloc de 8 caractère.
std::vector<msg> cutKey(const std::string& key); //Découpe de la clé en bloc.