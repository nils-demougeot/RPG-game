#include "jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu() {
    enCours = true;
    victoires = 0;
    joueur = new Joueur("Heros", 100);

    initialiserCatalogue();
}

Jeu::~Jeu() {
    delete joueur;

    for (Monstre* m : monstres) {
        delete m;
    }

    for (auto const& paire : catalogueActions) {
        delete paire.second;
    }
    catalogueActions.clear();
}

void Jeu::initialiserCatalogue() {
    // Actions positives
    catalogueActions["JOKE"] = new ActionACT("JOKE", "Tu racontes une blague un peu nulle.", 15);
    catalogueActions["COMPLIMENT"] = new ActionACT("COMPLIMENT", "Tu dis au monstre qu'il est effrayant.", 25);
    catalogueActions["DISCUSS"] = new ActionACT("DISCUSS", "Tu parles de la pluie et du beau temps.", 10);
    catalogueActions["OBSERVE"] = new ActionACT("OBSERVE", "Tu observes attentivement ton adversaire.", 5);
    catalogueActions["PET"] = new ActionACT("PET", "Tu tentes de caresser la bete.", 30);
    catalogueActions["OFFER_SNACK"] = new ActionACT("OFFER_SNACK", "Tu lui offres un petit biscuit.", 40);
    catalogueActions["REASON"] = new ActionACT("REASON", "Tu tentes une approche diplomatique.", 20);
    catalogueActions["DANCE"] = new ActionACT("DANCE", "Tu executes une petite danse de la paix.", 10);

    // Actions négatives (exigées par le sujet)
    catalogueActions["INSULT"] = new ActionACT("INSULT", "Tu traites le monstre de sac a puces !", -20);
    catalogueActions["MOCK"] = new ActionACT("MOCK", "Tu te moques ouvertement de sa posture de combat.", -15);
}

void Jeu::demarrerJeu() {
    try {
        chargerItems("items.csv");
        chargerMonstres("monstres.csv");

        cout << "Chargement des donnees reussi !" << endl;

        // --- DEBUT DU TEST ---
        cout << "\n===== TEST VERIFICATION DES MONSTRES =====" << endl;
        for (Monstre* m : monstres) {
            // Assure-toi que afficherMonstre() est bien déclarée comme 'virtual' dans Monstre.h
            m->afficherMonstre(); 
        }
        cout << "==========================================" << endl;
        // --- FIN DU TEST ---

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
        string act1, act2, act3, act4; 

        if (!getline(ss, categorie, ',') ||
            !getline(ss, nom, ',') ||
            !getline(ss, hpStr, ',') ||
            !getline(ss, atkStr, ',') ||
            !getline(ss, defStr, ',') ||
            !getline(ss, mercyStr, ',') ||
            !getline(ss, act1, ',') ||
            !getline(ss, act2, ',') ||
            !getline(ss, act3, ',') ||
            !getline(ss, act4)) {

            if(ligne != "\r" && !ligne.empty()) { 
                cout << "Ligne mal formee ignoree (monstres) : " << ligne << endl;
            }
            continue;
        }

        if (!act4.empty() && act4.back() == '\r') {
            act4.pop_back();
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

        // --- AJOUT DES ACTIONS AU MONSTRE ---
        string actionsLues[4] = {act1, act2, act3, act4};

        for (int i = 0; i < 4; i++) {
            if (actionsLues[i] != "-" && !actionsLues[i].empty()) {
                
                if (catalogueActions.count(actionsLues[i]) > 0) {
                    m->addAction(catalogueActions[actionsLues[i]]);
                } else {
                    cout << "Attention : l'action '" << actionsLues[i] << "' n'existe pas dans le catalogue !" << endl;
                }
            }
        }

        monstres.push_back(m);
    }
}


void Jeu::verifierConditionFin() {}

void Jeu::afficherBestiaire(){
    cout << "--- BESTIAIRE ---" << endl;
    cout << "Aucun monstre vaincu pour le moment." << endl;
}