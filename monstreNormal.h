#pragma once
#include "Monstre.h"

using namespace std;

class MonstreNormal : public Monstre {
public:
    MonstreNormal(string nom, int hp, int attaque, int defense, int mercyObjectif);
    int getNbActionsActDisponibles() const override;
};