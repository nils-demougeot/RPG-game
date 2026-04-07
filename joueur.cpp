#include "Joueur.h"
#include <iostream>

Joueur::Joueur(string nom, int hpMax) 
    : nom(nom), hpMax(hpMax), hpActuel(hpMax), monstresTues(0), monstresEpargnes(0) {}

string Joueur::getNom() const { return nom; }

int Joueur::getHpActuel() const { return hpActuel; }

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
    cout << "Tues: " << monstresTues << " | Epargnes: " << monstresEpargnes << endl;
}