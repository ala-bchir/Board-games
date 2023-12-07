#include "Butin.hpp"  // Assurez-vous que ce chemin est correct pour inclure votre classe Butin

int main() {
    Butin jeu;  // Créez une instance de votre jeu
    int joueurActuel = 1;  // Commencez avec le joueur 1
    bool jeuTermine = false;

    while (!jeuTermine) {
        jeu.afficherJeu();  // Affichez l'état actuel du jeu, si vous avez une telle méthode

        jeuTermine = jeu.jouerUnTour(joueurActuel);  // Jouez un tour pour le joueur actuel

        // Changez de joueur (dans cet exemple, on suppose 2 joueurs)
        joueurActuel = joueurActuel == 1 ? 2 : 1;
    }

    // À la fin du jeu, affichez les résultats ou le gagnant
    std::cout << "Fin de la partie!" << std::endl;

    return 0;
}
