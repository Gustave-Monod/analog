/*************************************************************************
 ApacheLogParser  -  description
 -------------------
 début                : 14 nov. 2013
 copyright            : (C) 2013 par mnimierdav
 *************************************************************************/

//- Réalisation de la classe <ApacheLogParser> (fichier ApacheLogParser.cpp) -
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//#include <iomanip>
#include <sstream>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "ApacheLogParser.h"

//------------------------------------------------------------- Constantes
string theExtensions[] = { "jpg", "jpeg", "png", "gif", "bmp", "js", "css",
		"mp3", "aac", "flac", "wav", "ogg", "mp4", "mov", "m4v", "flv", "3gp",
		"svg" };
const vector<string> ApacheLogParser::EXCLUDE_LIST( theExtensions,
		theExtensions + 18 );

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
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
	// On passe l'espace et le premier crochet
	mrInStream.get( );
	mrInStream.get( );
	getline( mrInStream, dateString, ']' );
	// On laisse la class Date parser le reste:
	Date date( dateString );

	// On passe l'espace et le premier guillemet
	mrInStream.get( );
	mrInStream.get( );

	string requestString;
	getline( mrInStream, requestString, '"' );
	stringstream requestStream( requestString );
	requestStream >> method;
	requestStream >> uri;
	requestStream >> protocol;

	mrInStream >> status;
	mrInStream >> size;

	// On passe l'espace et le guillemet ouvrant
	mrInStream.get( );
	mrInStream.get( );
	getline( mrInStream, referer, '"' );

	// On passe l'espace et le guillemet ouvrant
	mrInStream.get( );
	mrInStream.get( );
	getline( mrInStream, userAgent, '"' );

	return LogEntry( ip, logName, authLogName, date, method, uri, protocol,
			status, size, referer, userAgent );
} //----- Fin de parseLine

std::vector<LogEntry> ApacheLogParser::ParseToEnd ( )
{
	vector<LogEntry> result;

	// On passe les espaces blancs
	mrInStream >> ws;
	while ( mrInStream.good( ) )
	{
		LogEntry e = ParseLine( );
		// Si cette ligne est compatible avec les options activées
		bool doNotFilter = ( !mExcludeResourceFiles && mHourFilter < 0 );
		if ( doNotFilter
				|| ( ( mHourFilter < 0 || e.date.hour == mHourFilter )
						&& ( !mExcludeResourceFiles || hasValidExtension( e ) ) ) )
		{
			result.push_back( e );
		}
		// On passe les espaces blancs
		mrInStream >> ws;
	}

	return result;

} //----- Fin de parseDocument

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
ApacheLogParser::ApacheLogParser ( std::istream& inStream,
		bool excludeResourceFiles, int hourFilter )
		: mrInStream( inStream ), mExcludeResourceFiles( excludeResourceFiles ),
			mHourFilter( hourFilter ) // default constructor
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
bool ApacheLogParser::hasValidExtension ( LogEntry& logEntry )
{
	// L'extension est valide si on n'arrive pas à la trouver dans
	// la liste des extensions exclues
	return find( EXCLUDE_LIST.begin( ), EXCLUDE_LIST.end( ),
			logEntry.GetUriExtension( ) ) == EXCLUDE_LIST.end( );
}
