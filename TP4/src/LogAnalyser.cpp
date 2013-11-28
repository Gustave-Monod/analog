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

// TODO: passer en paramètre, par défaut à
unsigned int const DEFAULT_RESULT_SIZE = 10u;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void LogAnalyser::Analyse ( )
// Extrait tout et parcours la map pour créer la file à priorité:
// Pour chaque entrée de la map avec la même URI (la map est triée par URI,
// et à URI égales par referer) on agrège le nombre de hits (somme).
{
	extractAll( );

	THitsByLink::const_iterator it, currentUri;
	TUriAndRefererHits pair;

	for ( it = mHits.begin( ), currentUri = mHits.begin( ); it != mHits.end( );
			++it )
	{
		// Dans le premier tour, on initialise la paire.
		if ( it == mHits.begin( ) )
		{
			pair = make_pair( it->first.Uri, it->second );
		}

		// Ensuite, on augmente le nombre de hits totaux pour des URI égales
		if ( currentUri->first.Uri == it->first.Uri )
		{
			pair.second = pair.second + it->second;
		}
		// Si les URI sont différentes, c'est qu'on a finit la somme:
		else
		{
			// TODO Si on est >= nombre minimum de hits (-l)
//			if ( pair.second >= nombreMinimum )
//			{
				// On insère le nombre total de hits dans la file
				mUrisByHits.push( pair );
				// Si on dépasse la taille souhaitée (ex 10 plus grands)
//				if ( mUrisByHits.size( ) >  10 /*DEFAULT_RESULT_SIZE*/ )
//				{
//					// On enlève celui avec le score le moins bon
//					mUrisByHits.pop( );
//				}
//			}
			// TODO On efface tout de la map
//			else
//			{
//			}
			// On remet la paire à la valeur nécessaire pour la prochaine URI
			pair = make_pair( it->first.Uri, it->second );
		}
	}
	// TODO: enlever (trace de test) et en plus la file est vidée.
	while ( !mUrisByHits.empty( ) )
	{
		TUriAndRefererHits pair = mUrisByHits.top( );
		cout << pair.first << " " << pair.second << endl;
		mUrisByHits.pop( );
	}
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
