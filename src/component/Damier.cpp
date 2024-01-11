#include "Damier.hpp"
#include <iostream>

 
Damier::Damier(int taille) 
    : taille(taille > 0 ? taille : 1),  // Utilisez une taille minimale de 1 si la taille fournie est non positive
      grille(this->taille, std::vector<std::string>(this->taille, ".")) {
}
//Affichage du Damier
void Damier::afficher() const {
    for (const std::vector<string>& ligne : grille){
        for(string cellule : ligne){
            std::cout << cellule << " ";
        }
        std::cout << std::endl;  // Saut de ligne après chaque ligne du damier
    }
}

// Modifier une cellule du damier
void Damier::setCellule(int x, int y, const string& valeur) {
    if (x >= 0 && x < taille && y >= 0 && y < taille) {
        grille[x][y] = valeur;
    } else {
        //Afficher un message d'erreur grâce à cerr(= cout mais sans buffer donc affichage direct)
        std::cerr << "Position hors du damier" << std::endl;
    }
}

// Obtenir la valeur d'une cellule
string Damier::getCellule(int x, int y) const {
    if (x >= 0 && x < taille && y >= 0 && y < taille) {
        return grille[x][y];
    } else {
        std::cerr << "Position hors du damier " << std::endl;
        return " "; // Retourne un caractère vide en cas d'erreur
    }
}

int Damier::getTaille() const {
    return taille;
}
bool Damier::CoordonneesValides(int x, int y) const {
    // Vérifier si les coordonnées sont dans les limites du damier
    return x >= 0 && x < getTaille() && y >= 0 && y < getTaille();
}

