#include "Joueur.hpp"
#include "Pion.hpp"

// Constructeur
Joueur::Joueur(const int id) : id(id) {}

// Ajoute un pion à la liste des pions du joueur
void Joueur::ajouterAnimal(const Pion& pion) {
    animaux.push_back(pion);
}

// Retire un pion de la liste des pions du joueur
void Joueur::retirerAnimal(const Pion& pion) {
    for (auto it = animaux.begin(); it != animaux.end(); ++it) {
        if (it->getX() == pion.getX() && it->getY() == pion.getY() && it->getSymbole() == pion.getSymbole()) {
            animaux.erase(it);
            return; // Sortie anticipée après avoir trouvé et retiré le pion
        }
    }
}

// Retourne le vecteur contenant les pions du joueur
std::vector<Pion>& Joueur::getAnimaux() {
    return animaux;
}

// Retourne le nom du joueur
int Joueur::getId() const {
    return id;
}

// Retourne le nombre de pions que le joueur a
int Joueur::getNombreAnimaux() const {
    return animaux.size();
}
