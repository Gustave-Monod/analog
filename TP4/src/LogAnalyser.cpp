/*************************************************************************
 LogAnalyser  -  description
 -------------------
 début                : 18 nov. 2013
 copyright            : (C) 2013 par gmonod
 *************************************************************************/

//---------- Réalisation de la classe <LogAnalyser> (fichier LogAnalyser.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <algorithm>
#include <queue>

//------------------------------------------------------ Include personnel
#include "LogAnalyser.h"

//------------------------------------------------------------- Constantes

string const theExtensions[] = { "jpg", "jpeg", "png", "gif", "bmp", "js",
		"css", "mp3", "aac", "flac", "wav", "ogg", "mp4", "mov", "m4v", "flv",
		"3gp", "svg" };
const vector<string> LogAnalyser::EXCLUDE_LIST( theExtensions,
		theExtensions + 18 );

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void LogAnalyser::Analyse ( )
{
	extractAll( );
} //----- Fin de Analyse

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

LogAnalyser::LogAnalyser ( istream & inStream, bool excludeResourceFiles,
		int hourFilter )
		: mParser( inStream ), mExcludeResourceFiles( excludeResourceFiles ),
			mHourFilter( hourFilter ), mHits( ),
			mUrisByHits( UriAndHitsGreater( ) )
{
#ifdef MAP
	cout << "Appel au constructeur de <LogAnalyser>" << endl;
#endif
} //----- Fin de LogAnalyser ( std::istream, bool, int )

LogAnalyser::~LogAnalyser ( )
{
#ifdef MAP
	cout << "Appel au destructeur de <LogAnalyser>" << endl;
#endif
} //----- Fin de ~LogAnalyser

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void LogAnalyser::extractAll ( )
// Algorithme :
// Lit tant qu'il reste à lire et traite seulement si nécessaire.
{
	while ( mParser.HasMoreToParse( ) )
	{
		LogEntry e = mParser.ParseLine( );
		// Si cette ligne est compatible avec les options activées
		bool doNotFilter = ( !mExcludeResourceFiles && mHourFilter < 0 );
		if ( doNotFilter
				|| ( ( mHourFilter < 0 || e.date.hour == mHourFilter )
						&& ( !mExcludeResourceFiles || hasValidExtension( e ) ) ) )
		{
			addHit( e );
		}
	}
} //----- Fin de extractAll

void LogAnalyser::addHit ( LogEntry & e )
{
	// On cherche le couple uri <- referer
	THitsByLink::iterator it = mHits.find( LinkUriReferer( e.uri, e.referer ) );
	// S'il n'existe pas, on l'insère
	if ( it == mHits.end( ) )
	{
		mHits.insert( make_pair( LinkUriReferer( e.uri, e.referer ), 1u ) );
	}
	// Sinon, on incrémente le nombre de hits
	else
	{
		++( it->second );
	}
} //----- Fin de addHit

bool LogAnalyser::hasValidExtension ( LogEntry& logEntry )
{
	// L'extension est valide si on n'arrive pas à la trouver dans
	// la liste des extensions exclues
	return find( EXCLUDE_LIST.begin( ), EXCLUDE_LIST.end( ),
			logEntry.GetUriExtension( ) ) == EXCLUDE_LIST.end( );
} //----- Fin de hasValidExtension
