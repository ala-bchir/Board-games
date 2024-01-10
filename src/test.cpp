#include <iostream>
#include "Pion.hpp"
#include "Safari.hpp"
#include <string>
#include <vector>

int main() {
    
    Safari safari ;
    safari.initialiserJeu();
    int joueur_actuel = 1;  // Commencez avec le joueur 1

    safari.afficheIG();
    // Placement alterné des animaux pour chaque joueur
    for (int i = 0; i < 6; ++i) {
        int x, y;
        std::string symbole;

        do{
            
            std::cout << "Joueur " << joueur_actuel << ", veuillez placer votre animal :\n" ;
            safari.afficherJeu();
            std::cin >> x >> y >> symbole;
        
        }while (!(safari.placerAnimal(joueur_actuel, x, y, symbole)));
        
        // Passez au joueur suivant
        joueur_actuel = (joueur_actuel == 1) ? 2 : 1;
    }

    std::cout << "La phase de placement est finie que le jeu commence : \n" << endl ;
    
    safari.jouerUnTour(joueur_actuel);
    

    return 0;
}

