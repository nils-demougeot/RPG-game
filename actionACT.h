#pragma once
#include <string>

using namespace std;

class Monstre; 

class ActionACT {
private:
    string identifiant;
    string texte;
    int impactMercy;

public:
    ActionACT(string identifiant, string texte, int impactMercy);
    
    string getIdentifiant() const;
    void executer(Monstre* m);
};