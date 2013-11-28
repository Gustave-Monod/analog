/*************************************************************************
                           GraphGenerator  -  description
                             -------------------
    début                : 28 nov. 2013
    copyright            : (C) 2013 par mnimierdav
*************************************************************************/

//---------- Interface de la classe <GraphGenerator> (fichier GraphGenerator.h) ------
#if ! defined ( GRAPHGENERATOR_H_ )
#define GRAPHGENERATOR_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <GraphGenerator>
// Générer un fichier .dot (syntaxe GraphViz) représentant le graphe de
// parcours tel que donné par les logs.
//------------------------------------------------------------------------ 

class GraphGenerator
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
    GraphGenerator ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~GraphGenerator ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <GraphGenerator>

#endif // GRAPHGENERATOR_H_
