//---------- Réalisation de la classe <LogAnalyser> (fichier LogAnalyser.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogAnalyser.h"

//------------------------------------------------------------- Constantes

string const theExtensions[] = { "jpg", "jpeg", "png", "gif", "bmp", "js",
		"css", "mp3", "aac", "flac", "wav", "ogg", "mp4", "mov", "m4v", "flv",
		"3gp", "svg" };
const vector<string> LogAnalyser::EXCLUDE_LIST( theExtensions,
		theExtensions + 18 );

// TODO: rendre contrôlable par le paramètre -n
unsigned int const DEFAULT_RESULT_SIZE = 10u;
// TODO: rendre contrôlable par le paramètre -l
unsigned int const DEFAULT_MINIMUM_NUMBER_OF_HITS = 3u;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
THitsByLink & LogAnalyser::Analyse ( )
// Extrait tout et parcourt la map pour créer la file à priorité :
// Pour chaque entrée de la map avec la même URI (la map est triée par URI,
// et à URI égales par referer) on agrège le nombre de hits (somme).
{
	// On génère la map à partir du fichier de log, en prenant en compte les options
	extractAll( );

	THitsByLink::const_iterator it;
	string currentUri = "";
	TUriAndRefererHits pair;
	
	// On parcourt toute la map
	for ( it = mHits.begin( ); it != mHits.end( ); ++it )
	{
		// Dans le premier tour, on initialise la paire (URI, #hits)
		if ( it == mHits.begin( ) )
		{
			pair = make_pair( it->first.Uri, it->second );
			currentUri = pair.first;
			continue;
		}
		
		// Si cette ligne pointe encore vers la même URI, on ajoute les hits
		if ( currentUri == it->first.Uri )
		{
			pair.second = pair.second + it->second;
		}
		// Si les URI sont différentes, ou que l'on est à la fin du parcours,
		// c'est qu'on a compté tous les hits vers cette URI.
		// Ils sont pour le moment stockés dans pair.second.
		else
		{
			// TOOD : avec -l, on ne compte cette URI que si elle a un referer
			// lui fournissant #hits > minimum
			if ( true ) // pair.second >= DEFAULT_MINIMUM_NUMBER_OF_HITS )
			{
				// On insère le nombre total de hits pour cette URI dans la file
				mUrisByHits.push( pair );
				// Si la file dépasse la taille maximale demandée (ex 10 plus grands),
				// on fait sauter la dernière URI de la file (la moins bonne)
				if ( mUrisByHits.size( ) > 50 ) // DEFAULT_RESULT_SIZE
				{
					mUrisByHits.pop( );
				}
			}
			// TODO : Effacer tout ce qui concerne l'URI que l'on vient de traiter
			// dans la map
			
			// On passe à la prochaine URI
			currentUri = it->first.Uri;
			pair = make_pair( it->first.Uri, it->second );
		}
		//cout << it->first.Uri << " <- " << it->first.Referer << " : " << it->second << endl;
	}
	
	// TODO : traiter la dernière ligne, en particulier dans le cas où
	// elle porte sur une URI différente
	
	// Test : afficher le nombre total de hits comptabilisés
	// TODO : supprimer ce test
	long totalHits = 0;
	while (!mUrisByHits.empty())
	{
		totalHits += mUrisByHits.top().second;
		mUrisByHits.pop();
	}
    cout << totalHits << " hits comptés dans la file." << endl;
	
	return mHits;
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
	long compteur = 0;
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
			++compteur;
		}
	}
	cout << compteur << " lignes extraites des logs." << endl;
} //----- Fin de extractAll

void LogAnalyser::addHit ( LogEntry & e )
{
    // On cherche le couple uri <- referer
    LinkUriReferer l (e.uri, e.referer);
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

bool LogAnalyser::hasValidExtension ( LogEntry& logEntry )
{
	// L'extension est valide si on n'arrive pas à la trouver dans
	// la liste des extensions exclues
	return find( EXCLUDE_LIST.begin( ), EXCLUDE_LIST.end( ),
			logEntry.GetUriExtension( ) ) == EXCLUDE_LIST.end( );
} //----- Fin de hasValidExtension
