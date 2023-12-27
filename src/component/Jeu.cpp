
#include "Jeu.hpp"

// Constructeur
Jeu::Jeu(int tailleDamier) : damier(tailleDamier) {}


// Ajouter une pièce
void Jeu::ajouterPion(Pion* pion) {
    pions.push_back(pion);
}

void Jeu::afficherJeu() const {
    int taille = damier.getTaille();

    // Afficher l'en-tête avec les numéros de colonne
    std::cout << "   ";  // Espacement pour aligner avec les numéros de ligne
    for (int x = 0; x < taille; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Ajouter une ligne de séparation
    std::cout << "   ";  // Alignement de la séparation
    for (int x = 0; x < taille; ++x) {
        std::cout << "--";  // Double trait pour chaque colonne
    }
    std::cout << std::endl;

    // Afficher le damier avec les numéros de ligne
    for (int y = 0; y < taille; ++y) {
        std::cout << y << " |";  // Numéro de ligne suivi d'une barre verticale
        for (int x = 0; x < taille; ++x) {
            std::cout << damier.getCellule(x, y) << " ";
        }
        std::cout << std::endl;
    }

}



// Supprimer une pièce de l'échiquier: 
void Jeu::supprimerPion(int x, int y) {
    if (x < 0 || x >= damier.getTaille() || y < 0 || y >= damier.getTaille()) {
        std::cerr << "Erreur: Coordonnées hors limites." << std::endl;
        return;
    }
    for (size_t i = 0; i < pions.size(); ++i) {
        if ((pions[i]->getX() == x)&&(pions[i]->getY() == y)){
            /*Erase pour la supprimer des vecteurs*/
            pions.erase(pions.begin() + i);
            damier.setCellule(x, y, ".");  // Mettre à jour le damier pour refléter la suppression de la pièce
            break; // Sortie de la boucle après avoir trouvé et supprimé la pièce
        }
    }
}
// Avoir le Pion à la position x y 
Pion* Jeu::getPion(int x, int y) const{
    Pion* PionChoisi=nullptr;
    if (x < 0 || x >= damier.getTaille() || y < 0 || y >= damier.getTaille()) {
        std::cerr << "Erreur: Coordonnées hors limites." << std::endl;
        return nullptr;;
    }
    for (size_t i = 0; i < pions.size(); ++i) {
        if ((pions[i]->getX() == x)&&(pions[i]->getY() == y)){
            PionChoisi=pions[i];
        }
    }
    return PionChoisi;
}

bool Jeu::DemanderSaisieCoordonnees(int& x, int& y) const {
    bool saisieValide;
    do {
        if (!(std::cin >> x >> y)) {
            std::cerr << "Erreur : Saisie invalide. Veuillez entrer des nombres.\n";
            std::cin.clear(); // Effacer l'état d'erreur de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caractères erronés
            saisieValide = false;
        } else {
            saisieValide = damier.CoordonneesValides(x, y);
            if (!saisieValide) {
                std::cerr << "Coordonnees hors limites. Veuillez reessayer.\n";
            }
        }
    } while (!saisieValide);

    return true; // Saisie valide
}
void Jeu::enregistrerCapture(Pion* pieceCapturee, int joueur) {
    capturesParJoueur[joueur].push_back(pieceCapturee);
}
