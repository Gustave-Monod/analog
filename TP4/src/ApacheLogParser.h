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

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

	// TODO: add root argument to change the parsing:
	// http://intranet-if.com/ => /
	ApacheLogParser ( std::istream & inStream );
	// Mode d'emploi :
	// Construction à partir d'un flux d'entrée.
	// Si le paramètre hourFilter est à -1, on l'ignore (i.e. aucun filtrage
	// sur les heures).
	// Contrat :
	// Le flux d'entrée doit être au format d'un log Apache.
	// S'il est renseigné, le paramètre hourFilter doit être au format 24h.

	/* pas virtual <=> pas d'allocation dynamique ici */
	~ApacheLogParser ( );
	// Mode d'emploi :
	// Trace la destruction si MAP est définit.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	std::istream &mrInStream;
};

//------------------- Autres définitions dépendantes de <ApacheLogParser>

#endif // APACHELOGPARSER_H_
