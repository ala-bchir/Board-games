#include "Safari.hpp"

// Constructeur
Safari::Safari():jeu(8) ,joueur1(1), joueur2(2),Maxbarrieres(50) {
     
}

void Safari::initialiserJeu(){
    // Initialiser les pions pour chaque joueur
    // 3 lions ('L') pour le joueur 1 et 3 girafes ('G') pour le joueur 2
    char symbolesJoueur1 = 'L';
    char symbolesJoueur2 = 'G';
    for (int i = 0; i < 3; ++i) {
        Pion pionJoueur1(0, 0, symbolesJoueur1); // Position initiale (0,0) sera changée lors du placement
        joueur1.ajouterAnimal(pionJoueur1);

        Pion pionJoueur2(0, 0, symbolesJoueur2);
        joueur2.ajouterAnimal(pionJoueur2);
    }
}
    

// Placer un animal sur le plateau
void Safari::placerAnimal(int joueurId, int x, int y, char symbole) {
    // Choisissez le joueur correct basé sur l'ID
    Joueur* joueurCourant = (joueurId == 1) ? &joueur1 : &joueur2;

    // Trouver un pion avec le symbole correspondant qui n'a pas encore été placé
    for (auto& pion : joueurCourant->getAnimaux()) {
        if (pion.getSymbole() == symbole && pion.getX() == 0 && pion.getY() == 0) { // Supposons que (0,0) signifie non placé
            pion.setPosition(x, y);
            break;
        }
    }
}


