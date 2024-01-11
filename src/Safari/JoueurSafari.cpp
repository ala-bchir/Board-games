#include "JoueurSafari.hpp"

JoueurSafari::JoueurSafari(string symbole) :symbole{_symbole}{
        id = nbJoueur ;
        nbJoueur++;
    }  

int Joueur::getId() const {
    return id;
}

int Joueur::getSymbole() const {
    return symbole;
}

const vector<Pion>& Joueur::getPions() const {
    return pions;
}

void Joueur::ajouterPion(const Pion& pion) {
    pions.push_back(pion);  // Ajoute une copie du pion
}


