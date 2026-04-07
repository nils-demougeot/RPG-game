#pragma once
#include <string>
#include <vector>
#include "Joueur.h"
#include "Monstre.h"
#include "MonstreNormal.h"
#include "MonstreMiniBoss.h"
#include "MonstreBoss.h"
#include "ActionACT.h"
#include "Bestiaire.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Jeu {
private:
    bool enCours;
    int victoires;
    
    Joueur* joueur; 
    Bestiaire* bestiaire;
    vector<Monstre*> monstres;      
    vector<ActionACT*> actionsAct;  

public:
    Jeu();
    ~Jeu(); 
    
    void demarrerJeu();
    void afficherMenuPrincipal();
    void demarrerCombat();

private:
    void chargerItems(string nomFichier);
    void chargerMonstres(string nomFichier);
    void verifierConditionFin();
};