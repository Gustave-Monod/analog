#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "unistd.h"

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
	char const * OPTIONS = "hxag:l:t:n:";
	
	string pathToLogFile = "";
	bool showHelp = false;
	string graphOutputPath = "";
	bool excludeResourceFiles = false;
	int minimumRefererHits = -1;
	int hourFilter = -1;
	int topHitsSizeLimit = -1;
	bool showAll = false;
	
	bool argumentsNotValid = false;
	// Pas assez d'arguments passés
	argumentsNotValid = argumentsNotValid || ( argc < 2 );
	
	// On parse les arguments passés
	int thisOption;
	string thisArgument;
	stringstream ss;
	bool argumentIsNumber;
	int numberHolder;
	while ( !argumentsNotValid && (thisOption = getopt( argc, argv, OPTIONS )) != -1 )
	{
		thisArgument = "";
		argumentIsNumber = false;
		if ( optarg != NULL )
		{
			thisArgument = string( optarg );
			ss.clear();
			ss << thisArgument;
			// On essaie de parser un nombre
			if ( ss >> numberHolder )
			{
				argumentIsNumber = true;
			}
			// On vérifie maintenant que les arguments sont du bon type en fonction de l'option
			switch ( thisOption )
			{
				// Options nécessitant un nombre en argument
				case 'l':
				case 't':
				case 'n':
					argumentsNotValid = argumentsNotValid || !argumentIsNumber;
					break;
				// Options nécessitant un nom de fichier de sortie
				case 'g':
					argumentsNotValid = argumentsNotValid || thisArgument[0] == '-';
				break;
			}
		}
		
		// Après s'être assuré que l'éventuel argument soit valide, on l'assigne à la bonne variable
		if ( !argumentsNotValid )
		{
			switch ( thisOption )
			{
				// Option illégalle
				case '?':
					argumentsNotValid = true;
					break;
				case 'h':
					showHelp = true;
					break;
					
				// Options nécessitant un nombre en argument
				case 'l':
					minimumRefererHits = numberHolder;
					break;
				case 't':
					hourFilter = numberHolder;
					break;
				case 'n':
					topHitsSizeLimit = numberHolder;
					break;
				// Options nécessitant un nom de fichier de sortie
				case 'g':
					graphOutputPath = thisArgument;
					break;
				// Autres options
				case 'x':
					excludeResourceFiles = true;
					break;
				case 'a':
					showAll = true;
					break;
				default:
					break;
			}
		}
		
//		cout << "Option : " << (char)thisOption;
//		if ( thisArgument.length() > 0 )
//			cout << " = " << thisArgument;
//		cout << endl;
	}
	
	if ( showHelp )
	{
		showUsage ( argv[0] );
		return SUCCESS;
	}
	// À part pour -h, on a besoin du nom du fichier de log
	if ( optind < argc )
	{
		pathToLogFile = argv[optind];
	}
	else
	{
		argumentsNotValid = true;
	}
	
	if ( argumentsNotValid )
	{
		showUsage ( argv[0] );
		return ERR_ARGS;
	}
	
	
    ifstream inStream( pathToLogFile );
	if ( !inStream )
	{
		cerr << "Impossible de lire le fichier de log " << pathToLogFile << endl;
		return ERR_READ;
	}
	// On instancie et configure le LogAnalyser avec les options passées
	LogAnalyser analyser( inStream );
	analyser.SetExcludeResourceFiles( excludeResourceFiles );
	analyser.SetMinimumRefererHits( minimumRefererHits );
	analyser.SetHourFilter( hourFilter );
	analyser.SetTopSizeLimit( topHitsSizeLimit );
	
	TPriorityQueue & topN = analyser.Analyse();
	THitsByLink & data = analyser.getData();
	
	// Test : afficher le nombre total de hits comptabilisés
	long totalHits = 0;
	for ( THitsByLink::iterator it = data.begin(); it != data.end(); ++it )
	{
		totalHits += it->second;
	}
    cout << totalHits << " hits comptés";
	if ( minimumRefererHits > -1 )
		cout << " (attention, -l est activé avec minimumRefererHits = " << minimumRefererHits << ")";
	cout << endl;
	// Test : afficher le nombre total de hits comptabilisés dans le top
	totalHits = 0;
	while ( !topN.empty() )
	{
		totalHits += topN.top().second;
		topN.pop();
	}
    cout << totalHits << " hits comptés dans la file" << endl;
	
	// TODO : affichage du top N (ou top tout avec l'option -a)
	
	// Génération du graphe représentant les parcours (si demandé)
	if ( graphOutputPath.length() > 0 )
	{
		GraphGenerator generator;
		// TODO : remplacer le path par un ofstream
		generator.GenerateGraphTo( data, graphOutputPath );
		cout << "Dot-file generated" << endl;
	}
	
	return SUCCESS;
}
