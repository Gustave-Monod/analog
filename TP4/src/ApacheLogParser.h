/*************************************************************************
 ApacheLogParser  -  description
 -------------------
 début                : 14 nov. 2013
 copyright            : (C) 2013 par mnimierdav
 *************************************************************************/

//-- Interface de la classe <ApacheLogParser> (fichier ApacheLogParser.h) -
#if ! defined ( APACHELOGPARSER_H_ )
#define APACHELOGPARSER_H_

//--------------------------------------------------- Interfaces utilisées
#include <istream>
#include <vector>
#include <map>
#include "LogEntry.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
//------------------------------------------------------------------------ 
// Rôle de la classe <ApacheLogParser>
//
//
//------------------------------------------------------------------------ 

class ApacheLogParser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	LogEntry ParseLine ( );
	// Mode d'emploi :
	// Renvoie un LogEntry instancié à partir du flux et suivant les paramètres
	// données lors de la construction.
	// Contrat :
	// Le flux contient toujours au moins une ligne à lire.
	// ATTENTION : ParseLine renvoie une ligne de log même si elle aurait dû
	// être filtrée par une des options. Les options sont ignorées.

	std::vector<LogEntry> ParseToEnd ( );
	// Mode d'emploi :
	// Renvoie la liste de toutes LogEntry restant à lire dans le flux dans
	// l'ordre de lecture.
	// Si le flux ne contient pas de ligne à lire, la liste est vide.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
	ApacheLogParser ( std::istream & inStream, bool excludeResourceFiles =
			false, int hourFilter = -1 );
	// Mode d'emploi :
	// Construction à partir d'un flux d'entrée.
	// Si le paramètre hourFilter est à -1, on l'ignore (i.e. aucun filtrage
	// sur les heures).
	// Contrat :
	// Le flux d'entrée doit être au format d'un log Apache.
	// S'il est renseigné, le paramètre hourFilter doit être au format 24h.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	bool hasValidExtension( LogEntry & logEntry );
	// Mode d'emploi :
	// Compare l'extension de l'URI contenue dans cette LogEntry
	// avec la liste des extensions à exclure (EXCLUDE_LIST).
	// Si l'extension est vide, on considère qu'elle est valide.
//----------------------------------------------------- Attributs protégés
	std::istream &mrInStream;
	bool mExcludeResourceFiles;
	int mHourFilter;

	static const std::vector<std::string> EXCLUDE_LIST;
};

//------------------- Autres définitions dépendantes de <ApacheLogParser>

#endif // APACHELOGPARSER_H_
