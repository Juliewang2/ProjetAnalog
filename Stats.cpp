/*************************************************************************
                           Stats -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Stats> (fichier Stats.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Stats::Afficher() const
// Algorithme :
// Parcourir tous les couples (cible -> (ref -> nb_acces)) du graphe.
// Pour chaque cible, afficher la cible puis toutes ses références et compteurs.
//
{
    for (const auto & [cible, ref_pair] : graphe)
    {
        cout << "key:" << cible << "\n" << endl;
        for (const auto & [ref, nb_acces] : ref_pair)
        {
            cout << "reference:" << ref;
            cout << "nombre d'acces:" << nb_acces << endl;
        }
    }
} //----- Fin de Afficher

void Stats::AjouterNoeud(const LogStream & Log)
// Algorithme :
// Récupérer la cible et le référent depuis Log.
// Accéder à graphe[cible][referent] et incrémenter (création implicite si absent).
//
{   string cible=Log.GetCible();
    string referent=Log.GetReferat();
    if (cible.empty())return;
    if (referent.empty())referent="-";
    graphe[cible][referent]++;
} //----- Fin de AjouterNoeud

void Stats::CreationMultimap()
// Algorithme :
// Vider 'classement'.
// Calculer pour chaque cible la somme des nb_acces sur toutes ses références.
// Insérer (totalHits, cible) dans 'classement' (multimap triée par total).
//
{
    classement.clear();

    map<string, int> TotalHits;
    for (const auto & [cible, ref_pair] : graphe)
    {
        int sum = 0;
        for (const auto & [ref, nb_acces] : ref_pair)
        {
            sum += nb_acces;
        }
        TotalHits[cible] = sum;
    }

    for (const auto & [cible, total] : TotalHits)
    {
        classement.insert({ total, cible });
    }
} //----- Fin de CreationMultimap

map<string, map<string, int>> Stats::GetGraphe()
// Algorithme :
// Retourner une copie de l'attribut 'graphe'.
//
{
    return graphe;
} //----- Fin de GetGraphe

void Stats::AfficherTop10() const
// Algorithme :
// Parcourir 'classement' en ordre décroissant (reverse iterator).
// Afficher au plus 10 éléments : hits (clé) et url (valeur).
//
{
    int rang = 0;
    int prevHits = -1;

    for (auto it = classement.rbegin(); it != classement.rend(); ++it)
    {
        if (it->first != prevHits)
        {
            rang++;
            prevHits = it->first;
        }

        if (rang > 10)
            break;

        cout << "Hits: " << it->first
             << " | URL: " << it->second << endl;
    }
} //----- Fin de AfficherTop10

void Stats::CreateNoeudID()
// Algorithme :
// Initialiser un compteur id à 0.
// Parcourir toutes les URLs du graphe (chaque cible + chaque ref).
// Pour chaque URL, si absente de mapID, lui associer "noeud<id>" puis incrémenter id.
//
{
    int id = 0;
    for (auto & [cible, ref] : graphe)
    {
        if (mapID.find(cible) == mapID.end())
        {
            mapID[cible] = "noeud" + to_string(id++);
        }

        for (auto & [refNode, nb_access] : ref)
        {
            (void) nb_access; // nb_access not used for ID creation
            if (mapID.find(refNode) == mapID.end())
            {
                mapID[refNode] = "noeud" + to_string(id++);
            }
        }
    }
} //----- Fin de CreationNoeudID

void Stats::CreationFichierDot(string & nomFichier)
// Algorithme :
// Ouvrir un fichier "./" + nomFichier en écriture.
// Si l'ouverture réussit :
// - écrire l'en-tête "digraph{"
// - écrire toutes les déclarations de noeuds (id + label=url)
// - écrire tous les arcs (idCible -> idRef) avec label = nb_acces
// - fermer la définition avec "}"
//
{
    ofstream fic("./" + nomFichier);
    if (fic)
    {
        fic << "digraph{" << "\n";
        for (const auto & [cible, ref_pair] : graphe)
        {
            (void) ref_pair; // only need cible here
            fic << mapID[cible] << "[label=" << cible << "];" << endl;
        }

        for (const auto & [cible, ref_pair] : graphe)
        {
            for (const auto & [ref, nb_acces] : ref_pair)
            {
                fic << mapID[cible] << "->" << mapID[ref]
                    << "[label=" << to_string(nb_acces) << "];" << endl;
            }
        }
        fic << "}" << endl;
    }
} //----- Fin de CreationFichierDot

//------------------------------------------------- Surcharge d'opérateurs
Stats & Stats::operator = ( const Stats & unStats )
// Algorithme :
// Si unStats n'est pas *this : copier chaque attribut (graphe, classement, mapID).
// Retourner *this.
//
{
    if (this != &unStats)
    {
        graphe = unStats.graphe;
        classement = unStats.classement;
        mapID = unStats.mapID;
    }
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Stats::Stats ( const Stats & unStats ) : graphe(unStats.graphe), classement(unStats.classement), mapID(unStats.mapID)
// Algorithme : 
// Initialiser chaque attribut en le copiant depuis unStats (liste d'initialisation).
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Stats>" << endl;
#endif
} //----- Fin de Stats (constructeur de copie)


Stats::Stats ( )
// Algorithme :
// Construire un objet vide (les conteneurs membres sont initialisés vides).
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Stats>" << endl;
#endif
} //----- Fin de Stats

Stats::~Stats ( )
// Algorithme :
// Détruire l'objet (la libération des conteneurs membres est automatique).
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin de ~Stats

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

