#pragma once
#include "Monstre.h"

using namespace std;


class MonstreMiniBoss : public Monstre {
public:
    MonstreMiniBoss(string nom, int hp, int attaque, int defense, int mercyObjectif);
    
    int addAction(ActionACT* a) override; 
    void afficherMonstre() const;
};
