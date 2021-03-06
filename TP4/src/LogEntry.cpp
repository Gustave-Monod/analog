//---------- Réalisation de la classe <LogEntry> (fichier LogEntry.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "LogEntry.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
string LogEntry::GetUriExtension ( )
{
	// S'il y a une extension présente dans le nom de fichier
	long position = uri.find_last_of( '.' );
	if ( position != string::npos )
	{
		return uri.substr( position + 1 );
	}
	else
	{
		return "";
	}
} //----- Fin de GetUriExtension
//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
LogEntry::LogEntry ( std::string const & Ip, std::string const & LogName,
		std::string const & AuthLogName, Date const & theDate,
		std::string const & Method, std::string const & Uri,
		std::string const & Protocol, int Status, long Size,
		std::string const & Referer, std::string const & UserAgent )
		: ip( Ip ), logName( LogName ), authLogName( AuthLogName ),
			date( theDate ), method( Method ), uri( Uri ), protocol( Protocol ),
			status( Status ), size( Size ), referer( Referer ),
			userAgent( UserAgent )
{
#ifdef MAP
	cout << "Appel au constructeur de <LogEntry>" << endl;
#endif
} //----- Fin de LogEntry

//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
