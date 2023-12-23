#include "Barriere.hpp"

// Initialisation du compteur statique
int Barriere::nombreBarrieres = 0;

// Constructeur modifié
Barriere::Barriere(int x1, int y1, int x2, int y2) 
    : premier(std::make_pair(x1, y1)), second(std::make_pair(x2, y2)) {
    ++nombreBarrieres;
}

// Accesseurs
Barriere::Case Barriere::getPremier() const {
    return premier;
}

Barriere::Case Barriere::getSecond() const {
    return second;
}

// Méthode statique pour obtenir le nombre total de barrières
int Barriere::getNombreBarrieres() {
    return nombreBarrieres;
}
