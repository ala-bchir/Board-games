#include "Damier.hpp"
#include <iostream>

//Constructeur du Damier 
Damier::Damier(int taille) {
    if (taille < 0) {
        throw std::invalid_argument("La taille du damier doit être positive.");
    }

    this->taille = taille;
    grille.resize(taille, std::vector<char>(taille, '.'));
}
//Affichage du Damier
void Damier::afficher() const {
    for (const std::vector<char>& ligne : grille){
        for(char cellule : ligne){
            std::cout << cellule << " ";
        }
        std::cout << std::endl;  // Saut de ligne après chaque ligne du damier
    }
}

// Modifier une cellule du damier
void Damier::setCellule(int x, int y, char valeur) {
    if (x >= 0 && x < taille && y >= 0 && y < taille) {
        grille[x][y] = valeur;
    } else {
        //Afficher un message d'erreur grâce à cerr(= cout mais sans buffer donc affichage direct)
        std::cerr << "Position hors du damier !" << std::endl;
    }
}

// Obtenir la valeur d'une cellule
char Damier::getCellule(int x, int y) const {
    if (x >= 0 && x < taille && y >= 0 && y < taille) {
        return grille[x][y];
    } else {
        std::cerr << "Position hors du damier !" << std::endl;
        return ' '; // Retourne un caractère vide en cas d'erreur
    }
}

// Obtenir la taille du damier
int Damier::getTaille() const {
    return taille;
}
bool Damier::CoordonneesValides(int x, int y) const {
    // Vérifier si les coordonnées sont dans les limites du damier
    return x >= 0 && x < getTaille() && y >= 0 && y < getTaille();
}