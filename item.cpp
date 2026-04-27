#include "Item.h"
#include <iostream>

Item::Item(string nom, string type, int valeur, int quantite, string rarete)
    : nom(nom), type(type), valeur(valeur), quantite(quantite), rarete(rarete) {}

void Item::utiliser(Joueur* j) {
    
    cout << "Utilisation de l'item : " << nom << endl;
}

int Item::getQuantite() const { return quantite; }

void Item::reduireQuantite() {
    if (quantite > 0) quantite--;
}

string Item::getNom() const { return nom; }

string Item::getType() const { return type; }

int Item::getValeur() const { return valeur; }

string Item::getRarete() const { return rarete; }
