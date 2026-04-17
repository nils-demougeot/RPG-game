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

#include <random>

void Jeu::demarrerCombat() {
    if (monstres.empty()) {
        cout << "Aucun monstre disponible pour combattre !" << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distMonstre(0, monstres.size() - 1);
    
    Monstre* adversaire = monstres[distMonstre(gen)];

    cout << "\nUn " << adversaire->getNom() << " (" << adversaire->getCategorie() << ") sauvage apparait !" << endl;

    bool combatEnCours = true;

    while (combatEnCours) {
        
        cout << "\n=== TON TOUR ===" << endl;
        adversaire->afficherMonstre();
        cout << "\n1. FIGHT\n2. ACT\n3. ITEM\n4. MERCY" << endl;
        cout << "Que fais-tu ? : ";
        
        int choix;
        cin >> choix;

        switch (choix) {
            case 1: {
                uniform_int_distribution<> distDegatsJoueur(0, adversaire->getHpMax());
                int degats = distDegatsJoueur(gen);
                
                cout << "\nTu attaques " << adversaire->getNom() << " !" << endl;
                if (degats == 0) {
                    cout << "Mince, ton attaque rate !" << endl;
                } else {
                    cout << "Tu infliges " << degats << " points de degats." << endl;
                    adversaire->recevoirDegats(degats);
                }
                break;
            }
            case 2: // ACT
                cout << "\n[TODO: Implementer l'utilisation du catalogue d'actions]" << endl;
                break;
            case 3: // ITEM
                cout << "\n[TODO: Implementer l'inventaire]" << endl;
                break;
            case 4: // MERCY
                cout << "\n[TODO: Implementer la condition de fuite pacifique]" << endl;
                break;
            default:
                cout << "Choix invalide, tu perds ton tour !" << endl;
        }

        if (adversaire->estVaincu()) {
            cout << "\nBravo, tu as vaincu " << adversaire->getNom() << " !" << endl;
            victoires++;
            joueur->ajouterMonstreTue();
            combatEnCours = false;
            continue;
        }

        cout << "\n=== TOUR DE " << adversaire->getNom() << " ===" << endl;
        
        uniform_int_distribution<> distDegatsMonstre(0, joueur->getHpMax());
        int degatsMonstre = distDegatsMonstre(gen);

        if (degatsMonstre == 0) {
            cout << adversaire->getNom() << " trebuche et rate son attaque !" << endl;
        } else {
            cout << adversaire->getNom() << " t'attaque et t'inflige " << degatsMonstre << " degats !" << endl;
            joueur->recevoirDegats(degatsMonstre);
        }

        if (joueur->getHpActuel() <= 0) {
            cout << "\nTu as peri au combat... GAME OVER." << endl;
            combatEnCours = false;
            enCours = false;
        }
    }
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