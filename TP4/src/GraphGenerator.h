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
	void GenerateGraphTo ( THitsByLink const & data, std::ostream & outputStream );
    // Mode d'emploi :
    //
    // Contrat :
    // Le flux outputStream est ouvert et prêt à recevoir.
//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
    GraphGenerator ( );
    virtual ~GraphGenerator ( );
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	std::string getNodeDeclarationLine( std::string const nodeName );
	// Mode d'emploi :
	// Renvoie une déclaration de noeud en syntaxe GraphViz
	std::string getEdgeDeclarationLine( std::string const source,
									    std::string const destination,
									    std::string const label );
	// Mode d'emploi :
	// Renvoie une déclaration d'arête en syntaxe GraphViz
//----------------------------------------------------- Attributs protégés
};
//--------------------------- Autres définitions dépendantes de <GraphGenerator>
#endif // GRAPHGENERATOR_H_
