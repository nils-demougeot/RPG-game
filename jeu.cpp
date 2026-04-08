#include "jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu() {
    enCours = true;
    victoires = 0;

    joueur = new Joueur("Heros", 100);
}

Jeu::~Jeu() {
    delete joueur;

    for (Monstre* m : monstres) {
        delete m;
    }
}

void Jeu::demarrerJeu() {
    try {
        chargerItems("items.csv");
        chargerMonstres("monstres.csv");

        cout << "Chargement des donnees reussi !" << endl;

        int choix;
        do {
            afficherMenuPrincipal();
            cin >> choix;

            switch (choix) {
                case 1:
                    cout << "Ouverture du bestiaire..." << endl;
                    afficherBestiaire();
                    break;

                case 2:
                    demarrerCombat();
                    break;

                case 3:
                    cout << "Statistiques du joueur..." << endl;
                    joueur->afficherStatistiques();
                    break;

                case 4:
                    cout << "Items du joueur..." << endl;
                    // joueur->afficherInventaire();
                    break;

                case 0:
                    enCours = false;
                    cout << "Fermeture du jeu..." << endl;
                    break;

                default:
                    cout << "Choix invalide !" << endl;
            }

            verifierConditionFin();

        } while (enCours);

    } catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
        cout << "Arret du jeu." << endl;
    }
}

void Jeu::afficherMenuPrincipal() {
    cout << "\n===== MENU PRINCIPAL =====" << endl;
    cout << "1. Bestiaire" << endl;
    cout << "2. Demarrer un combat" << endl;
    cout << "3. Statistiques du personnage" << endl;
    cout << "4. Items" << endl;
    cout << "0. Quitter" << endl;
    cout << "Votre choix : ";
}

void Jeu::demarrerCombat() {
    cout << "Fonction a ecrire" << endl;
}

void Jeu::chargerItems(string nomFichier) {
    ifstream file(nomFichier);

    if (!file.is_open()) {
        throw std::runtime_error("Fichier items introuvable : " + nomFichier);
    }

    string ligne;
    int ligneNum = 0;

    while (getline(file, ligne)) {
        ligneNum++;
        if (ligne.empty()) continue;

        stringstream ss(ligne);

        string nom, type, valeurStr, quantiteStr;

        if (!getline(ss, nom, ',') ||
            !getline(ss, type, ',') ||
            !getline(ss, valeurStr, ',') ||
            !getline(ss, quantiteStr)) {
            std::cout << "Ligne mal formee (items) ignoree à la ligne " << ligneNum << " : " << ligne << std::endl;
            continue;
        }

        try {
            int valeurSoin = std::stoi(valeurStr);
            int quantite = std::stoi(quantiteStr);

            Item* item = new Item(nom, type, valeurSoin, quantite);

            std::cout << "[ITEM] " << nom << " | type: " << type
                      << " | valeur: " << valeurSoin
                      << " | quantite: " << quantite << std::endl;

        } catch (const std::invalid_argument& e) {
            std::cout << "Valeur invalide (items) ignoree à la ligne " << ligneNum << " : " << ligne << std::endl;
            continue;
        }
    }

    file.close();
}

void Jeu::chargerMonstres(string nomFichier) {
    ifstream file(nomFichier);

    if (!file) {
        throw runtime_error("Fichier monstres introuvable : " + nomFichier);
    }

    string ligne;

    while (getline(file, ligne)) {
        stringstream ss(ligne);

        string nom, categorie;
        string hpStr, atkStr, defStr, mercyStr;

        if (!getline(ss, nom, ',') ||
            !getline(ss, categorie, ',') ||
            !getline(ss, hpStr, ',') ||
            !getline(ss, atkStr, ',') ||
            !getline(ss, defStr, ',') ||
            !getline(ss, mercyStr)) {

            cout << "Ligne mal formee ignoree : " << ligne << endl;
            continue;
        }

        int hp = stoi(hpStr);
        int attaque = stoi(atkStr);
        int defense = stoi(defStr);
        int mercy = stoi(mercyStr);

        Monstre* m = nullptr;

        if (categorie == "NORMAL") {
            m = new MonstreNormal(nom, hp, attaque, defense, mercy);
        }
        else if (categorie == "MINIBOSS") {
            m = new MonstreMiniBoss(nom, hp, attaque, defense, mercy);
        }
        else if (categorie == "BOSS") {
            m = new MonstreBoss(nom, hp, attaque, defense, mercy);
        }
        else {
            cout << "Type inconnu ignore : " << categorie << endl;
            continue;
        }

        monstres.push_back(m);

        cout << "[MONSTRE] " << nom << " (" << categorie << ")" << endl;
    }
}


void Jeu::verifierConditionFin() {}

void Jeu::afficherBestiaire(){
    cout << "--- BESTIAIRE ---" << endl;
    cout << "Aucun monstre vaincu pour le moment." << endl;
}