#include <iostream>
#include "Pion.hpp"
#include "Safari.hpp"
#include <string>
#include <vector>

int main() {
    
    Safari safari ;
    safari.initialiserJeu();
    int joueur_actuel = 1;  // Commencez avec le joueur 1

    //safari.afficheIG();
    // Placement alterné des animaux pour chaque joueur
    // Placement alterné des animaux pour chaque joueur
    for (int i = 0; i < 3; ++i) {
        int x, y;

        do {
            safari.afficherJeu();
            std::cout << "\n";
            
            std::cout << "Joueur " << joueur_actuel << ", veuillez placer votre animal ( x y ):\n";
            std::cin >> x >> y;

        } while (!(safari.placerAnimal((joueur_actuel == 1) ? safari.joueurL : safari.joueurG, x, y)));

        // Passez au joueur suivant
        joueur_actuel = (joueur_actuel == 1) ? 2 : 1;
    }

    std::cout << "La phase de placement est finie que le jeu commence : \n" << endl ;

    JoueurSafari currentJoueur = safari.joueurL;

    for (int i = 0; i < 6; i++) {
        if (safari.jouerUnTourSafari(currentJoueur)) {
            // Le joueur actuel a gagné
            break;
        }

    // Changer de joueur pour le tour suivant
    currentJoueur = (currentJoueur.getId() == safari.joueurL.getId()) ? safari.joueurG : safari.joueurL;
}
    
    
    

    return 0;
}

