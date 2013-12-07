//-- Interface de la classe <ApacheLogParser> (fichier ApacheLogParser.h) -
#if ! defined ( APACHELOGPARSER_H_ )
#define APACHELOGPARSER_H_

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "LogEntry.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
//------------------------------------------------------------------------ 
// Rôle de la classe <ApacheLogParser>
// Lit le flux d'entrée passé en paramètre et en extrait les informations
// pour les mettre dans une LogEntry.
// Note : pas d'allocation dynamique.
//------------------------------------------------------------------------ 

class ApacheLogParser
{
//----------------------------------------------------------------- PUBLIC

public:
//--------------------------------------------------- Constantes de classe
//----------------------------------------------------- Méthodes publiques

	bool HasMoreToParse ( );
	// Mode d'emploi :
	// Indique s'il reste encore quelque chose à parser dans le flux.

	LogEntry ParseLine ( );
	// Mode d'emploi :
	// Renvoie un LogEntry instancié à partir du flux et suivant les paramètres
	// données lors de la construction.
	// Contrat :
	// Le flux contient toujours au moins une ligne à lire.
	// ATTENTION : ParseLine renvoie une ligne de log même si elle aurait dû
	// être filtrée par une des options. Les options sont ignorées.

	// std::vector<LogEntry> ParseToEnd ( );
	// Mode d'emploi :
	// Renvoie la liste de toutes LogEntry restant à lire dans le flux dans
	// l'ordre de lecture.
	// Si le flux ne contient pas de ligne à lire, la liste est vide.

	// Paramétrage de ApacheLogParser
	void SetRootUrl ( std::string const rootUrl );
	void SetStripGetParameters ( bool stripGetParameters );
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

	ApacheLogParser ( std::istream & inStream );
	// Mode d'emploi :
	// Construction à partir d'un flux d'entrée.
	// Si le paramètre hourFilter est à -1, on l'ignore (i.e. aucun filtrage
	// sur les heures).
	// Contrat :
	// Le flux d'entrée doit être au format d'un log Apache.
	// S'il est renseigné, le paramètre hourFilter doit être au format 24h.

	// Pas virtual <=> pas d'allocation dynamique ici
	~ApacheLogParser ( );
	// Mode d'emploi :
	// Trace la destruction si MAP est définit.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	std::string stripRootUrl ( std::string const url );
	// Mode d'emploi :
	// Si mRootUrl n'est pas vide, on renvoie l'URL débarassée de ce préfixe.
	// Exemple : "http://intranet-if.insa-lyon.fr/temps/5IF40.html"
	// devient   "/temps/5IF40.html"
	std::string stripGetParameters ( std::string const uri );
	// Mode d'emploi :
	// Renvoie l'URI débarassée de ses paramètes GET.
	// Exemple : "http://www.google.fr/?q=42"
	// devient   "http://www.google.fr/"
	std::string stripIndexFilename ( std::string const uri );
	// Mode d'emploi :
	// Si l'URI donnée contient "index.html" ou "index.php",
	// on renvoie la version épurée. Cependant, on fait attention à ne pas
	// supprimer des paramètres GET éventuels si on ne nous l'a pas demandé.
	
//----------------------------------------------------- Attributs protégés
	std::istream &mrInStream;
	
	// Indique si l'on doit supprimer tous les paramètres GET des URIs
	bool mStripGetParameters;
	// Permet de considérer que /page.html est la même que mRootUrl + "page.html"
	std::string mRootUrl;
};

//------------------- Autres définitions dépendantes de <ApacheLogParser>

#endif // APACHELOGPARSER_H_
