//- Réalisation de la classe <ApacheLogParser> (fichier ApacheLogParser.cpp) -
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ApacheLogParser.h"

//------------------------------------------------------------- Constantes
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
	// On laisse la class Date parser le reste
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
	
	// On passe les espaces blancs et le guillemet ouvrant
	mrInStream >> ws;
	mrInStream.get( );
	getline( mrInStream, userAgent, '"' );
	
	// Si on nous a donné une root URL, on l'ôte si besoin du referer
	if ( mRootUrl.size() > 0 )
	{
		referer = stripRootUrl( referer );
	}
	// Si on nous a demandé de se débarrasser des paramètes GET
	if ( mStripGetParameters )
	{
		// On s'occupe de l'URI
		uri = stripGetParameters( uri );
		referer = stripGetParameters( referer );
	}
	uri = stripIndexFilename( uri );
	referer = stripIndexFilename( referer );
	
	return LogEntry( ip, logName, authLogName, date, method, uri, protocol,
			status, size, referer, userAgent );
} //----- Fin de ParseLine

// Paramétrage de ApacheLogParser
void ApacheLogParser::SetRootUrl ( string const rootUrl )
{
	// On ignore un éventuel slash final
	if ( rootUrl[rootUrl.length() - 1] == '/' )
	{
		mRootUrl = rootUrl.substr( 0, rootUrl.length() - 1 );
	}
	else
	{
		mRootUrl = rootUrl;
	}
}
void ApacheLogParser::SetStripGetParameters ( bool stripGetParameters )
{
	mStripGetParameters = stripGetParameters;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

ApacheLogParser::ApacheLogParser ( std::istream & inStream )
		: mrInStream( inStream ), mStripGetParameters( false ),
		  mRootUrl( "" )
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
string ApacheLogParser::stripRootUrl ( string const url )
{
	string result = url;
	if ( result.substr( 0, mRootUrl.length( ) ) == mRootUrl )
	{
		result = result.substr( mRootUrl.length( ) );
		if ( result.length() < 1 )
		{
			result = "/";
		}
	}
	return result;
}
string ApacheLogParser::stripGetParameters ( string const uri )
{
	size_t positionOfGet = uri.find( '?' );
	if ( positionOfGet != string::npos )
	{
		return uri.substr( 0, positionOfGet );
	}
	else
	{
		return uri;
	}
}
string ApacheLogParser::stripIndexFilename ( string const uri )
{
	string result = uri;
	size_t position = result.find("index.html");
	if ( position != string::npos )
	{
		result = result.substr(0, position );
	}
	position = uri.find( "index.php" );
	if ( position != string::npos )
	{
		result = result.substr(0, position );
	}
	return result;
}
