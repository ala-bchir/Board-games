#include "Safari.hpp"

// Constructeur
Safari::Safari():Jeu(8),Maxbarrieres(50) {
     
}

void Safari::initialiserJeu(){
    
}
    

// Placer un animal sur le plateau


void Safari::placerAnimal(int joueurId, int x, int y, const std::string& symbole) {
    
    // Vérifiez si la case est déjà occupée
    if (damier.getCellule(x, y) == ".") {
        // Créez un nouvel animal avec les informations fournies
        Pion nouvelAnimal(x, y, symbole);

        // Placez l'animal dans le damier
        damier.setCellule(x, y, symbole);

        // Ajoutez l'animal au tableau des animaux du Safari
        animaux.push_back(nouvelAnimal);

        // L'animal est bien placé, retournez true
        
    } else {
        // La case est déjà occupée, retournez false
        std::cout << "La case est déjà occupée." << std::endl;
    }
}




void Safari::placerBarriere() {
    do {
        int x1, y1, x2, y2;

        // Demander au joueur les coordonnées de la première case
        std::cout << "Entrez les coordonnées de la première case de la barrière (x y) : ";
        std::cin >> x1 >> y1;

        // Demander au joueur les coordonnées de la deuxième case
        std::cout << "Entrez les coordonnées de la deuxième case de la barrière (x y) : ";
        std::cin >> x2 >> y2;

        // Vérifier si les deux cases sont voisines
        if ((std::abs(x1 - x2) == 1 && y1 == y2) || (std::abs(y1 - y2) == 1 && x1 == x2)) {
            // Créer une nouvelle barrière avec les coordonnées fournies
            Barriere nouvelleBarriere(x1, y1, x2, y2);

            // Ajouter la nouvelle barrière au tableau barrieres
            barrieres.push_back(nouvelleBarriere);

            std::cout << "Barrière placée avec succès !" << std::endl;
            break;  // Sortir de la boucle une fois que des coordonnées valides ont été fournies
        } else {
            std::cout << "Erreur : les deux cases doivent être voisines. Veuillez réessayer." << std::endl;
        }
    } while (true);
}

 
    
    


bool Safari::estVictoire(int joueur) const {
    // Utilisez un dictionnaire pour compter le nombre d'occurrences de chaque symbole
    std::map<std::string, int> occurrences;

    // Parcourez le tableau des animaux du joueur et comptez les occurrences de chaque symbole
    for (const auto& animal : animaux) {
        occurrences[animal.getSymbole()]++;
    }

    // Parcourez le dictionnaire des occurrences
    for (const auto& entry : occurrences) {
        // Si le nombre d'occurrences est égal à la taille du tableau des animaux,
        // cela signifie que le joueur a gagné en ayant un seul type d'animal restant
        if (entry.second == animaux.size()) {
            std::cout << "Le joueur a gagné avec les animaux de type '" << entry.first << "' !" << std::endl;
            return true;
        }
    }

    // Aucune victoire détectée
    return false;
}


bool Safari::estMouvementValide(const Pion* pion, int xDestination, int yDestination)const {
    // Implémentation de la validation du mouvement pour Safari
    // ...
    return true;
}



bool Safari::Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) {
    // Implémentation du déplacement pour Safari
    // ...
    return true;
}

bool Safari::jouerUnTour(int joueur){
    return true;
}

Safari::~Safari() {
}