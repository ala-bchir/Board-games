#include <iostream>
#include "Pion.hpp"
#include "Safari.hpp"
#include <string>
#include <vector>

int main() {
    
    Safari safari ;
    safari.initialiserJeu();
    int joueur_actuel = 1;  
    bool jeuTermine = false;
    
    
    
    // Placement alterné des animaux pour chaque joueur
    for (int i = 0; i < 6; ++i) {
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
    safari.afficheIG();

    std::cout << "La phase de placement est finie que le jeu commence : \n" << endl ;

    JoueurSafari currentJoueur = safari.joueurL;

    do{
        if(safari.jouerUnTourSafari(currentJoueur)){
            jeuTermine = true;
        }else{
            currentJoueur = (currentJoueur.getId() == safari.joueurL.getId()) ? safari.joueurG : safari.joueurL;
        }
        safari.afficheIG();
           
    }while(!jeuTermine);

    return 0;
}

