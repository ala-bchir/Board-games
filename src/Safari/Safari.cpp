#include "Safari.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>



Safari::Safari():Jeu(8),joueurL(1,"L"), joueurG(2,"G"),Maxbarrieres(50) {}

void Safari::initialiserJeu(){}
    

bool Safari::placerAnimal(JoueurSafari& joueur, int x, int y) {
    // Vérifiez si la case est déjà occupée
    if (damier.getCellule(x, y) == ".") {
        Pion nouvelAnimal(x, y, joueur.getSymbole());  // Placez l'animal dans le damier avec le symbole du joueur
        damier.setCellule(x, y, joueur.getSymbole());
        animaux.push_back(nouvelAnimal);
        

        return true;
    } else {
        std::cout << "La case est déjà occupée ! Veuillez choisir un autre emplacement" << std::endl;
        return false;
    }
}

Pion* Safari::selectionnerAnimal(JoueurSafari& joueur) {
    int choix;
    std::cout << "Joueur " << joueur.getId() << ", choisissez l'animal à déplacer :" << std::endl;

    // Afficher la liste des animaux du joueur avec le symbole spécifié
    for (size_t i = 0; i < animaux.size(); ++i) {
        const Pion& animal = animaux[i];
        if (animal.getSymbole() == joueur.getSymbole()) {
            std::cout << i + 1 << ". " << animal.getSymbole() << " à la position (" << animal.getX() << ", " << animal.getY() << ")" << std::endl;
        }
    }

    // Demander au joueur de choisir un animal
    do {
        std::cout << "Entrez le numéro de l'animal : ";
        std::cin >> choix;

        // Vérifier si le choix est valide
        if (choix < 1 || choix > animaux.size() || animaux[choix - 1].getSymbole() != joueur.getSymbole()) {
            std::cout << "Choix invalide. Veuillez entrer un numéro valide." << std::endl;
        }

    } while (choix < 1 || choix > animaux.size() || animaux[choix - 1].getSymbole() != joueur.getSymbole());

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
            // Vérifie si une barriere est deja presente
            if (barrierePresente(x1, y1) || barrierePresente(x2, y2)) {
                std::cout << "Erreur : une barrière existe déjà à cet emplacement. Veuillez réessayer." << std::endl;
            } else {
                // Créer une nouvelle barrière avec les coordonnées fournies
                Barriere nouvelleBarriere(x1, y1, x2, y2);

                // Ajouter la nouvelle barrière au tableau barrieres
                barrieres.push_back(nouvelleBarriere);

                std::cout << "Barrière placée avec succès !" << std::endl;
                break;  // Sortir de la boucle une fois que des coordonnées valides ont été fournies
            }
        } else {
            std::cout << "Erreur : les deux cases doivent être voisines. Veuillez réessayer." << std::endl;
        }
    } while (true);
}

     
bool Safari::estVictoireSafari(){
    bool joueur1Present = false;
    bool joueur2Present = false;

    // Parcourir le tableau des animaux
    for (const auto& animal : animaux) {
        if (animal.getSymbole() == "L") {
            joueur2Present = true;
        } else if (animal.getSymbole() == "G") {
            joueur1Present = true;
        }
    }

    // Conditions de victoire
    if (!joueur1Present) {
        std::cout << "Le joueur 2 a gagné !" << std::endl;
        return true;
    } else if (!joueur2Present) {
        std::cout << "Le joueur 1 a gagné !" << std::endl;
        return true;
    }
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

    if (estMouvementValide(pion, xDestination, yDestination)) {
        damier.setCellule(xDepart, yDepart, ".");

        pion->setPosition(xDestination, yDestination);

        damier.setCellule(xDestination, yDestination, pion->getSymbole());

        std::cout << "deplacement réussi\n";
        return true; //  déplacement a réussi
    } else {
        std::cout << "deplacement échoué\n ";
        return false; // déplacement invalide
    }
}

bool Safari::estAnimalCapture(int x, int y) const {
    // Récupérer l'animal à la position (x, y)
    auto it = std::find_if(animaux.begin(), animaux.end(), [x, y](const Pion& animal) {
        return animal.getX() == x && animal.getY() == y;
    });

    // verifier s'il y a eu des éléments trouvés
    if (it != animaux.end()) {
        const Pion& animal = *it;

        // cérifier les mouvements possibles de l'animal
        int mouvementsPossibles = 0;

        // tester les mouvements possibles dans toutes les directions
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

        // si l'animal peut visiter 8 ou moins de cases, il est capturé
        return mouvementsPossibles <= 8;
    }

    return false; 
}

void Safari::enleverAnimauxCaptures() {
    auto it = std::remove_if(animaux.begin(), animaux.end(), [this](const Pion& animal) {
        int x = animal.getX();
        int y = animal.getY();

        // Vérifier si l'animal est enfermé par des barrières dans une zone de moins de 8 cases( )
        
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

bool Safari::jouerUnTour(int i){return true;} // Non utilisé
bool Safari::estVictoire(int joueur) const {return true;}// Non utilisé

bool Safari::jouerUnTourSafari(JoueurSafari& joueur) {
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

    } while (!Deplacement(animal, xDestination, yDestination, joueur.getId()));
    afficherJeu();

    // Place éventuellement une barrière
    placerBarriere();

    // Enlever les animaux capturés( probleme avec l'algo de la fonction animalCapturé)
    //enleverAnimauxCaptures();

    // Vérifier la victoire du joueur
    if (estVictoireSafari()) {
        return true; // La partie est terminée
    }

    return false;
}

void Safari::afficheIG() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Safari");
    window.clear();

    int cellSize = 100;
    sf::Texture textureG;
    sf::Texture textureL;

    if (!textureG.loadFromFile("images/giraffe.png")) {
    }

    if (!textureL.loadFromFile("images/lion.png")) {
    }

    // créez des sprites pour les lions et les girffes 
    sf::Sprite spriteG(textureG);
    sf::Sprite spriteL(textureL);

    // Dessin du damier
    for (int i = 0; i < damier.getTaille(); ++i) {
        for (int j = 0; j < damier.getTaille(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);

            if ((i + j) % 2 == 0) {
                cell.setFillColor(sf::Color(240, 230, 140));
            } else {
                cell.setFillColor(sf::Color(144, 238, 144));
            }

            window.draw(cell);

            
            std::string symbol = damier.getCellule(i, j);
            // dessin des images
            if (symbol == "L") {
                spriteL.setPosition(i * cellSize + (cellSize - spriteL.getLocalBounds().width) / 2, j * cellSize + (cellSize - spriteL.getLocalBounds().height) / 2);
                window.draw(spriteL);
            } else if (symbol == "G") {
                spriteG.setPosition(i * cellSize + (cellSize - spriteG.getLocalBounds().width) / 2, j * cellSize + (cellSize - spriteG.getLocalBounds().height) / 2);
                window.draw(spriteG);
            }
        }
    }

    // fonctionement non correcte ( affichage mais mauvais sens )
    /* Dessin des barrières
    for (const auto& barriere : barrieres) {
    if (barriere.estVerticale()) {
        // Barrière verticale
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(barriere.getPremier().first * cellSize, barriere.getPremier().second * cellSize), sf::Color::Red),
            sf::Vertex(sf::Vector2f(barriere.getSecond().first  * cellSize, barriere.getSecond().second * cellSize), sf::Color::Red)
        };

        window.draw(line, 2, sf::Lines);
    } else {
        // Barrière horizontale
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(barriere.getPremier().first * cellSize, (barriere.getPremier().second) * cellSize), sf::Color::Red),
            sf::Vertex(sf::Vector2f(barriere.getSecond().first * cellSize, (barriere.getSecond().second)* cellSize), sf::Color::Red)
        };

        window.draw(line, 2, sf::Lines);
    }*/


    window.display();

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::H) {
                    window.close();
                }
            }
        }
    }
}



Safari::~Safari() {
    
    for (Pion* pion : pions) {
        delete pion;
    }
    pions.clear();

    
}