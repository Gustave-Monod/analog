//- Réalisation de la classe <ApacheLogParser> (fichier ApacheLogParser.cpp) -
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ApacheLogParser.h"

//------------------------------------------------------------- Constantes

string const ApacheLogParser::ROOT_URL ( "http://intranet-if.insa-lyon.fr/" );
// Sert à déterminer que /page.html est la même que ROOT_URL + "page.html"
// On décide d'enlever cette chaîne si on la trouve (plus lisible que l'ajout)

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool ApacheLogParser::HasMoreToParse ( )
{
	mrInStream >> ws;
	return mrInStream.good( );
}

LogEntry ApacheLogParser::ParseLine ( )
{
	string ip;
	string logName;
	string authLogName;
	string method;
	string uri;
	string protocol;
	int status;
	long size;
	string referer;
	string userAgent;
	mrInStream >> ip;
	mrInStream >> logName;
	mrInStream >> authLogName;

	string dateString;
	// On passe les espaces blancs et le crochet ouvrant
	mrInStream >> ws;
	mrInStream.get( );
	getline( mrInStream, dateString, ']' );
	// On laisse la class Date parser le reste:
	Date date( dateString );

	// On passe les espaces blancs et le guillemet ouvrant
	mrInStream >> ws;
	mrInStream.get( );

	string requestString;
	getline( mrInStream, requestString, '"' );
	stringstream requestStream( requestString );
	requestStream >> method;
	requestStream >> uri;
	requestStream >> protocol;

	mrInStream >> status;

	// On passe les espaces blancs
	mrInStream >> ws;
	// Si la taille a été anonymisée
	if ( '-' == mrInStream.peek( ) )
	{
		// On la met à zéro
		size = 0;
		// On passe le tiret
		mrInStream.get( );
	}
	else
	{
		mrInStream >> size;
	}

	// On passe les espaces blancs et le guillemet ouvrant
	mrInStream >> ws;
	mrInStream.get( );
	getline( mrInStream, referer, '"' );

	if ( ROOT_URL == referer.substr( 0, ROOT_URL.length( ) ) )
	// Si la chaîne commence par la ROOT_URL
	{
		// On enlève la ROOT_URL
		referer = "/" + referer.substr( ROOT_URL.length( ) );
	}

	// On passe les espaces blancs et le guillemet ouvrant
	mrInStream >> ws;
	mrInStream.get( );
	getline( mrInStream, userAgent, '"' );

	return LogEntry( ip, logName, authLogName, date, method, uri, protocol,
			status, size, referer, userAgent );
} //----- Fin de ParseLine

//std::vector<LogEntry> ApacheLogParser::ParseToEnd ( )
//{
//	vector<LogEntry> result;
//
//	// On passe les espaces blancs
//	mrInStream >> ws;
//	while ( mrInStream.good( ) )
//	{
//		LogEntry e = ParseLine( );
//		// Si cette ligne est compatible avec les options activées
//		bool doNotFilter = ( !mExcludeResourceFiles && mHourFilter < 0 );
//		if ( doNotFilter
//				|| ( ( mHourFilter < 0 || e.date.hour == mHourFilter )
//						&& ( !mExcludeResourceFiles || hasValidExtension( e ) ) ) )
//		{
//			result.push_back( e );
//		}
//		// On passe les espaces blancs
//		mrInStream >> ws;
//	}
//
//	return result;
//
//} //----- Fin de ParseToEnd

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

ApacheLogParser::ApacheLogParser ( std::istream & inStream )
		: mrInStream( inStream )
{
#ifdef MAP
	cout << "Appel au constructeur de <ApacheLogParser>" << endl;
#endif
} //----- Fin de ApacheLogParser ( std::istream &, bool, int )

ApacheLogParser::~ApacheLogParser ( )
{
#ifdef MAP
	cout << "Appel au destructeur de <ApacheLogParser>" << endl;
#endif
} //----- Fin de ~ApacheLogParser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
