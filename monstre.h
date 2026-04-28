#pragma once
#include <string>
#include <vector>

using namespace std;

class ActionACT;

class Monstre {
protected: 
    string nom;
    string categorie;
    int hp;
    int hpMax;
    int attaque;
    int defense;
    int mercyObjectif;
    int mercyActuel;
    string statut; 
    vector<ActionACT*> actions;

public:
    Monstre(string nom, string categorie, int hp, int attaque, int defense, int mercyObjectif, int mercyActuel);
    virtual ~Monstre() = default; 
    string getNom() const;
    string getCategorie() const;
    int getHpMax() const;
    int getAtk() const;
    int getDef() const;
    
    void recevoirDegats(int montant);
    void modifierMercy(int montant);
    bool estVaincu() const;
    bool peutEtreEpargne() const;
    virtual void afficherMonstre() const = 0;
    
    virtual int addAction(ActionACT* a) = 0;
    virtual const std::vector<ActionACT*>& getActions() const = 0;
};