#include <iostream>
#include <fstream>
#include <string>
#include "Stats.h"
#include "LogStream.h"

using namespace std;

int main(int argc, char *argv[])
{
    // --------------------------------------------------------------------
    // Programme "analog" (TP Analyse de logs Apache)
    //
    // Usage : ./analog [options] file.log
    // - Le dernier argument est le fichier de log à analyser.
    // - Sans option : affiche le Top 10 des documents les plus consultés.
    //
    // Options :
    //  -e            : exclut certains fichiers statiques (.css, .js, .jpg, .png)
    //  -t <heure>    : ne considère que les hits dont l'heure == <heure>
    //  -g <fichier>  : génère un fichier Graphviz .dot représentant le graphe
    //
    // Principe :
    // 1) Lire le fichier ligne par ligne.
    // 2) Parser chaque ligne (LogStream) pour extraire cible/référent/heure.
    // 3) Appliquer les filtres (-t, -e).
    // 4) Alimenter Stats (graphe des parcours), puis afficher le Top 10.
    // 5) Si -g, écrire le graphe au format .dot.
    // --------------------------------------------------------------------

    istream *input = &cin;
    ifstream fic;
    if (argc >= 2)
    {
        string dernierArg = argv[argc - 1];
        if (dernierArg[0] != '-')
        {
            fic.open(dernierArg);
            if (!fic)
            {
            cerr << "Erreur d'ouverture de : " << dernierArg << endl;
            return 1;
            }
        input = &fic;
        }
    }


   
    string nomDot = "";
    bool excludeExtension = false;
    int heureFiltre = -1;

    // Lecture des options (tous les arguments sauf le dernier).
    for (int i = 1; i < argc - 1; ++i)
    {
        string opt = argv[i];
        if (opt == "-e")
            excludeExtension = true;
        else if (opt == "-g" && i + 1 < argc - 1)
            nomDot = argv[++i];
        else if (opt == "-t" && i + 1 < argc - 1)
        {
            try
            {
                heureFiltre = stoi(argv[++i]);
            }
            catch (...)
            {
                cerr << "Heure invalide." << endl;
                return 1;
            }
        }
    }

    Stats myStats;
    string Ligne;

    // Traitement des lignes du log.
    while (getline(*input, Ligne))
    {
        if (Ligne.empty())
            continue;

        // Parsing d'une ligne de log (extraction cible/référent/heure, etc.).
        LogStream unLog;
        unLog.MiseAjourVector(Ligne);

        // Filtre horaire (si -t a été fourni).
        if (heureFiltre != -1 && unLog.GetTime() != heureFiltre)
            continue;

        // Filtre extensions (si -e a été fourni).
        if (excludeExtension)
        {
            string url = unLog.GetCible();
            if (url.find(".css") != string::npos || url.find(".js") != string::npos ||
                url.find(".jpg") != string::npos || url.find(".png") != string::npos)
                continue;
        }

        // Ajout de l'accès dans les statistiques (incrémente arc référent -> cible).
        myStats.AjouterNoeud(unLog);
    }

    // Construction du classement et affichage du Top 10.
    myStats.CreationMultimap();
    myStats.AfficherTop10();

    // Génération optionnelle du fichier .dot.
    if (!nomDot.empty())
    {
        myStats.CreateNoeudID();
        myStats.CreationFichierDot(nomDot);
        cout << "Fichier Graph créé : " << nomDot << endl;
    }

    return 0;
}