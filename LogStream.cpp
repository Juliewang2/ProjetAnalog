/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogStream> (fichier LogStream.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogStream.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void LogStream::AfficherLigne() const
// Algorithme :
// Afficher les champs déjà extraits (ip, dateHeure, cible, codeHttp, quantDonnee, referat, identiser).
//
{
    cout << "ip:" << ip << endl;
    cout << "dateHeure:" << dateHeure << endl;
    cout << "cible:" << cible << endl;
    cout << "codeHttp:" << codeHttp << endl;
    cout << "quantDonnee:" << quantDonnee << endl;
    cout << "referat:" << referat << endl;
    cout << "identiser:" << identiser << endl;
} //----- Fin de AfficherLigne

string LogStream::GetCible() const
// Algorithme :
// Retourner l'attribut cible.
//
{
    return cible;
} //----- Fin de GetCible


string LogStream::GetReferat() const
// Algorithme :
// Retourner l'attribut referat.
//
{
    return referat;
} //----- Fin de GetReferat


int LogStream::GetTime()
// Algorithme :
// Convertir Timebrut en heure via BonFormeTime et retourner le résultat.
//
{
    return BonFormeTime(Timebrut);
} //----- Fin de GetTime


string LogStream::GetExtention(string cible)
// Algorithme :
// Si la cible est vide, retourner "".
// Chercher le premier '.' dans la chaîne.
// Si trouvé, retourner la sous-chaîne après le '.' ; sinon retourner "".
//
{
    if (cible.empty()) return "";
    size_t pos = cible.find('.');
    if (pos != string::npos) return cible.substr(pos + 1);
    return "";
} //----- Fin de GetExtention


string LogStream::BonFormecible(string Ciblebrut)
// Algorithme :
// Si la chaîne est vide, retourner "".
// Extraire la partie URL d'une requête HTTP du type : "GET /chemin/fichier.html HTTP/1.1"
// - trouver le 1er espace, puis le 2e espace,
// - récupérer la sous-chaîne entre ces deux espaces,
// - retourner uniquement le dernier segment (à partir du dernier '/').
//
{
    if (Ciblebrut.empty()) return "";

    size_t start = Ciblebrut.find(' ');
    if (start == string::npos) return "";

    size_t end = Ciblebrut.find(' ', start + 1);
    if (end == string::npos) end = Ciblebrut.size();

    string url = Ciblebrut.substr(start + 1, end - start - 1);

    size_t lastSlash = url.rfind('/');
    if (lastSlash == string::npos) return url;

    return url.substr(lastSlash);
} //----- Fin de BonFormecible


string LogStream::BonFormereferat(string Referatbrut)
// Algorithme :
// Si la chaîne est vide, retourner "".
// Chercher le dernier '/'.
// Si trouvé, retourner la sous-chaîne à partir de ce '/' (dernier segment), sinon retourner la chaîne entière.
//
{
    if (Referatbrut.empty()) return "";

    size_t pos = Referatbrut.rfind('/');
    if (pos == string::npos) return Referatbrut;

    return Referatbrut.substr(pos);
} //----- Fin de BonFormereferat


int LogStream::BonFormeTime(string Timebrut)
// Algorithme :
// Si la chaîne est vide, retourner 0.
// Rechercher le 1er ':' puis le 2e ':'.
// Extraire la sous-chaîne entre les deux ':' (l'heure) et la convertir en int avec stoi, puis retourner.
// Si le format attendu n'est pas trouvé, retourner 0.
//
{
    if (Timebrut.empty()) return 0;

    size_t pos1 = Timebrut.find(':');
    if (pos1 == string::npos) return 0;

    size_t pos2 = Timebrut.find(':', pos1 + 1);
    if (pos2 != string::npos)
    {
        string bonneheure = Timebrut.substr(pos1 + 1, pos2 - pos1 - 1);
        return stoi(bonneheure); // stoi may throw if non-numeric/out of range
    }
    return 0;
} //----- Fin de BonFormeTime


void LogStream::MiseAjourVector(string Ligne)
// Algorithme :
// Réinitialiser les champs.
// Si Ligne vide, sortir.
// Extraire successivement :
// 1) ip : avant le premier espace.
// 2) date/heure brute : entre '[' et ']' ; calculer heure via BonFormeTime ; stocker dateHeure.
// 3) requête cible : entre le premier paire de guillemets '"' ; normaliser via BonFormecible.
// 4) codeHttp puis quantDonnee : lire deux tokens numériques/chaînes séparés par espaces.
// 5) referer : entre la paire de guillemets suivante ; normaliser via BonFormereferat.
//
{
    ip = Ciblebrut = Referatbrut = dateHeure = cible = codeHttp = quantDonnee = referat = identiser = Extention = "";

    if (Ligne.empty()) return;

    // IP
    size_t pos = Ligne.find(' ');
    if (pos != string::npos)
    {
        ip = Ligne.substr(0, pos);
        Ligne.erase(0, pos + 1);
    }

    // Date/Heure
    size_t pos2 = Ligne.find('[');
    size_t endpos2 = Ligne.find(']');
    if (pos2 != string::npos && endpos2 != string::npos)
    {
        Timebrut = Ligne.substr(pos2 + 1, endpos2 - pos2 - 1);
        heure = BonFormeTime(Timebrut);
        dateHeure = to_string(heure);
        Ligne.erase(0, endpos2 + 1);
    }

    // Cible (requête)
    size_t quote1 = Ligne.find('"');
    size_t quote2 = Ligne.find('"', quote1 + 1);
    if (quote1 != string::npos && quote2 != string::npos)
    {
        Ciblebrut = Ligne.substr(quote1 + 1, quote2 - quote1 - 1);
        cible = BonFormecible(Ciblebrut);
        Ligne.erase(0, quote2 + 1);
    }

    // codeHttp & quantDonnee
    size_t pos4 = Ligne.find_first_not_of(' ');
    if (pos4 != string::npos)
    {
        size_t pos4end = Ligne.find(' ', pos4);
        if (pos4end != string::npos)
        {
            codeHttp = Ligne.substr(pos4, pos4end - pos4);
            Ligne.erase(0, pos4end + 1);

            size_t pos5end = Ligne.find(' ');
            if (pos5end != string::npos)
            {
                quantDonnee = Ligne.substr(0, pos5end);
                Ligne.erase(0, pos5end + 1);
            }
            else
            {
                quantDonnee = Ligne;
                Ligne.clear();
            }
        }
    }

    // Referer
    size_t quote3 = Ligne.find('"');
    size_t quote4 = Ligne.find('"', quote3 + 1);
    if (quote3 != string::npos && quote4 != string::npos)
    {
        Referatbrut = Ligne.substr(quote3 + 1, quote4 - quote3 - 1);
        referat = BonFormereferat(Referatbrut);
        Ligne.erase(0, quote4 + 1);
    }
} //----- Fin de MiseAjourVector

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
LogStream::LogStream ( )
    : heure(0), Ciblebrut(""), Timebrut(""), Referatbrut(""), ip(""), dateHeure(""),
      cible(""), codeHttp(""), quantDonnee(""), referat(""), identiser(""), Extention("")
// Algorithme :
// Initialiser les attributs à des valeurs neutres (0 / chaînes vides).
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogStream>" << endl;
#endif
} //----- Fin de LogStream


LogStream::~LogStream ( )
// Algorithme :
// Détruire l'objet (la libération des attributs est automatique).
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogStream>" << endl;
#endif
} //----- Fin de ~LogStream

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

