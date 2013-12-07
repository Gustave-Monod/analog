//---------- Interface de la classe <GraphGenerator> (fichier GraphGenerator.h) ------
#if ! defined ( GRAPHGENERATOR_H_ )
#define GRAPHGENERATOR_H_

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "LogAnalyser.h"

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
	// TODO : make this method static?
	void GenerateGraphTo ( THitsByLink const & data, std::string const outputPath );
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
	std::string getNodeDeclarationLine( std::string const nodeName );
	std::string getEdgeDeclarationLine( std::string const source,
									    std::string const destination,
									    std::string const label );
//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <GraphGenerator>

#endif // GRAPHGENERATOR_H_
