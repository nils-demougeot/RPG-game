#include "Item.h"
#include <iostream>

Item::Item(string nom, string type, int valeurSoin, int quantite) 
    : nom(nom), type(type), valeurSoin(valeurSoin), quantite(quantite) {}

void Item::utiliser(Joueur* j) {
    
    cout << "Utilisation de l'item : " << nom << endl;
}

int Item::getQuantite() const { return quantite; }

void Item::reduireQuantite() {
    if (quantite > 0) quantite--;
}