1) Objectif
Ce programme analyse un fichier de log Apache et reconstruit un graphe de parcours :
- les nœuds sont les documents (URL),
- les arcs représentent un passage d’un document référent vers un document cible,
- le poids d’un arc correspond au nombre d’accès observés.

Par défaut (sans option), le programme affiche sur la sortie standard les 10 documents les plus consultés, par ordre décroissant de popularité. 

2) Compilation
Pré-requis :
- g++ avec support C++17
- make

Compilation :
  make

Nettoyage :
  make clean
  make mrproper

Remarque : l’option -std=c++17 est nécessaire (le code utilise des fonctionnalités C++17).

3) Utilisation
Syntaxe :
  ./analog [options] nomfichier.log

Le fichier .log doit être fourni en dernier argument.

Options :
- -g nomfichier.dot
  Génère un fichier GraphViz (.dot) du graphe analysé (nœuds = documents, arcs étiquetés par le nombre de parcours).

- -e
  Exclut tous les documents dont l’extension est de type image, CSS ou JavaScript.

- -t heure
  Ne prend en compte que les hits dans le créneau horaire [heure ; heure+1[.

Exemples :
1) Sans option (Top 10 uniquement) :
   ./analog court.log

2) Exclure les ressources statiques + générer un .dot :
   ./analog -e -g court.dot court.log

3) Filtrer sur une heure + générer un .dot :
   ./analog -t 12 -g court.dot court.log

4) Format des logs (rappel)
Chaque ligne de log contient notamment :
- IP client,
- date/heure,
- requête HTTP (la cible),
- code HTTP,
- quantité de données,
- referer (référent),
- identification du client.

5) Sorties
- Sans -g : affichage console du Top 10 des documents les plus consultés.
- Avec -g : création du fichier .dot demandé, en plus des statistiques affichées.

6) Génération d’une image (GraphViz)
À partir d’un fichier .dot généré, on peut produire une image (ex: PNG) :
  dot -Tpng -o out.png in.dot 

7) Contenu du livrable (rappel)
Le rendu doit contenir :
- code source (.h, .cpp), Makefile,
- arborescence des tests (framework fourni),
- un manuel d’utilisation (ce fichier).