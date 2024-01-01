#include <iostream>
#include "Pion.hpp"
#include "Safari.hpp"
#include <string>
#include <vector>

int main() {
    
    Safari safari ;
    safari.initialiserJeu();
    int joueur_actuel = 1;  // Commencez avec le joueur 1

    // Placement alterné des animaux pour chaque joueur
    for (int i = 0; i < 2; ++i) {
        int x, y;
        std::string symbole;

        std::cout << "Joueur " << joueur_actuel << ", veuillez placer votre animal " << i + 1 << " : ";
        std::cin >> x >> y >> symbole;
        safari.placerAnimal(joueur_actuel, x, y, symbole);

        // Passez au joueur suivant
        joueur_actuel = (joueur_actuel == 1) ? 2 : 1;
    }
    
    safari.placerBarriere();
    safari.afficherJeu();
    

    return 0;
}

