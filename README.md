analog
======
Analyse le contenu d’un fichier log formaté à la manière de Apache.

# Synopsis

analog -h
analog [-xa]  fichierL
analog [-g fichierG] fichierL
analog [-l #] fichierL
analog [-t #] fichierL
analog [-n #] fichierL

# Description

L’utilitaire analog lit les lignes d’un fichierL log donné formaté à la manière de Apache et affiche des statistiques à leur propos. Il est possible de filtrer les données que l’on veut analyser à l’aide des options.
Sans aucune option, analog affiche les 10 documents les plus sollicités (ou tous pour un fichier avec moins de 10 documents) ainsi que le nombre de hits qu’ils ont chacun généré.

Les options d’utilisation sont les suivantes :

-h
Affiche l’utilisation de analog et ses options sur la sortie standard.

-g fichierG
Génère un fichierG au format GraphViz représentant les entrées du fichierL log. Chaque document est un nœud et les arcs portent le nombre d’entrées empruntant le chemin en question.
Note : affiche "Dot-file generated" si le fichier a bien pu être généré.

-x
Exclue tous les fichiers qui se termine par une extension de type :
image (jpg, jpeg, png, gif, bmp)
code de mise en forme (js, css)
son (mp3, aac, flac, wav, ogg)
vidéo (mp4, mov, m4v, flv, 3gp)
vectoriel (svg)
Non sensible à la casse. Si un fichier n'a pas d'extension, il ne sera pas exclu.

-l #
Filtre tous les documents n’ayant pas au moins un referer faisant # hits à lui tout seul. Dans le graphe (-g) on n’affiche pas les liens de strictement moins de # hits.

-t #
Filtre tous les documents n’ayant pas été écrits à l’heure #, avec # un nombre au format 24h (ex : 1 ou 13).

-n #
Affiche les # documents les plus sollicités (10 par défaut).

-a
Affiche tous les documents présents dans le fichierL.

# Hypothèses

Le fichier de log (fichierL) doit être encodé en us-ascii sans accents et avec un caractère de fin de ligne (EOL) comprenant un '\n'.
Le format des champs doit être celui des fichiers de log Apache (9 champs séparés par des espaces non échappés par des guillemets doubles (").
Les URI ne doivent pas avoir de paramètres de type GET (i.e. /bonjour.php?param=valeur), et doivent finir par une extension (/fic.html, /a.css, etc.) ou pas d'extension du tout (/, /bonjour).
Diagnostique
analog renvoie 0 si tout s’est bien passé, et >0 en cas d’erreur (listés ci-dessous).
Le fichierL n’est pas spécifié ⇒ affiche l’utilisation de analog et ses options sur la sortie d’erreur standard. Code d’erreur ERR_ARGS (1).
Une option autre que -h, -x, ou -a n’est pas suivie de son argument (ou celui-ci est mal formaté) ⇒ affiche l’utilisation de analog et ses options sur la sortie d’erreur standard . Code d’erreur ERR_ARGS (1).
Le fichierL est inaccessible en lecture ⇒ affiche l’utilisation de analog et ses options sur la sortie d’erreur standard. Code d’erreur ERR_READ (2).
Le fichierL est vide ⇒ affiche "Fichier vide" sur la sortie d’erreur standard. Code d’erreur ERR_EMPTY.
Le fichierL est mal formaté (pas toujours détecté) ⇒ affiche "Fichier mal formaté" sur l’erreur standard. Code d’erreur ERR_FORMAT (3).
Le fichierG n’est pas accessible en écriture ⇒ affiche "Impossible de générer fichier GraphViz" sur la sortie d’erreur standard. Code d’erreur ERR_WRITE (4).
