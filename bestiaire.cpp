#include "Bestiaire.h"
#include <iostream>

Bestiaire::Bestiaire() {
    resultatCombat = "En attente";
}

void Bestiaire::afficherBestiaire() const {
    cout << "--- BESTIAIRE ---" << endl;
    if (monstresVaincus.empty()) {
        cout << "Aucun monstre vaincu pour le moment." << endl;
    }
    
}