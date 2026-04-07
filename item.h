#pragma once
#include <string>

using namespace std;

class Joueur; 

class Item {
private:
    string nom;
    string type;
    int valeurSoin;
    int quantite;

public:
    Item(string nom, string type, int valeurSoin, int quantite);
    
    void utiliser(Joueur* j);
    int getQuantite() const;
    void reduireQuantite();
};