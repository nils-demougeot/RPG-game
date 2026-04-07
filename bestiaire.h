#pragma once
#include <string>
#include <vector>
#include "Monstre.h"

using namespace std;

class Bestiaire {
private:
    string resultatCombat;
    vector<Monstre*> monstresVaincus; 

public:
    Bestiaire();
    void afficherBestiaire() const;
};