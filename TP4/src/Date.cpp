//---------- Réalisation de la classe <Date> (fichier Date.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Date.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
Date::Date ( string const & dateString )
// Exemple de format de la string reçue :
// 08/Sep/2012:11:15:00 +0200
{
#ifdef MAP
	cout << "Appel au constructeur de <Date>" << endl;
#endif
	stringstream dateStream( dateString );
	string buffer;

	getline( dateStream, buffer, '/' );
	day = atoi( buffer.c_str( ) );

	getline( dateStream, month, '/' );

	getline( dateStream, buffer, ':' );
	year = atoi( buffer.c_str( ) );

	getline( dateStream, buffer, ':' );
	hour = atoi( buffer.c_str( ) );

	getline( dateStream, buffer, ':' );
	minutes = atoi( buffer.c_str( ) );

	seconds = 0;
	dateStream >> seconds;

	dateStream >> utcOffset;
} //----- Fin de Date

//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
