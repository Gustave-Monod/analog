/*************************************************************************
                           GraphGenerator  -  description
                             -------------------
    début                : 28 nov. 2013
    copyright            : (C) 2013 par mnimierdav
*************************************************************************/

//---------- Réalisation de la classe <GraphGenerator> (fichier GraphGenerator.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "GraphGenerator.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type GraphGenerator::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
GraphGenerator::GraphGenerator ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <GraphGenerator>" << endl;
#endif
} //----- Fin de GraphGenerator


GraphGenerator::~GraphGenerator ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <GraphGenerator>" << endl;
#endif
} //----- Fin de ~GraphGenerator


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
