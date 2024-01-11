#include "Safari.hpp"
#include <SFML/Graphics.hpp>

// Constructeur
Safari::Safari():Jeu(8),Maxbarrieres(50) {
     
}

void Safari::initialiserJeu(){
    
}
    

// Placer un animal sur le plateau


bool Safari::placerAnimal(int joueurId, int x, int y, const std::string& symbole) {
    
    // Vérifiez si la case est déjà occupée
    if (damier.getCellule(x, y) == ".") {
        
        Pion nouvelAnimal(x, y, symbole);// Placez l'animal dans le damier
        damier.setCellule(x, y, symbole);
        animaux.push_back(nouvelAnimal);

        return true;
        
    } else {
        std::cout << "La case est déjà occupée ! Veuillez choisir un autre emplacement" << std::endl;
        return false;
    }
}

Pion* Safari::selectionnerAnimal(int joueur){
    int choix;
    std::cout << "Joueur " << joueur << ", choisissez l'animal à déplacer :" << std::endl;

    // Afficher la liste des animaux du joueur
    for (size_t i = 0; i < animaux.size(); ++i) {
        const Pion& animal = animaux[i];
        std::cout << i + 1 << ". " << animal.getSymbole() << " à la position (" << animal.getX() << ", " << animal.getY() << ")" << std::endl;
    }

    // Demander au joueur de choisir un animal
    do {
        std::cout << "Entrez le numéro de l'animal : ";
        std::cin >> choix;

        // Vérifier si le choix est valide
        if (choix < 1 || choix > animaux.size()) {
            std::cout << "Choix invalide. Veuillez entrer un numéro valide." << std::endl;
        }

    } while (choix < 1 || choix > animaux.size());

    // Retourner l'animal choisi
    return &animaux[choix - 1];
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


bool Safari::estMouvementValide(const Pion* pion, int xDestination, int yDestination) const {
    // Vérifier si la destination est en dehors du damier
    if (!damier.CoordonneesValides(xDestination, yDestination)) {
        return false;
    }

    // Vérifier si la destination est occupée par un autre animal
    const Pion* pionDestination = getPion(xDestination, yDestination);
    if (pionDestination != nullptr) {
        return false; // La destination est occupée par un autre animal
    }

    // Vérifier la présence des barrières sur la trajectoire de l'animal
    int xActuel = pion->getX();
    int yActuel = pion->getY();

    int diffX = std::abs(xDestination - xActuel);
    int diffY = std::abs(yDestination - yActuel);

    // Vérifier si le mouvement est vertical ou horizontal
    if (diffX != 0 && diffY != 0) {
        return false; // Le mouvement n'est ni vertical ni horizontal
    }

    // Vérifier la présence des barrières sur la trajectoire de l'animal
    if (diffX == 0) {
        // Mouvement vertical
        int directionY = (yDestination > yActuel) ? 1 : -1;
        for (int y = yActuel + directionY; y != yDestination; y += directionY) {
            if (barrierePresente(xActuel, y)) {
                return false; // Il y a une barrière sur la trajectoire
            }
        }
    } else {
        // Mouvement horizontal
        int directionX = (xDestination > xActuel) ? 1 : -1;
        for (int x = xActuel + directionX; x != xDestination; x += directionX) {
            if (barrierePresente(x, yActuel)) {
                return false; // Il y a une barrière sur la trajectoire
            }
        }
    }

    return true; // Le mouvement est valide
}


bool Safari::barrierePresente(int x, int y) const {
    for (const Barriere& barriere : barrieres) {
        if (((barriere.getPremier() == std::make_pair(x, y) && barriere.getSecond() == std::make_pair(x, y + 1)) ||
             (barriere.getPremier() == std::make_pair(x, y + 1) && barriere.getSecond() == std::make_pair(x, y))) ||
            ((barriere.getPremier() == std::make_pair(x, y - 1) && barriere.getSecond() == std::make_pair(x, y)) ||
             (barriere.getPremier() == std::make_pair(x, y) && barriere.getSecond() == std::make_pair(x, y - 1))) ||
            ((barriere.getPremier() == std::make_pair(x - 1, y) && barriere.getSecond() == std::make_pair(x, y)) ||
             (barriere.getPremier() == std::make_pair(x, y) && barriere.getSecond() == std::make_pair(x - 1, y))) ||
            ((barriere.getPremier() == std::make_pair(x + 1, y) && barriere.getSecond() == std::make_pair(x, y)) ||
             (barriere.getPremier() == std::make_pair(x, y) && barriere.getSecond() == std::make_pair(x + 1, y)))) {
            // barrière entre les cases (x, y) et (x, y + 1) ou entre (x, y - 1) et (x, y)/ (x, y) et (x+1, y) ou entre (x-1, y)
            
            return true;
        }
    }
    return false;
}



bool Safari::Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) {
    int xDepart = pion->getX();
    int yDepart = pion->getY();

    // Vérifier la validité du mouvement
    if (estMouvementValide(pion, xDestination, yDestination)) {
        // Mettre à jour la case précédente à vide
        damier.setCellule(xDepart, yDepart, ".");

        // Mettre à jour la position de l'animal
        pion->setPosition(xDestination, yDestination);

        // Mettre à jour la nouvelle case avec le symbole du pion
        damier.setCellule(xDestination, yDestination, pion->getSymbole());

        // Autres actions à effectuer en cas de déplacement réussi
        std::cout << "deplacement réussi\n";
        return true; // Le déplacement a réussi
    } else {
        std::cout << "deplacement échoué\n ";
        return false; // Le déplacement est invalide
    }
}

bool Safari::estAnimalCapture(int x, int y) const {
    // Récupérer l'animal à la position (x, y)
    auto it = std::find_if(animaux.begin(), animaux.end(), [x, y](const Pion& animal) {
        return animal.getX() == x && animal.getY() == y;
    });

    // Vérifier s'il y a eu des éléments trouvés
    if (it != animaux.end()) {
        const Pion& animal = *it;

        // Vérifier les mouvements possibles de l'animal
        int mouvementsPossibles = 0;

        // Tester les mouvements possibles dans toutes les directions
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if (i == x && j == y) {
                    continue;  // Ignorer la position actuelle de l'animal
                }

                if (estMouvementValide(&animal, i, j)) {
                    mouvementsPossibles++;
                }
            }
        }

        // Si l'animal peut visiter 8 ou moins de cases, il est capturé
        return mouvementsPossibles <= 8;
    }

    return false; // Animal non trouvé
}

void Safari::enleverAnimauxCaptures() {
    // Parcourir la liste des animaux
    auto it = std::remove_if(animaux.begin(), animaux.end(), [this](const Pion& animal) {
        int x = animal.getX();
        int y = animal.getY();

        // Vérifier si l'animal est enfermé par des barrières dans une zone de moins de 8 cases
        
        if (estAnimalCapture(x, y)) {
            std::cout << "Animal capturé : (" << animal.getX() << "," << animal.getY()<< "," << animal.getSymbole() << ")"<<std::endl;
            damier.setCellule(x, y, "."); // Mettre à jour la case du damier à vide
            return true; // Animal capturé
        }

        return false; 
    });

    // Supprimer les animaux capturés de la liste
    animaux.erase(it, animaux.end());
}


bool Safari::jouerUnTour(int joueur) {
    // Demander au joueur de déplacer l'un de ses animaux
    int xDestination, yDestination;
    Pion* animal;
    
    afficherJeu();

    do {
        // Sélectionner un animal du joueur actuel
        animal = selectionnerAnimal(joueur);

        // Demander au joueur les coordonnées de destination
        std::cout << "Entrez les coordonnées de destination (x y) : ";
        std::cin >> xDestination >> yDestination;

    } while (!Deplacement(animal, xDestination, yDestination, joueur));
    afficherJeu();
    // Place éventuellement une barrière
    placerBarriere();

    // Enlever les animaux capturés
    //enleverAnimauxCaptures();

    // Vérifier la victoire du joueur
    if (estVictoire(joueur)) {

        return true; // La partie est terminée
    }

    return false; // La partie continue
}

void Safari::afficheIG()  {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Safari Game");

    // Boucle principale de rendu
    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Effacer la fenêtre
        window.clear();

        // Dessiner le damier
        int taille = damier.getTaille();
        float cellSize = 800.0f / taille;

        for (int y = 0; y < taille; ++y) {
            for (int x = 0; x < taille; ++x) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x * cellSize, y * cellSize);

                // Changer la couleur en fonction de la position de la cellule (damier noir et blanc)
                if ((x + y) % 2 == 0) {
                    cell.setFillColor(sf::Color::Black);
                } else {
                    cell.setFillColor(sf::Color::White);
                }

                window.draw(cell);
            }
        }

        // Afficher la fenêtre
        window.display();
    }
}


Safari::~Safari() {
    
    for (Pion* pion : pions) {
        delete pion;
    }
    pions.clear();

    
}