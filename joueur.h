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
    int attaque;
    int defense;
    int monstresTues;
    int monstresEpargnes;
    
    vector<Item*> inventaire; 

public:
    Joueur(string nom, int hpMax);
    
    string getNom() const;
    int getHpActuel() const;
    int getAtk() const;
    int getDef() const;
    void recevoirDegats(int montant);
    void soigner(int montant);
    void afficherStatistiques() const;
    void afficherInventaire() const;
    void ajouterMonstreTue();
    void ajouterMonstreEpargne();
    int getHpMax() const;
    void ajouterItem(Item* item);
    vector<Item*>& getInventaire();
    void augmenterAtk(int val);
    void augmenterDef(int val);

    int getNbMonstresTues() const;
    int getNbMonstresEpargnes() const;
};