#include <iostream>
#include <fstream>
#include <sstream>

#include "LogAnalyser.h"
#include "GraphGenerator.h"

using namespace std;

enum TReturnCode
{
	SUCCESS, ERR_ARGS, ERR_READ, ERR_FORMAT, ERR_WRITE
};

void afficherTest ( int numero, bool resultat )
{
	cout << "Test #" << numero << ' ' << ( resultat ? "OK" : "KO" ) << endl;
}

// TODO : migrer ces tests dans le 'framework' de test fourni
void testUnitaireLogParser ( )
{

	cout << "=== Tests de Apache LogParser" << endl;

	// On construit notre jeu de test
	stringstream inStream;
	inStream << endl
			<< "192.168.0.0 - - [08/Sep/2012:11:16:02 +0200] \"GET /temps/4IF16.html HTTP/1.1\" 200 12106 \"http://intranet-if.insa-lyon.fr/temps/4IF15.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\""
			<< endl << '\r' << '\n'
			<< "192.168.0.0 - - [23/Apr/2012:13:06:05 -0600] \"GET /temps/4IF17.html HTTP/1.1\" 200 5189 \"http://intranet-if.insa-lyon.fr/temps/4IF16.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\""
			<< '\r' << '\n' << endl
			<< "192.168.0.6 - - [08/Sep/2012:01:19:56 +0200] \"GET /BonjreuoRKL/fdjKL.css/QF.DCOIfd.css HTTP/1.1\" 200 216 \"-\" \"Mozilla/5.0 (Linux; U; Android 4.0.4; fr-fr; Galaxy Nexus Build/IMM76L; CyanogenMod-9.0.0) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30\""
			<< endl
			<< "192.168.0.0 - - [10/Oct/2013:23:56:06 +0200] \"GET /temps/4IF19.html HTTP/1.1\" 200 5179 \"http://intranet-if.insa-lyon.fr/temps/4IF18.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\""
			<< '\r'
			<< "192.168.0.6 - - [08/Sep/2012:01:19:56 +0200] \"GET / HTTP/1.1\" 200 216 \"-\" \"Mozilla/5.0 (Linux; U; Android 4.0.4; fr-fr; Galaxy Nexus Build/IMM76L; CyanogenMod-9.0.0) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30\"";

	// On lance les tests à partir du jeu de test
	ApacheLogParser a( inStream );

	// Première ligne de log
	LogEntry e = a.ParseLine( );
	afficherTest( 0, e.uri == "/temps/4IF16.html" );
	afficherTest( 1, e.date.hour == 11 );
	afficherTest( 2,
			e.referer == "http://intranet-if.insa-lyon.fr/temps/4IF15.html" );

	// Deuxième ligne de log
	e = a.ParseLine( );
	afficherTest( 3, e.uri == "/temps/4IF17.html" );
	afficherTest( 4, e.date.hour == 13 );
	afficherTest( 5,
			e.referer == "http://intranet-if.insa-lyon.fr/temps/4IF16.html" );

	// Le reste du document
//	vector<LogEntry> theRest = a.ParseToEnd( );
//	afficherTest( 6, theRest.size( ) == 3 );
//	// Le dernier de ce vecteur (= le dernier du document)
//	LogEntry & e2 = theRest[theRest.size( ) - 1];
//	afficherTest( 7, e2.uri == "/" );
//	afficherTest( 8, e2.date.hour == 1 );
//	afficherTest( 9, e2.referer == "-" );
//
//	e2 = theRest[0];
//	afficherTest( 10, e2.GetUriExtension( ) == "css" );

	cout << endl;
}

void showUsage ( char *pszPath )
{
	cerr << "Usage :" << endl << pszPath << " [-hxa] fichierL" << endl
		 << pszPath << " [-g fichierG] fichierL" << endl << pszPath
		 << " [-l #] fichierL" << endl << pszPath << " [-t #] fichierL"
		 << endl << pszPath << " [-n #] fichierL" << endl;
}

int main ( int argc, char *argv[] )
{
/*
	string const theOptions[] = {
		"-h",
		// Toutes les options suivantes nécessitent un nom de fichier
		// en entrée (fichierL)
		"-x", "-a",
		"-g", // Nécessite un nom de fichier en sortie (fichierG)
		"-l", "-t", "-n" // Nécessite un nombre (
		// TODO : rajouter une option permettant de virer les variables
		// GET des URI et Referers
	};
	const vector<string> OPTIONS( theOptions, theOptions + 7 );

	if ( argc < 2 )
	{
		showUsage ( argv[0] );
		return ERR_ARGS;
	}

	string firstArgument ( argv[1] );

	bool badCombination = firstArgument == "-h" && argc > 2;
	// TODO : vérifier que tous les arguments passés font partie des options
	if ( badCombination )
	{
		showUsage ( argv[0] );
		return ERR_ARGS;
	}
*/
	// On ouvre le fichier et on appelle le parser avec les bons arguments
	// ifstream inStream( "/shares/binomes/B3109/oo/analog/small.log" );
    ifstream inStream( "/Users/Merlin/Documents/Cours/3IF/OO/analog/small.log" );
	// Par défaut, pas de filtrage d'extension ni d'heure
	
	LogAnalyser analyser( inStream, false, -1 );
	// TODO : configurer l'analyser selon les options
	
	
	TPriorityQueue & topN = analyser.Analyse();
	THitsByLink & data = analyser.getData();
	
	// Test : afficher le nombre total de hits comptabilisés
	long totalHits = 0;
	for ( THitsByLink::iterator it = data.begin(); it != data.end(); ++it )
	{
		totalHits += it->second;
	}
    cout << totalHits << " hits comptés (attention, -l peut être activé)." << endl;
	// Test : afficher le nombre total de hits comptabilisés dans le top
	totalHits = 0;
	while ( !topN.empty() )
	{
		totalHits += topN.top().second;
		topN.pop();
	}
    cout << totalHits << " hits comptés dans la file." << endl;

	
	// On s'occuppe maintenant de générer le graphe représentant les parcours
	GraphGenerator generator;
	// TODO : prendre en compte le nom du fichier de sortie donné en paramètre
	generator.GenerateGraphTo( data, "out.dot" );
	
	return SUCCESS;
}
