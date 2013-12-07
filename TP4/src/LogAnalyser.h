//---------- Interface de la classe <LogAnalyser> (fichier LogAnalyser.h) ------
#if ! defined ( LOGANALYSER_H_ )
#define LOGANALYSER_H_

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <queue>

#include "LogEntry.h"
#include "LinkUriReferer.h"
#include "ApacheLogParser.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types
typedef std::map<LinkUriReferer, unsigned int> THitsByLink;

typedef std::pair<std::string, int> TUriAndRefererHits;

// Pour trier la file à priorité, on définit un foncteur
class UriAndHitsGreater
{
public:
	// On trie le plus souvent en ordre inverse pour pouvoir enlever
	// facilement les éléments avec le nombre de hits le plus bas
	// (ils se retrouveront naturellement en bout de fil, on pourra les
	// supprimer d'un simple pop)
	UriAndHitsGreater ( const bool descending = false )
			: mDescending( descending )
	{
	}

	bool operator () ( const TUriAndRefererHits & rA, const TUriAndRefererHits &rB ) const
	{
		return mDescending ?
				( rA.second > rB.second ) : ( rA.second < rB.second );
	}
protected:
	bool mDescending;
};

// Cette file à priorité contiendra les # URI ayant le plus grand nombre de hits
// (# varie selon les options données par l'utilisateur)
typedef std::priority_queue<TUriAndRefererHits, std::vector<TUriAndRefererHits>,
		UriAndHitsGreater> TPriorityQueue;

//------------------------------------------------------------------------ 
// Rôle de la classe <LogAnalyser>
// Analyser les lignes lues dans un fichier de log Apache, telles que
// données par ApacheLogParser.
// Travaille avec un dictionnaire et une file à priorité inverse.
//------------------------------------------------------------------------ 

class LogAnalyser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	THitsByLink & Analyse ( );
	// Mode d'emploi :
	// Analyse
	// Retourne la map contenant toutes les informations extraites des logs.
	// Contrat :
	//

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur

	LogAnalyser ( std::istream & inStream, bool excludeResourceFiles = false,
			int hourFilter = -1 );
	// Mode d'emploi :
	// Trace la construction.

	// Pas virtual <=> pas d'allocation dynamique ici
	~LogAnalyser ( );
	// Mode d'emploi :
	// Trace la destruction.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

	void extractAll ( );
	// Mode d'emploi :
	// Lit tout ce qu'il y a à lire dans le flux et compte le nombre de hits.

	void addHit ( LogEntry & e );
	// Mode d'emploi :
	// Ajoute un (1) au nombre de hits pour un lien donné.
	// Si la LogEntry n'a pas encore été lue, on l'insère avec
	// un (1) seul hit.

	bool hasValidExtension ( LogEntry & logEntry );
	// Mode d'emploi :
	// Compare l'extension de l'URI contenue dans cette LogEntry
	// avec la liste des extensions à exclure (EXCLUDE_LIST).
	// Si l'extension est vide, on considère qu'elle est valide.

//----------------------------------------------------- Attributs protégés

	ApacheLogParser mParser;
	bool mExcludeResourceFiles;
	int mHourFilter;

	THitsByLink mHits;

	TPriorityQueue mUrisByHits;

	static const std::vector<std::string> EXCLUDE_LIST;

	static unsigned int const DEFAULT_RESULT_SIZE;
};

//--------------------------- Autres définitions dépendantes de <LogAnalyser>

#endif // LOGANALYSER_H_
