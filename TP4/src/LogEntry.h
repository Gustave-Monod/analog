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
// Simple structure représentant une ligne d'un fichier de log Apache,
// avec toutes ses propriétés.
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
//-------------------------------------------- Constructeurs - destructeur
	LogEntry ( std::string const & Ip, std::string const & LogName,
			std::string const & AuthLogName, Date const & theDate,
			std::string const & Method, std::string const & Uri,
			std::string const & Protocol, int Status, long Size,
			std::string const & Referer, std::string const & UserAgent );

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées
//----------------------------------------------------- Attributs protégés
};
//--------------------------- Autres définitions dépendantes de <LogEntry>
#endif // LOGENTRY_H_
