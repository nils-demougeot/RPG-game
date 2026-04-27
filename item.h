#pragma once
#include <string>

using namespace std;

class Joueur; 

class Item {
private:
    string nom;
    string type;
    int valeur;
    int quantite;
    string rarete;

public:
    Item(string nom, string type, int valeur, int quantite, string rarete);
    
    void utiliser(Joueur* j);
    int getQuantite() const;
    void reduireQuantite();

    string getNom() const;
    string getType() const;
    int getValeur() const;
    string getRarete() const;

};