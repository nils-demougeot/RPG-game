#pragma once
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Joueur {
private:
    string nom;
    int hpMax;
    int hpActuel;
    int monstresTues;
    int monstresEpargnes;
    
    vector<Item*> inventaire; 

public:
    Joueur(string nom, int hpMax);
    
    string getNom() const;
    int getHpActuel() const;
    void recevoirDegats(int montant);
    void soigner(int montant);
    void afficherStatistiques() const;
    void ajouterMonstreTue() { monstresTues++; }
    void ajouterMonstreEpargne() { monstresEpargnes++; }
    int getHpMax() const { return hpMax; }
};