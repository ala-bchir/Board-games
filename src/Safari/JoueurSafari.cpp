#include "JoueurSafari.hpp"

JoueurSafari::JoueurSafari(int _id , string _symbole) :id(_id),symbole(_symbole){
    
}  

int JoueurSafari::getId() const {
    return id;
}

string JoueurSafari::getSymbole() const {
    return symbole;
}

const vector<Pion>& JoueurSafari::getPions() const {
    return pions;
}

void JoueurSafari::ajouterPion(Pion* pion) {
    pions.push_back(*pion);
}
