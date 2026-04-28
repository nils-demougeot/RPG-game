#include "monstre.h"
#include <iostream>

Monstre::Monstre(string nom, string categorie, int hp, int attaque, int defense, int mercyObjectif, int mercyInitial)
    : nom(nom), categorie(categorie), hp(hp), attaque(attaque), defense(defense), 
      mercyObjectif(mercyObjectif), mercyActuel(mercyInitial), hpMax(hp) {}

void Monstre::recevoirDegats(int montant) {
    hp -= montant;
    if (hp < 0) hp = 0;
}

void Monstre::modifierMercy(int montant) {
    mercyActuel += montant;
    if (mercyActuel < 0) mercyActuel = 0;
    if (mercyActuel > mercyObjectif) mercyActuel = mercyObjectif;
}

bool Monstre::estVaincu() const { return hp == 0; }

bool Monstre::peutEtreEpargne() const { return mercyActuel >= mercyObjectif; }

string Monstre::getNom() const {
    return nom;
}

string Monstre::getCategorie() const {
    return categorie;
}

int Monstre::getHpMax() const {
    return hpMax;
}

int Monstre::getAtk() const {
    return hp;
}

int Monstre::getDef() const {
    return defense;
}