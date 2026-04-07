#pragma once
#include "Monstre.h"

using namespace std;

class MonstreBoss : public Monstre {
public:
    MonstreBoss(string nom, int hp, int attaque, int defense, int mercyObjectif);
    int getNbActionsActDisponibles() const override;
};