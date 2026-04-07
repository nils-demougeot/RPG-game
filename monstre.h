#pragma once
#include <string>

using namespace std;

class Monstre {
protected: 
    string nom;
    string categorie;
    int hp;
    int attaque;
    int defense;
    int mercyObjectif;
    int mercyActuel;

public:
    Monstre(string nom, string categorie, int hp, int attaque, int defense, int mercyObjectif);
    virtual ~Monstre() = default; 
    
    void recevoirDegats(int montant);
    void modifierMercy(int montant);
    bool estVaincu() const;
    bool peutEtreEpargne() const;
    
    virtual int getNbActionsActDisponibles() const = 0; 
};