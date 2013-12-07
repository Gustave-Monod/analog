#if ! defined ( LOGANALYSERTYPES_H_ )
#define LOGANALYSERTYPES_H_

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <queue>

#include "LinkUriReferer.h"

//------------------------------------------------------------------ Types
typedef std::map<LinkUriReferer, unsigned int> THitsByLink;

typedef std::pair<std::string, int> TUriAndRefererHits;

// Pour trier la file à priorité, on définit un foncteur
class UriAndHitsGreater
{
public:
	// On trie le plus souvent en ordre inverse pour pouvoir enlever
	// facilement les éléments avec le nombre de hits le plus bas
	// (ils se retrouveront naturellement en bout de fil, on pourra les
	// supprimer d'un simple pop)
	UriAndHitsGreater ( const bool descending = false )
	: mDescending( descending )
	{
	}
	
	bool operator () ( const TUriAndRefererHits & rA, const TUriAndRefererHits &rB ) const
	{
		return mDescending ?
		( rA.second > rB.second ) : ( rA.second < rB.second );
	}
protected:
	bool mDescending;
};

// Cette file à priorité contiendra les # URI ayant le plus grand nombre de hits
// (# varie selon les options données par l'utilisateur)
typedef std::priority_queue<TUriAndRefererHits, std::vector<TUriAndRefererHits>,
	UriAndHitsGreater> TPriorityQueue;

#endif // LOGANALYSERTYPES_H_