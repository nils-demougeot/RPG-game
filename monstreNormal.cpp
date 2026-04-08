#include "MonstreNormal.h"

MonstreNormal::MonstreNormal(string nom, int hp, int attaque, int defense, int mercyObjectif)
    : Monstre(nom, "NORMAL", hp, attaque, defense, mercyObjectif) {}
// NORMAL : 2 actions
int MonstreNormal::getNbActionsActDisponibles() const { return 2; } 