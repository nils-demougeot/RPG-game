#include "ActionACT.h"
#include "monstre.h"
#include <iostream>

ActionACT::ActionACT(string identifiant, string texte, int impactMercy)
    : identifiant(identifiant), texte(texte), impactMercy(impactMercy) {}

void ActionACT::executer(Monstre* m) {
    cout << texte << endl;
    m->modifierMercy(impactMercy);
}