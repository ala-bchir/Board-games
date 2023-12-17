#include "Jeu.hpp"

// Constructeur
Jeu::Jeu(int tailleDamier) : damier(tailleDamier) {}


// Ajouter une pièce
void Jeu::ajouterPion(Pion* pion) {
    pions.push_back(pion);
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
            damier.setCellule(x, y, '.');  // Mettre à jour le damier pour refléter la suppression de la pièce
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
// Methode pour l'affichage : Entrée les coordonnées où l'on souhaite se déplacer
std::pair<int, int> Jeu::CoordonneeDeplacement() const {
    int x, y;
    while (true) {
        std::cout << "Entrez les coordonnées (format: x y): ";
        std::cin >> x >> y;

        if (std::cin.fail() || !damier.CoordonneesValides(x, y)) {
            std::cout << "Coordonnées invalides. Veuillez réessayer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return std::make_pair(x, y);
    }
}