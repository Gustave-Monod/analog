/*************************************************************************
 LogAnalyser  -  description
 -------------------
 début                : 18 nov. 2013
 copyright            : (C) 2013 par gmonod
 *************************************************************************/

//---------- Réalisation de la classe <LogAnalyser> (fichier LogAnalyser.cpp) -------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "LogAnalyser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type LogAnalyser::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
LogAnalyser::LogAnalyser ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <LogAnalyser>" << endl;
#endif
} //----- Fin de LogAnalyser

LogAnalyser::~LogAnalyser ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <LogAnalyser>" << endl;
#endif
} //----- Fin de ~LogAnalyser

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void LogAnalyser::addHit ( LogEntry & e )
{
	// On cherche le couple uri <- referer
	THitsByLink::iterator it = mHits.find(
			make_pair( e.uri, e.referer ) );
	// S'il n'existe pas, on l'insère
	if ( it == mHits.end( ) )
	{
		mHits.insert( make_pair( make_pair( e.uri, e.referer ), 1u ) );
	}
	// Sinon, on incrémente le nombre de hits
	else
	{
		++(it->second);
	}
}
