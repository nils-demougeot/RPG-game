#include "MonstreBoss.h"
#include <iostream>
#include "ActionACT.h"

MonstreBoss::MonstreBoss(string nom, int hp, int attaque, int defense, int mercyObjectif)
    : Monstre(nom, "BOSS", hp, attaque, defense, mercyObjectif, 10) {}

    int MonstreBoss::addAction(ActionACT* a) {
    if (actions.size() < 4) {
        actions.push_back(a);
        return 1;
    }
    cout << "Impossible d'ajouter l'action, le Monstre Boss a deja ses 4 actions !" << endl;
    return 0;
    }
    
    void MonstreBoss::afficherMonstre() const {
    cout << "--- " << nom << " (" << categorie << ") ---" << endl;
    cout << "HP : " << hp << " | Attaque : " << attaque << " | Defense : " << defense << endl;
    cout << "Mercy : " << mercyActuel << "/" << mercyObjectif << endl;
    cout << "Statut actuel : " << (statut.empty() ? "En combat" : statut) << endl;
    
    cout << "Actions disponibles (" << actions.size() << "/4) :" << endl;
    if (actions.empty()) {
        cout << "  (Aucune action pour le moment)" << endl;
    } else {
        // On parcourt la liste des actions
        for (size_t i = 0; i < actions.size(); i++) {
            cout << "  - Action " << i + 1 << endl; 
        }
    }
    cout << "-----------------------" << endl;
}
    
    const std::vector<ActionACT*>& MonstreBoss::getActions() const {
        return actions;
    }