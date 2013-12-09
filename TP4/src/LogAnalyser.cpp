//---------- Réalisation de la classe <LogAnalyser> (fichier LogAnalyser.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LinkUriReferer.h"
#include "LogAnalyser.h"

//------------------------------------------------------------- Constantes

string const theExtensions[] = { "jpg", "jpeg", "png", "gif", "bmp", "ico",
		"js", "css", "mp3", "aac", "flac", "wav", "ogg", "mp4", "mov", "m4v",
		"flv", "3gp", "svg" };
const vector<string> LogAnalyser::EXCLUDE_LIST( theExtensions,
		theExtensions + 18 );

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
TPriorityQueue & LogAnalyser::Analyse ( )
// Extrait tout et parcourt la map pour créer la file à priorité :
// Pour chaque entrée de la map avec la même URI (la map est triée par URI,
// et à URI égales par referer) on agrège le nombre de hits (somme).
{
	// On génère la map à partir du fichier de log, en prenant en compte
	// les éventuelles options de filtrage
	extractAll( );
	
	if ( mHits.size( ) < 1 )
	{
		return mTopHits;
	}
	
	TUriAndRefererHits currentPair = make_pair( mHits.begin( )->first.Uri, 0 );
	// On parcourt toute la map
	for ( THitsByLink::iterator it = mHits.begin( ); it != mHits.end( );
	/* pas d'incrémentation */)
	{
		// Si cette ligne pointe vers la même URI que la précédente
		// on ajoute ces hits au total
		if ( it->first.Uri == currentPair.first )
		{
			currentPair.second += it->second;
		}
		// Sinon, c'est le moment de faire une insertion dans le top
		else
		{
			insertInTopHits( currentPair );
			
			// On passe à cette nouvelle URI
			currentPair = make_pair( it->first.Uri, it->second );
		}
		// Option -l : pour qu'un lien survive dans les résultats,
		// il doit porter au moins mMinimumRefererHits
		if ( (int) it->second < mMinimumRefererHits )
		// ATTENTION : ne pas comparer des uint avec des int...
		{
			mHits.erase( it++ );
		}
		else
		{
			++it;
		}
	}
	// On maintenant traite la dernière ligne de la map
	insertInTopHits( currentPair );

	return mTopHits;
} //----- Fin de Analyse

THitsByLink & LogAnalyser::getData ( )
{
	return mHits;
} //----- Fin de getData

// Fonctions de paramétrage du ApacheLogParser
void LogAnalyser::SetRootUrl ( string const rootUrl )
{
	mParser.SetRootUrl( rootUrl );
}
void LogAnalyser::SetStripGetParameters ( bool stripGetParameters )
{
	mParser.SetStripGetParameters( stripGetParameters );
}
// Fonctions de paramétrage du LogAnalyser
void LogAnalyser::SetExcludeResourceFiles ( bool excludeResourceFiles )
{
	mExcludeResourceFiles = excludeResourceFiles;
}
void LogAnalyser::SetHourFilter ( int hourFilter )
{
	mHourFilter = hourFilter;
}
void LogAnalyser::SetMinimumRefererHits ( int minimumRefererHits )
{
	mMinimumRefererHits = minimumRefererHits;
}
void LogAnalyser::SetTopSizeLimit ( int topSizeLimit )
{
	mTopSizeLimit = topSizeLimit;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

LogAnalyser::LogAnalyser ( istream & inStream, bool excludeResourceFiles,
		int hourFilter, int minimumRefererHits )
		: mParser( inStream ), mExcludeResourceFiles( excludeResourceFiles ),
			mHourFilter( hourFilter ),
			mMinimumRefererHits( minimumRefererHits ), mHits( ),
			mTopHits( UriAndHitsGreater( ) )
{
	mTopSizeLimit = DEFAULT_TOP_SIZE_LIMIT;
	
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
	LinkUriReferer l( e.uri, e.referer );
	THitsByLink::iterator it = mHits.find( l );
	
	// S'il n'existe pas, on l'insère
	if ( it == mHits.end( ) )
	{
		mHits.insert( make_pair( LinkUriReferer( e.uri, e.referer ), 1u ) );
	}
	// Sinon, on incrémente le nombre de hits pour ce couple
	else
	{
		++( it->second );
	}
} //----- Fin de addHit

void LogAnalyser::insertInTopHits ( TUriAndRefererHits & pair )
{
	// On insère le nombre total de hits pour cette URI dans la file
	mTopHits.push( pair );
	// Si la file dépasse la taille maximale demandée (ex 10 plus grands),
	// on fait sauter la dernière URI de la file (la moins bonne)
	if ( mTopHits.size( ) > mTopSizeLimit )
	{
		mTopHits.pop( );
	}
} //----- Fin de insertInQueueIfNecessary

bool LogAnalyser::hasValidExtension ( LogEntry& logEntry )
{
	// L'extension est valide si on n'arrive pas à la trouver dans
	// la liste des extensions exclues
	return find( EXCLUDE_LIST.begin( ), EXCLUDE_LIST.end( ),
			logEntry.GetUriExtension( ) ) == EXCLUDE_LIST.end( );
} //----- Fin de hasValidExtension
