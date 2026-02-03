/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogStream> (fichier LogStream.h) ----------------
#if ! defined ( LOGSTREAM_H )
#define LOGSTREAM_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <fstream>   
#include <iostream>

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogStream>
//
// Spécialise un flux d'entrée fichier (ifstream) pour lire/extraire les
// informations d'une ligne de log : cible, referer, date/heure, etc.
// Fournit des accesseurs (Get...) et des méthodes de mise en forme (BonForme...).
//
//------------------------------------------------------------------------

class LogStream : public ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AfficherLigne ( ) const;
    // Mode d'emploi :
    // Affiche (ou aide à afficher) les informations extraites de la ligne courante.
    //
    // Contrat :
    // Ne modifie pas l'objet.

    string GetCible ( ) const;
    // Mode d'emploi :
    // Renvoie la cible (URL) mise en forme.
    //
    // Contrat :
    // cible doit avoir été initialisée (par MiseAjourVector ou parsing équivalent).

    string GetReferat ( ) const;
    // Mode d'emploi :
    // Renvoie le referer mis en forme.
    //
    // Contrat :
    // referat doit avoir été initialisé.

    int GetTime ( );
    // Mode d'emploi :
    // Renvoie l'heure (ou un entier représentant le temps) extrait.
    //
    // Contrat :
    // heure doit avoir été calculée/initialisée.

    string GetExtention ( string cible );
    // Mode d'emploi :
    // Renvoie l'extension (ex: html, css, js, png...) extraite de la cible fournie.
    //
    // Contrat :
    // cible non vide.

    string BonFormecible ( string cible );
    // Mode d'emploi :
    // Normalise/filtre la cible brute (suppression paramètres, normalisation, etc.).
    //
    // Contrat :
    // cible non vide.

    string BonFormereferat ( string referat );
    // Mode d'emploi :
    // Normalise/filtre le referer brut.
    //
    // Contrat :
    // referat peut être vide selon les logs, sinon chaîne valide.

    int BonFormeTime ( string dateHeure );
    // Mode d'emploi :
    // Convertit une date/heure brute en entier (ex: heure).
    //
    // Contrat :
    // dateHeure au format attendu par le parsing.

    void MiseAjourVector ( string unLigne );
    // Mode d'emploi :
    // Analyse une ligne de log et met à jour les attributs (ip, dateHeure, cible...).
    //
    // Contrat :
    // unLigne respecte le format du fichier log.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    LogStream ( );
    // Mode d'emploi :
    // Construit un LogStream (flux non forcément ouvert).
    //
    // Contrat :
    // Aucun.

    virtual ~LogStream ( );
    // Mode d'emploi :
    // Détruit l'objet.
    //
    // Contrat :
    // Aucun.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int heure;
    string Ciblebrut;
    string Timebrut;
    string Referatbrut;
    string ip;
    string dateHeure;
    string cible;
    string codeHttp;
    string quantDonnee;
    string referat;
    string identiser;
    string Extention;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // LOGSTREAM.H

