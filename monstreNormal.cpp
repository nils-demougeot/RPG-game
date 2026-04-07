#include "MonstreNormal.h"

// Le constructeur appelle celui de la classe mère (Monstre)
MonstreNormal::MonstreNormal(string nom, int hp, int attaque, int defense, int mercyObjectif)
    : Monstre(nom, "NORMAL", hp, attaque, defense, mercyObjectif) {}
// NORMAL : 2 actions [cite: 44]
int MonstreNormal::getNbActionsActDisponibles() const { return 2; } 