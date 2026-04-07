#include "jeu.h"
#include <iostream>

using namespace std;

void afficherMenuPrincipal() {
    cout << "\n===== MENU PRINCIPAL =====" << endl;
    cout << "1. Bestiaire (bitacora de monstres)" << endl;
    cout << "2. Demarrer un combat" << endl;
    cout << "3. Statistiques du personnage" << endl;
    cout << "4. Items" << endl;
    cout << "0. Quitter" << endl;
    cout << "Votre choix : ";
    }

void lancer() {
    int choix;
    do {
        afficherMenuPrincipal();
        cin >> choix;
        switch (choix) {
            case 1:
                cout << "Ouverture du bestiaire..." << endl;
                break;
            case 2:
                cout << "Combat en cours..." << endl;
                break;
            case 3:
                cout << "Affichage des statistiques..." << endl;
                break;
            case 4:
                cout << "Ouverture des items..." << endl;
                break;
            case 0:
                cout << "Fermeture du jeu..." << endl;
                break;
            default:
                cout << "Choix invalide !" << endl;
            }
        } while (choix != 0);
    }

