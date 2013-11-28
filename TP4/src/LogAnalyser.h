/*************************************************************************
                           LogAnalyser  -  description
                             -------------------
    début                : 18 nov. 2013
    copyright            : (C) 2013 par gmonod
*************************************************************************/

//---------- Interface de la classe <LogAnalyser> (fichier LogAnalyser.h) ------
#if ! defined ( LOGANALYSER_H_ )
#define LOGANALYSER_H_

//--------------------------------------------------- Interfaces utilisées
#include <map>

#include "LogEntry.h"
#include "LinkUriReferer.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
// DONE : définir notre propre structure de donnée, dans laquelle on redéfinit
// l'opérateur < (pour le tri à l'insertion dans la map)
// typedef std::pair<std::string, std::string> TLinkUriReferer;
typedef std::map<LinkUriReferer, unsigned int> THitsByLink;

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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
    LogAnalyser ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    /* pas virtual <=> pas d'allocation dynamique ici */
    ~LogAnalyser ( );
    // Mode d'emploi :
    // Trace la destruction.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    void addHit ( LogEntry & e );
    	// Mode d'emploi :
    	// Ajoute un (1) au nombre de hits pour un lien donné.
    	// Si la LogEntry n'a pas encore été lue, on l'insère avec
    	// un (1) seul hit.
//----------------------------------------------------- Attributs protégés
	THitsByLink mHits;
};

//--------------------------- Autres définitions dépendantes de <LogAnalyser>

#endif // LOGANALYSER_H_
