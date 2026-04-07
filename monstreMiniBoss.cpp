#include "MonstreMiniBoss.h"

MonstreMiniBoss::MonstreMiniBoss(string nom, int hp, int attaque, int defense, int mercyObjectif)
    : Monstre(nom, "MINIBOSS", hp, attaque, defense, mercyObjectif) {}
// MINIBOSS : 3 actions [cite: 45]
int MonstreMiniBoss::getNbActionsActDisponibles() const { return 3; }
