#include "Butin.hpp"  
#include <iostream>
#include "Dames.hpp"
#include "Safari.hpp"
using namespace std;

int main() {
    
    int choix ;
    // Affichage du message d'accueil
    cout << "Bienvenue dans notre sélection de jeux!\n";
    cout << "Veuillez choisir le jeu auquel vous voulez jouer:\n";
    cout << "1. Buttin\n";
    cout << "2. Dame\n";
    cout << "3. Safari\n";
    cout << "Entrez le numéro de votre choix: ";
    cin >> choix;

    Butin butin; 
    Dames dames; 
    Safari safari;

    int joueurActuel = 1;  // Commencez avec le joueur 1
    bool jeuTermine = false;
    JoueurSafari currentJoueur = safari.joueurL;
    // Gestion du choix
    
    switch (choix) {
        case 1:
            // Code pour démarrer Buttin
            cout << "Vous avez choisi le jeu Buttin.\n";
            butin.initialiserJeu(); 
            butin.afficheIG();
            
            

            while (!jeuTermine) {
                
                butin.afficherJeu();  // Affichez l'état actuel du jeu, si vous avez une telle méthode
                

                jeuTermine = butin.jouerUnTour(joueurActuel);  // Jouez un tour pour le joueur actuel
                butin.afficheIG();

                // Changez de joueur (dans cet exemple, on suppose 2 joueurs)
                joueurActuel = joueurActuel == 1 ? 2 : 1;
            }

            // À la fin du jeu, affichez les résultats ou le gagnant
            std::cout << "Fin de la partie!" << std::endl;

            break;
        case 2:
            // Code pour démarrer Dame
            cout << "Vous avez choisi  Dame.\n";
            dames.initialiserJeu();
            dames.afficheIG();
            while (!jeuTermine) {
                jeuTermine = dames.jouerUnTour(joueurActuel);  // Joue un tour pour le joueur actuel
                // Changez de joueur 
                joueurActuel = joueurActuel == 1 ? 2 : 1;
                dames.afficheIG();
            }
            // Fin de Partie
            std::cout << "Fin de la partie!" << std::endl;
        
            break;
        case 3:
            // Code pour démarrer  Safari
            cout << "Vous avez choisi  Safari.\n";
            safari.initialiserJeu();
            for (int i = 0; i < 6; ++i) {
                int x, y;

                do {
                    safari.afficherJeu();
                    std::cout << "\n";
                    
                    std::cout << "Joueur " << joueurActuel << ", veuillez placer votre animal ( x y ):\n";
                    std::cin >> x >> y;

                } while (!(safari.placerAnimal((joueurActuel == 1) ? safari.joueurL : safari.joueurG, x, y)));

                // Passez au joueur suivant
                joueurActuel = (joueurActuel == 1) ? 2 : 1;
            }
            safari.afficheIG();

            std::cout << "La phase de placement est finie que le jeu commence : \n" << endl ;

            

            do{
                if(safari.jouerUnTourSafari(currentJoueur)){
                    jeuTermine = true;
                }else{
                    currentJoueur = (currentJoueur.getId() == safari.joueurL.getId()) ? safari.joueurG : safari.joueurL;
                }
                safari.afficheIG();
                
            }while(!jeuTermine);
            
        break;
        default:
            // Gestion des entrées non valides
            cout << "Choix non valide. Veuillez entrer un numéro entre 1 et 3.\n";
            break;
    }

    return 0;
}

