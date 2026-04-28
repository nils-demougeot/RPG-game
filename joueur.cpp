#include "Joueur.h"
#include <iostream>

Joueur::Joueur(string nom, int hpMax) 
    : nom(nom), hpMax(hpMax), hpActuel(hpMax), attaque(10), defense(3), monstresTues(0), monstresEpargnes(0) {}

string Joueur::getNom() const { return nom; }

int Joueur::getHpActuel() const { return hpActuel; }

int Joueur::getAtk() const { return attaque; }

int Joueur::getDef() const { return defense; }

int Joueur::getNbMonstresTues() const {return monstresTues;}

int Joueur::getNbMonstresEpargnes() const {return monstresEpargnes;}

int Joueur::getHpMax() const {return hpMax;}

void Joueur::recevoirDegats(int montant) {
    hpActuel -= montant;
    if (hpActuel < 0) hpActuel = 0;
}

void Joueur::soigner(int montant) {
    hpActuel += montant;
    if (hpActuel > hpMax) hpActuel = hpMax;
}

void Joueur::afficherStatistiques() const {
    cout << "--- STATS DE " << nom << " ---" << endl;
    cout << "HP: " << hpActuel << "/" << hpMax << endl;
    cout << "ATK: " << attaque << " | DEF: " << defense << endl;
    cout << "Tues: " << monstresTues << " | Epargnes: " << monstresEpargnes << endl;
}

void Joueur::afficherInventaire() const {
    cout << "\n================ INVENTAIRE ================" << endl;

    if (inventaire.empty()) {
        cout << "Inventaire vide." << endl;
        return;
    }

    for (int i = 0; i < inventaire.size(); i++) {
        Item* item = inventaire[i];

        cout << i << ". "
             << item->getNom()
             << " (x" << item->getQuantite() << ")"
             << " | Type: " << item->getType()
             << " | Valeur: " << item->getValeur()
             << " | Rarete: " << item->getRarete()
             << endl;
    }
}

void Joueur::ajouterItem(Item* item) {
    inventaire.push_back(item);
}

vector<Item*>& Joueur::getInventaire() {
    return inventaire;
}

void Joueur::augmenterAtk(int val) {
    attaque += val;
}

void Joueur::augmenterDef(int val) {
    defense += val;
}


void Joueur::ajouterMonstreTue() {
    monstresTues++;
}

void Joueur::ajouterMonstreEpargne() {
    monstresEpargnes++;
}