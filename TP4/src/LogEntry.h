/*************************************************************************
 LogEntry  -  description
 -------------------
 début                : 14 nov. 2013
 copyright            : (C) 2013 par mnimierdav
 *************************************************************************/

//---------- Interface de la classe <LogEntry> (fichier LogEntry.h) ------
#if ! defined ( LOGENTRY_H_ )
#define LOGENTRY_H_

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "Date.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <LogEntry>
//
//
//------------------------------------------------------------------------ 

struct LogEntry
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	std::string GetUriExtension ( );
	// Mode d'emploi :
	// Renvoie uniquement l'extension de l'URI (sans le point).
	// Si aucune extension ne peut être extraite, on renvoit la chaîne vide.
	// Contrat :
	// L'URI est renseignée.

//------------------------------------------------------ Attributs publics
	std::string ip;
	std::string logName;
	std::string authLogName;
	Date date;
	std::string method;
	std::string uri;
	std::string protocol;
	int status;
	long size;
	std::string referer;
	std::string userAgent;
//------------------------------------------------- Surcharge d'opérateurs
	// LogEntry & operator = ( const LogEntry & unLogEntry );
	// Mode d'emploi :
	//
	// Contrat :
	//

//-------------------------------------------- Constructeurs - destructeur
	LogEntry ( std::string const & Ip, std::string const & LogName,
			std::string const & AuthLogName, Date const & theDate,
			std::string const & Method, std::string const & Uri,
			std::string const & Protocol, int Status, long Size,
			std::string const & Referer, std::string const & UserAgent );
	// Mode d'emploi :
	//
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

//--------------------------- Autres définitions dépendantes de <LogEntry>

#endif // LOGENTRY_H_
