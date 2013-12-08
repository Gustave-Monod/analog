//---------- Interface de la classe <LogAnalyser> (fichier LogAnalyser.h) ------
#if ! defined ( LOGANALYSER_H_ )
#define LOGANALYSER_H_

//--------------------------------------------------- Interfaces utilisées
#include "LogEntry.h"
#include "ApacheLogParser.h"
#include "LogAnalyserTypes.h"

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
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
	TPriorityQueue & Analyse ( );
	// Mode d'emploi :
	// Analyse les logs et construit un top N des URIs (en nombre de hits).
	// Retourne la file à priorité contenant le top N.
	
	THitsByLink & getData ( );
	
	// Paramétrage de ApacheLogParser
	void SetRootUrl ( std::string const rootUrl );
	void SetStripGetParameters ( bool stripGetParameters );
	// Paramétrage de LogAnalyser
	void SetExcludeResourceFiles ( bool excludeResourceFiles );
	void SetHourFilter ( int hourFilter );
	void SetMinimumRefererHits ( int minimumRefererHits );
	void SetTopSizeLimit ( int topSizeLimit );

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur

	LogAnalyser ( std::istream & inStream, bool excludeResourceFiles = false,
			int hourFilter = -1, int minimumRefererHits = -1 );
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
	
	void insertInTopHits ( TUriAndRefererHits & pair );
	// Mode d'emploi :
	// Ajoute un couple (URI, #hits) au top (mUrisByHits) en respectant
	// l'éventuelle option -n qui limite la taille maximale du top.
	
	bool hasValidExtension ( LogEntry & logEntry );
	// Mode d'emploi :
	// Compare l'extension de l'URI contenue dans cette LogEntry
	// avec la liste des extensions à exclure (EXCLUDE_LIST).
	// Si l'extension est vide, on considère qu'elle est valide.

//----------------------------------------------------- Attributs protégés

	ApacheLogParser mParser;
	THitsByLink mHits;
	TPriorityQueue mTopHits;
	
	static const std::vector<std::string> EXCLUDE_LIST;
	static unsigned int const DEFAULT_TOP_SIZE_LIMIT = 10;
	
	bool mExcludeResourceFiles;
	int mHourFilter;
	int mMinimumRefererHits;
	int mTopSizeLimit;
};

//--------------------------- Autres définitions dépendantes de <LogAnalyser>

#endif // LOGANALYSER_H_
