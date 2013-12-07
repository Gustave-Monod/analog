//---------- Interface de la classe <Date> (fichier Date.h) ------
#if ! defined ( DATE_H_ )
#define DATE_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Date>
//
//
//------------------------------------------------------------------------ 

struct Date
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------ Attributs publics
	int day;
	std::string month; // Trois premières lettres (en anglais)
	int year;
	int hour; // Au format 24h
	int minutes;
	int seconds;
	std::string utcOffset; // Par exemple : "+0100"

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    Date ( std::string const & dateString );
    // Mode d'emploi :
    // Construit un objet date.
    // Contrat :
    // La chaine doit être formatée comme suit :
    // 08/Sep/2012:11:15:00 +0200

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <Date>

#endif // DATE_H_
