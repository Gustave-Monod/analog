/*************************************************************************
                           LinkUriReferer  -  description
                             -------------------
    début                : 28 nov. 2013
    copyright            : (C) 2013 par gmonod
*************************************************************************/

//---------- Interface de la classe <LinkUriReferer> (fichier LinkUriReferer.h) ------
#if ! defined ( LINKURIREFERER_H_ )
#define LINKURIREFERER_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <LinkUriReferer>
// Lien entre un URI et un referer pouvant être ajouté dans une collection
// triée selon l'ordre alphabétique de la concaténation entre URI et
// referer (dans cet ordre).
// Note: ici les chaînes représentant l'URI et le referer sont copiées.
// Aucune allocation dynamique.
//------------------------------------------------------------------------ 

struct LinkUriReferer
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

	bool operator < ( LinkUriReferer const & b) const;
	// Mode d'emploi :
	// Dis qui de *this ou de b est le premier dans l'ordre alphabétique
	// de la concaténation entre l'URI et le referer (dans cet ordre)
	// du lien.

//-------------------------------------------- Constructeurs - destructeur

	LinkUriReferer ( std::string const uri, std::string const referer );
    // Mode d'emploi :
    // Construit un lien entre URI et Referer à partir de deux std::string.

	/* pas virtual <=> pas d'allocation dynamique ici */
	~LinkUriReferer ( );
	// Mode d'emploi :
	// Trace la destruction si MAP est définit.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    std::string mUri;
    std::string mReferer;
};

//--------------------------- Autres définitions dépendantes de <LinkUriReferer>

#endif // LINKURIREFERER_H_
