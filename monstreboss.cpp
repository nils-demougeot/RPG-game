#include "MonstreBoss.h"


MonstreBoss::MonstreBoss(string nom, int hp, int attaque, int defense, int mercyObjectif)
    : Monstre(nom, "BOSS", hp, attaque, defense, mercyObjectif) {}
// BOSS : 4 actions
int MonstreBoss::getNbActionsActDisponibles() const { return 4; }