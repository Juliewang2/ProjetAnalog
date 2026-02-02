/*************************************************************************
                           Stats  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Stats> (fichier Stats.h) ----------------
#if ! defined ( STATS_H )
#define STATS_H

//--------------------------------------------------- Interfaces utilisées
#include <map>      
#include <string> 
#include "LogStream.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Stats>
//
// Stocke un graphe (cible -> (référent -> nb accès)) et permet :
// - d'ajouter des accès depuis un LogStream,
// - de construire un classement (top10) via un multimap,
// - de générer des identifiants de noeuds et un fichier .dot.
//
//------------------------------------------------------------------------

class Stats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ( ) const;
    // Mode d'emploi :
    // Affiche le contenu de 'graphe' (pour debug/visualisation).
    //
    // Contrat :
    // Ne modifie pas l'objet.

    void AfficherTop10 ( ) const;
    // Mode d'emploi :
    // Affiche les 10 URLs ayant le plus de hits (nécessite CreationMultimap).
    //
    // Contrat :
    // Le multimap 'classement' doit avoir été construit.

    void AjouterNoeud ( const LogStream & oneLog );
    // Mode d'emploi :
    // Incrémente le compteur pour (cible, referer) lu dans oneLog.
    //
    // Contrat :
    // oneLog fournit une cible et un référent valides.

    void CreationMultimap ( );
    // Mode d'emploi :
    // Calcule le total de hits par cible et remplit 'classement'.
    //
    // Contrat :
    // Utilise le contenu courant de 'graphe'.

    void CreationFichierDot ( string & nomFichier );
    // Mode d'emploi :
    // Crée un fichier Graphviz .dot (digraph) à partir de 'graphe'.
    //
    // Contrat :
    // mapID doit être prêt (appeler CreateNoeudID avant).

    void CreateNoeudID ( );
    // Mode d'emploi :
    // Attribue un identifiant unique ("noeudX") à chaque URL rencontrée.
    //
    // Contrat :
    // S'appuie sur 'graphe'.

    map<string, map<string, int>> GetGraphe ( );
    // Mode d'emploi :
    // Renvoie une copie du graphe.
    //
    // Contrat :
    // Aucun.


//------------------------------------------------- Surcharge d'opérateurs
    Stats & operator = ( const Stats & unStats );
    // Mode d'emploi :
    // Copie les attributs de unStats dans *this.
    //
    // Contrat :
    // Gère l'auto-affectation.


//-------------------------------------------- Constructeurs - destructeur
    Stats ( const Stats & unStats );
    // Mode d'emploi (constructeur de copie) :
    // Construit une copie de unStats.
    //
    // Contrat :
    // Aucun.

    Stats ( );
    // Mode d'emploi :
    // Construit un objet Stats vide.
    //
    // Contrat :
    // Aucun.

    virtual ~Stats ( );
    // Mode d'emploi :
    // Détruit l'objet.
    //
    // Contrat :
    // Aucun.


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map<string, map<string, int>> graphe;
    multimap<int, string> classement;
    map<string, string> mapID;

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // STATS_H

