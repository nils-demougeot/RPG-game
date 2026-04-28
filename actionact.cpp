#include "ActionACT.h"
#include "monstre.h"
#include <iostream>

ActionACT::ActionACT(string identifiant, string texte, int impactMercy)
    : identifiant(identifiant), texte(texte), impactMercy(impactMercy) {}

void ActionACT::executer(Monstre* m) {
    cout << texte << endl;

    cout << "=> Mercy augmentee de : +" << impactMercy << " points !" << endl;

    m->modifierMercy(impactMercy);

    if (m->peutEtreEpargne()) {
        cout << "\n!!! Le monstre semble prêt à t'écouter. Tu peux essayer de l'épargner (MERCY) !" << endl;
    }
}

string ActionACT::getIdentifiant() const {
    return identifiant;
}