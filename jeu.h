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
#include <random>

using namespace std;

class Jeu {
private:
    bool enCours;
    int victoires;
    vector<Item*> poolItems;
    vector<string> listeBestiaire;
    
    Joueur* joueur; 
    vector<Monstre*> monstres;     
    map<string, ActionACT*> catalogueActions; 
    Item* tirerItemAleatoire(mt19937& gen);
    void chargerItems(string nomFichier);
    void chargerMonstres(string nomFichier);
    void verifierConditionFin();
    void donnerItemsDeDepart();

    void initialiserCatalogue();
public:
    Jeu();
    ~Jeu(); 
    
    void demarrerJeu();
    void afficherMenuPrincipal();
    void demarrerCombat();
    void afficherBestiaire();

};