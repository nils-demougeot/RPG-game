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
#include <map>

using namespace std;

class Jeu {
private:
    bool enCours;
    int victoires;
    
    Joueur* joueur; 
    vector<Monstre*> monstres;     
    map<string, ActionACT*> catalogueActions; 
    void chargerItems(string nomFichier);
    void chargerMonstres(string nomFichier);
    void verifierConditionFin();

    void initialiserCatalogue();
public:
    Jeu();
    ~Jeu(); 
    
    void demarrerJeu();
    void afficherMenuPrincipal();
    void demarrerCombat();
    void afficherBestiaire();

};