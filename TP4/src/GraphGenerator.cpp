//---------- Réalisation de la classe <GraphGenerator> (fichier GraphGenerator.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;
//------------------------------------------------------ Include personnel
#include "GraphGenerator.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void GraphGenerator::GenerateGraphTo ( THitsByLink const & data, ostream & outputStream )
{
	set<string> existingNodes;
	
	// Début du graphe
	outputStream << "digraph {" << endl;
	
	// Pour chaque couple (URI <- Referer, #hits)
	string currentUri, currentReferer, currentLabel;
	for ( THitsByLink::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		currentUri = it->first.Uri;
		currentReferer = it->first.Referer;
		currentLabel = "";
		if ( it->second > 1 )
		{
			currentLabel = to_string( it->second );
		}
		
		// Si on n'avat pas encore croisé cette URI ou ce referer,
		// on lui crée un noeud
		if ( existingNodes.count( currentUri ) < 1 )
		{
			outputStream << getNodeDeclarationLine( currentUri );
			existingNodes.insert( currentUri );
		}
		if ( existingNodes.count( currentReferer ) < 1 )
		{
			outputStream << getNodeDeclarationLine( currentReferer );
			existingNodes.insert( currentReferer );
		}
		
		// On représente ce lien (arrête entre deux noeuds)
		outputStream << getEdgeDeclarationLine( currentReferer, currentUri, currentLabel );
	}
	// Fin du graphe
	outputStream << "}" << endl;
} //----- Fin de GenerateGraphTo

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
GraphGenerator::GraphGenerator ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <GraphGenerator>" << endl;
#endif
} //----- Fin de GraphGenerator

GraphGenerator::~GraphGenerator ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <GraphGenerator>" << endl;
#endif
} //----- Fin de ~GraphGenerator

//------------------------------------------------------------------ PRIVE
string GraphGenerator::getNodeDeclarationLine( string const nodeName )
{
	stringstream declaration;
	declaration <<  "\"" << nodeName << "\";" << endl;
	return declaration.str();
} //----- Fin de getNodeDeclarationLine

string GraphGenerator::getEdgeDeclarationLine( string const source,
						string const destination, string const label )
{
	stringstream declaration;
	declaration <<  "\"" << source << "\" -> "
				<<  "\"" << destination << "\"";
	if ( label.length() > 0 )
	{
		declaration <<  "[label=\"" << label << "\"]";
	}
	declaration << ";" << endl;
	return declaration.str();
} //----- Fin de getEdgeDeclarationLine
//----------------------------------------------------- Méthodes protégées
