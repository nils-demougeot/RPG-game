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

    for (Item* item : poolItems) {
        delete item;
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

    // Actions négatives
    catalogueActions["INSULT"] = new ActionACT("INSULT", "Tu traites le monstre de sac a puces !", -20);
    catalogueActions["MOCK"] = new ActionACT("MOCK", "Tu te moques ouvertement de sa posture de combat.", -15);
}

void Jeu::demarrerJeu() {
    try {
        chargerItems("items.csv");
        chargerMonstres("monstres.csv");

        donnerItemsDeDepart();

        cout << "Chargement des donnees reussi !" << endl;

        // --- DEBUT DU TEST AFFICHAGE DES MONSTRES ---
        /*cout << "\n===== TEST VERIFICATION DES MONSTRES =====" << endl;
        for (Monstre* m : monstres) {
            m->afficherMonstre(); 
        }
        cout << "==========================================" << endl;*/
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
                    joueur->afficherInventaire();
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

    cout << "\n==================================================\n" << endl;
}

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

    int numTour = 1;
    bool combatEnCours = true;

    while (combatEnCours) {

        cout << "\n==================================================" << endl;
        cout << ">>>                   TOUR " << numTour << "                   <<<" << endl;
        cout << "\n==================================================\n" << endl;
        
        cout << "[ JOUEUR : " << joueur->getNom() 
             << " | HP : " << joueur->getHpActuel() << " ]" << endl;
             
        cout << "          VS" << endl;
        
        adversaire->afficherMonstre();
        
        cout << "\n+---------------------------------------+" << endl;
        cout << "|              QUE FAIRE ?              |" << endl;
        cout << "+-------------------+-------------------+" << endl;
        cout << "|  [1] FIGHT        |  [2] ACT          |" << endl;
        cout << "|  [3] ITEM         |  [4] MERCY        |" << endl;
        cout << "+-------------------+-------------------+" << endl;
        cout << "|               [0] FUIR                |" << endl;
        cout << "+-------------------+-------------------+" << endl;
        cout << ">> Votre choix : ";
        
        int choix;
        cin >> choix;

        if (choix == 0) {
            cout << "\nTu fuis lachement le combat... L'aventure s'arrete ici !" << endl;
            combatEnCours = false;
            return;
        }

        cout << "\n--------------------------------------------------" << endl;

        switch (choix) {
            case 1: {
                cout << "\nTu attaques " << adversaire->getNom() << " !" << endl;

                int atkJoueur = joueur->getAtk();
                int defMonstre = adversaire->getDef();

                // petite variation aléatoire
                uniform_int_distribution<> variance(0, atkJoueur / 4);
                int bonus = variance(gen);

                int degats = atkJoueur + bonus - defMonstre;

                if (degats < 0) degats = 0;

                // critique (10%)
                uniform_int_distribution<> critDist(1, 100);
                if (critDist(gen) > 90) {
                    degats *= 2;
                    cout << "Coup critique !" << endl;
                }

                if (degats == 0) {
                    cout << "L'épée te glisse entre les doigts, l'attaque n'inflige aucun degat..." << endl;
                } else {
                    cout << "=> Tu infliges [" << degats << "] degats ! <=" << endl;
                    adversaire->recevoirDegats(degats);
                }

                break;
            }
            case 2: // ACT
                cout << "\nActions disponibles :" << endl;
                
                // On appelle getActions() directement dans la boucle
                for (size_t i = 0; i < adversaire->getActions().size(); ++i) {
                    cout << i + 1 << ". " << adversaire->getActions()[i]->getIdentifiant() << endl;
                }
                
                int choixAct;
                cout << "Quelle action ? : "; 
                cin >> choixAct;
                
                if (choixAct > 0 && choixAct <= (int)adversaire->getActions().size()) {
                    // On appelle getActions() directement pour exécuter
                    adversaire->getActions()[choixAct - 1]->executer(adversaire);
                } else {
                    cout << "Tu begayes et restes plante la sans rien faire..." << endl;
                }
                break;
            case 3: { // ITEM
                vector<Item*>& inv = joueur->getInventaire();

                joueur->afficherInventaire();

                if (inv.empty()) {
                    break;
                }

                cout << "Choisis un item : ";

                int choixItem;
                cin >> choixItem;

                // validation
                if (choixItem < 0 || choixItem >= inv.size()) {
                    cout << "Choix invalide !" << endl;
                    break;
                }

                Item* item = inv[choixItem];

                if (item->getQuantite() <= 0) {
                    cout << "Cet item n'est plus disponible !" << endl;
                    break;
                }

                // effet
                string type = item->getType();
                int val = item->getValeur();

                cout << "\nUtilisation de " << item->getNom() << " !" << endl;

                if (type == "HEAL") {
                    joueur->soigner(val);
                    cout << "Tu recuperes " << val << " HP !" << endl;
                }
                else if (type == "MERCY") {
                    adversaire->modifierMercy(val);
                    cout << "La mercy augmente de " << val << " !" << endl;
                }
                else if (type == "ATK") {
                    joueur->augmenterAtk(val);
                    cout << "Ton attaque augmente de " << val << " !" << endl;
                }
                else if (type == "DEF") {
                    joueur->augmenterDef(val);
                    cout << "Ta defense augmente de " << val << " !" << endl;
                }


                // consommation
                item->reduireQuantite();
            break;
            }
            case 4: // MERCY
                if (adversaire->peutEtreEpargne()) {
                    cout << "\nTu as apaise " << adversaire->getNom() << ". Tu l'epargnes et le combat prend fin pacifiquement !" << endl;
                    
                    joueur->ajouterMonstreEpargne();
                    victoires++;
                    combatEnCours = false;
                    
                    continue; 
                } else {
                    cout << "\n" << adversaire->getNom() << " te regarde d'un air menacant. Il ne veut pas encore s'arreter !" << endl;
                    cout << "(Astuce : Utilise ACT pour faire monter sa jauge de Mercy a " << adversaire->getMercyObjectif() << ")" << endl;
                }

                listeBestiaire.push_back("[EPARGNE] " + adversaire->getNom() + " (" + adversaire->getCategorie() + ")");
                break;
            default:
                cout << "Choix invalide, tu perds ton tour !" << endl;
        }

        if (adversaire->estVaincu()) {
            cout << "\nBravo, tu as vaincu " << adversaire->getNom() << " !" << endl;
            victoires++;
            joueur->ajouterMonstreTue();

            Item* loot = tirerItemAleatoire(gen);

            if (loot) {
                cout << "Tu obtiens : " << loot->getNom()
                    << " (" << loot->getRarete() << ")" << endl;

                Item* copie = new Item(
                    loot->getNom(),
                    loot->getType(),
                    loot->getValeur(),
                    1,
                    loot->getRarete()
                );
                joueur->ajouterItem(copie);
            } else {
                cout << "Aucun objet obtenu..." << endl;
            }

            combatEnCours = false;

            listeBestiaire.push_back("[TUE] " + adversaire->getNom() + " (" + adversaire->getCategorie() + ")");

            continue;
        }

        cout << "\n==================================================" << endl;
        cout << ">>> TOUR DE "<< adversaire->getNom() <<" <<<" << endl;
        cout << "--------------------------------------------------" << endl;
        
        int atkMonstre = adversaire->getAtk();
        int defJoueur = joueur->getDef();

        // variation aléatoire
        uniform_int_distribution<> variance(0, atkMonstre / 4);
        int bonus = variance(gen);

        int degatsMonstre = atkMonstre + bonus - defJoueur;

        if (degatsMonstre < 0) degatsMonstre = 0;

        // critique (10%)
        uniform_int_distribution<> critDist(1, 100);
        if (critDist(gen) > 90) {
            degatsMonstre *= 2;
            cout << adversaire->getNom() << " porte un COUP CRITIQUE !" << endl;
        }

        if (degatsMonstre == 0) {
            cout << adversaire->getNom() << " trebuche et rate son attaque !" << endl;
        } else {
            cout << adversaire->getNom() << " t'attaque et t'inflige [" << degatsMonstre << "] degats !" << endl;
            joueur->recevoirDegats(degatsMonstre);
        }

        if (joueur->getHpActuel() <= 0) {
            cout << "\nTu as peri au combat... GAME OVER." << endl;
            combatEnCours = false;
            enCours = false;
        }

        if (combatEnCours) {
            cout << "\n(Appuyez sur Entree pour continuer...)" << endl;
            cin.ignore(10000, '\n');
            cin.get();
            numTour++;
        }
    }
}

Item* Jeu::tirerItemAleatoire(mt19937& gen) {

    // 1. Tirage de rareté
    uniform_int_distribution<> distRarete(1, 100);
    int roll = distRarete(gen);

    string rareteChoisie;

    if (roll <= 60) rareteChoisie = "COMMUN";
    else if (roll <= 90) rareteChoisie = "RARE";
    else rareteChoisie = "EPIC";

    // 2. Filtrer les items de cette rareté
    vector<Item*> candidats;

    for (Item* item : poolItems) {
        if (item->getRarete() == rareteChoisie) {
            candidats.push_back(item);
        }
    }

    // 3. Sécurité (au cas où)
    if (candidats.empty()) {
        cout << "Aucun item de rarete " << rareteChoisie << endl;
        return nullptr;
    }

    // 4. Tirage aléatoire parmi les candidats
    uniform_int_distribution<> distPick(0, candidats.size() - 1);
    return candidats[distPick(gen)];
}

void Jeu::donnerItemsDeDepart() {

    if (poolItems.empty()) return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, poolItems.size() - 1);

    cout << "\n=== INVENTAIRE DE DEPART ===" << endl;

    for (int i = 0; i < 3; i++) { // 🔥 3 items de départ

        Item* base = poolItems[dist(gen)];

        // copie propre
        Item* copie = new Item(
            base->getNom(),
            base->getType(),
            base->getValeur(),
            1,
            base->getRarete()
        );

        joueur->ajouterItem(copie);

        cout << "- " << copie->getNom() << endl;
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

        string nom, type, valeurStr, quantiteStr, rareteStr;

        if (!getline(ss, nom, ';') ||
            !getline(ss, type, ';') ||
            !getline(ss, valeurStr, ';') ||
            !getline(ss, quantiteStr, ';') ||
            !getline(ss, rareteStr)) {
            std::cout << "Ligne mal formee (items) ignoree à la ligne " << ligneNum << " : " << ligne << std::endl;
            continue;
        }

        try {
            int valeur = std::stoi(valeurStr);
            int quantite = std::stoi(quantiteStr);

            Item* item = new Item(nom, type, valeur, quantite, rareteStr);
            poolItems.push_back(item);

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


void Jeu::verifierConditionFin() {

    if (victoires >= 10) {
        enCours = false;

        cout << "\n==================================================" << endl;
        cout << "                  FIN DE L'AVENTURE                 " << endl;
        cout << "==================================================" << endl;

        // Récupération des statistiques du joueur
        int tues = joueur->getNbMonstresTues();
        int epargnes = joueur->getNbMonstresEpargnes();

        if (tues == 0) {
            cout << "*** FIN PACIFISTE ***" << endl;
            cout << "Tu as un coeur en or. Tu n'as blesse aucun monstre !" << endl;
        } 
        else if (epargnes == 0) {
            cout << "*** FIN GENOCIDAIRE ***" << endl;
            cout << "Tu es le veritable monstre... Tu as extermine tout le monde." << endl;
        } 
        else {
            cout << "*** FIN NEUTRE ***" << endl;
            cout << "Tu as survecu, mais a quel prix ? (" << tues << " monstres tues, " << epargnes << " epargnes)." << endl;
            cout << "Bilan : " << tues << " morts et " << epargnes << " vies sauvees." << endl;
        }
        
        cout << "==================================================\n" << endl;
    }
}

void Jeu::afficherBestiaire() {
    cout << "\n=================== BESTIAIRE ===================\n" << endl;

    if (listeBestiaire.empty()) {
        cout << "Votre carnet est vide. Partez a l'aventure pour le remplir !" << endl;
    } else {
        for (const string& phrase : listeBestiaire) {
            cout << "- " << phrase << endl;
        }
    }
    
    cout << "\n=================================================\n" << endl;
}