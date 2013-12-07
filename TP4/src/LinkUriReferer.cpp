//---------- Réalisation de la classe <LinkUriReferer> (fichier LinkUriReferer.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "LinkUriReferer.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//------------------------------------------------- Surcharge d'opérateurs
bool LinkUriReferer::operator < ( LinkUriReferer const & b ) const
{
	// this < b si l'URI est inférieure, ou à URI égale
	// si le referer est inférieur (ordre alphanumérique)
	return ( Uri == b.Uri ) ? ( Referer < b.Referer ) : ( Uri < b.Uri );
} //----- Fin de operator <

//-------------------------------------------- Constructeurs - destructeur
LinkUriReferer::LinkUriReferer ( string const uriParam, string const refererParam )
: Uri(uriParam), Referer(refererParam)
{
#ifdef MAP
    cout << "Appel au constructeur de <LinkUriReferer>" << endl;
#endif
} //----- Fin de LinkUriReferer ( string const, string const )

LinkUriReferer::~LinkUriReferer ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <LinkUriReferer>" << endl;
#endif
} //----- Fin de ~LinkUriReferer

//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées