#pragma once
#include <string>
#include <vector>
#include "Joueur.h"
#include "Monstre.h"
#include "MonstreNormal.h"
#include "MonstreMiniBoss.h"
#include "MonstreBoss.h"
#include "ActionACT.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Jeu {
private:
    bool enCours;
    int victoires;
    
    Joueur* joueur; 
    vector<Monstre*> monstres;      

public:
    Jeu();
    ~Jeu(); 
    
    void demarrerJeu();
    void afficherMenuPrincipal();
    void demarrerCombat();
    void afficherBestiaire();

private:
    void chargerItems(string nomFichier);
    void chargerMonstres(string nomFichier);
    void verifierConditionFin();
};