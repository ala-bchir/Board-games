#include "Butin.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


Butin::Butin():Jeu(8) { 
     
}
// Création des Pions
void Butin::creerPions() {
    // Ajout au vecteur 'Pions'
    // Pions noirs
    for (int i = 0; i < 10; ++i) {
        ajouterPion(new Pion(-1, -1, "N"));
    }

    // Pions rouges
    for (int i = 0; i < 20; ++i) {
        ajouterPion(new Pion(-1, -1, "R"));
    }

    // Pions jaunes
    for (int i = 0; i < 34; ++i) {
        ajouterPion(new Pion(-1, -1, "J"));
    }
}

void Butin::initialiserJeu() { 
    creerPions();
    placerPionsAleatoirement();
    afficherJeu();
    supprimerPionsJaunesInitiaux();
}

void Butin::placerPionsAleatoirement() {
    std::random_device rd;
    std::mt19937 g(rd());
    int pionsPlaces = 0;
    while (pionsPlaces < pions.size()) {
        int x = g() % 8;
        int y = g() % 8;

        if (damier.getCellule(x, y) == ".") { // '.' représente une cellule vide
            Pion* Pion = pions[pionsPlaces];
            Pion->setPosition(x, y);
            damier.setCellule(x, y, Pion->getSymbole());
            pionsPlaces++;
        }
    }
}

void Butin::supprimerPionsJaunesInitiaux() {
    for (int joueur = 0; joueur < 2; ++joueur) {
        bool pionSupprime = false;
        while (!pionSupprime) {
            int x, y;
            cout << "Joueur " << (joueur + 1) << ", entrez les coordonnees du pion jaune a supprimer (format: x y): ";
            //Vérifier si il y a une erreur de Saisie
            DemanderSaisieCoordonnees(x, y);
            // Vérifier si les coordonnées sont valides et correspondent à un pion jaune
            if (damier.getCellule(x, y) == "J") {
                damier.setCellule(x, y, "."); // Supprimer le pion jaune du damier
                supprimerPion(x, y); // Supprimer le pion correspondant dans 'Pions'
                pionSupprime = true;
            } else {
                if(damier.getCellule(x, y) != "J"){
                    cerr << "Veuillez choisir un pion Jaune reessayer.\n";
                }
            }
        }
    }
}


bool Butin::estVictoire(int joueur) const{
    // Vérifier s'il reste des sauts possibles avec des pions jaunes
    for (Pion* pion : pions) {
        if (pion->getSymbole() == "J" && SautPossible(pion)) {
            return false;  // Il reste des sauts possibles, donc la partie n'est pas terminée
        }
    }
    return true;
}

bool Butin::estMouvementValide(const Pion *pion, int xDestination, int yDestination) const {
    int xOrigine=pion->getX();
    int yOrigine=pion->getY();
    // Calculer les distances absolues en x et y
    int distanceX = std::abs(xOrigine - xDestination);
    int distanceY = std::abs(yOrigine - yDestination);

    // Vérifier si la distance est exactement de deux cases dans une direction ou diagonalement
    bool estMouvementHorizontal = (distanceX == 2 && distanceY == 0);
    bool estMouvementVertical = (distanceX == 0 && distanceY == 2);
    bool estMouvementDiagonal = (distanceX == 2 && distanceY == 2);

    if (!(estMouvementHorizontal || estMouvementVertical || estMouvementDiagonal)) {
        return false;
    }
    // Vérifier si la case de destination est dans les limites du damier
    if (!damier.CoordonneesValides(xDestination, yDestination)) {
        return false;
    }

    // Vérifier si la case de destination est libre et la case intermédiaire est occupée
    int xMilieu = (xOrigine + xDestination) / 2;
    int yMilieu = (yOrigine + yDestination) / 2;
    return damier.getCellule(xMilieu, yMilieu) != "." && damier.getCellule(xDestination, yDestination) == ".";
}


bool Butin::SautPossible(const Pion* pion) const{
    int x = pion->getX();
    int y = pion->getY();

    // Vérifier chaque direction pour un saut possible
    return (estMouvementValide(pion, x + 2, y) ||    // Droite
            estMouvementValide(pion, x - 2, y) ||    // Gauche
            estMouvementValide(pion, x, y + 2) ||    // Bas
            estMouvementValide(pion, x, y - 2) ||    // Haut
            estMouvementValide(pion, x + 2, y + 2) ||// Diagonale Bas Droite
            estMouvementValide(pion, x - 2, y - 2) ||// Diagonale Haut Gauche
            estMouvementValide(pion, x + 2, y - 2) ||// Diagonale Haut Droite
            estMouvementValide(pion, x - 2, y + 2));  // Diagonale Bas Gauche
}

bool Butin::jouerUnTour(int joueur) {
    afficherJeu();
    std::cout << "Tour du Joueur " << joueur << std::endl;

    Pion* pionChoisi = nullptr;
    bool mouvementRealise = false;
    bool end = false;

    while (end == false) {
        if (!mouvementRealise&&pionChoisi==nullptr) {  // Le joueur peut choisir un pion seulement si aucun mouvement n'a été réalisé
            pionChoisi = ChoixPion();
        }
        char reponse;
        std::cout << "Voulez-vous sauter avec ce pion ? (o/n): ";
        std::cin >> reponse;

        // Vide le buffer pour éviter la lecture de caractères résiduels
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (reponse == 'o' || reponse == 'O') {
            if(!SautPossible(pionChoisi)){
                std::cout<< "Impossible de le chosir car aucun mouvement possible\n";
                if(mouvementRealise){end=true;}
            }
            else{
                int x, y;
                std::cout << "Entrer les coordonnes pour deplacer le pion\n";
                DemanderSaisieCoordonnees(x, y);
                mouvementRealise = Deplacement(pionChoisi, x, y, joueur);
            }
            
        } else if (reponse == 'n' || reponse == 'N') {
            if (mouvementRealise) {
                end=true;  // Si un mouvement a déjà été réalisé, le tour est terminé
            }
            pionChoisi=nullptr;
        } else {
            std::cout << "Reponse invalide. Veuillez repondre par 'o' (oui) ou 'n' (non)." << std::endl;
        }
    }
    if(estVictoire(joueur)){Score(joueur);}
    return estVictoire(joueur);  
}





Pion* Butin::ChoixPion() const{
    int x,y;
    Pion* pionChoisi=nullptr;
    /*Choisir un pion jaune qui peut se déplacer*/
    do {
        std::cout << "Entrez les coordonnees du pion jaune a deplacer (format: x y): ";
        DemanderSaisieCoordonnees(x, y);
        pionChoisi = getPion(x, y);
        if(pionChoisi->getSymbole() != "J"){std::cout<< "Le pion n est pas jaune. \n";}
        else{
            if(!SautPossible(pionChoisi)){
                std::cout<< "Aucun saut n est possible avec ce pion. \n";
            }
        }
    }  
    while (pionChoisi == nullptr || pionChoisi->getSymbole() != "J" || !SautPossible(pionChoisi));
    return pionChoisi;
}

bool Butin::Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) {
    // Vérifiez si le saut est possible
    if (!estMouvementValide(pion, xDestination, yDestination)) {
        std::cerr << "Erreur : Le mouvement est pas valide (case occupee / aucun saut)" << std::endl;
        return false;
    }

    int xOrigine = pion->getX();
    int yOrigine = pion->getY();

    // Capturez le pion sauté
    int xMilieu = (xOrigine + xDestination) / 2;
    int yMilieu = (yOrigine + yDestination) / 2;
    Pion* pionCapture = getPion(xMilieu, yMilieu);
    if (pionCapture) {
        supprimerPion(xMilieu, yMilieu);          // Supprimez le pion de la liste des pièces
        enregistrerCapture(pionCapture, joueur);   // Enregistrez la capture pour le joueur
    }

    // Déplacez le pion
    damier.setCellule(xOrigine, yOrigine, ".");
    damier.setCellule(xDestination, yDestination, pion->getSymbole());
    pion->setPosition(xDestination, yDestination);
    std::cout << "Le pion a ete deplacer\n";
    //On affichage le jeu quand le pion a été déplacer
    afficherJeu();
    return true;
}



Butin::~Butin() {
    // Libérer la mémoire des pions dans le vecteur pieces
    for (Pion* pion : pions) {
        delete pion;
    }
    pions.clear();

    // Libérer la mémoire des pions capturés
    for (std::pair<const int, std::vector<Pion*>>& pair : capturesParJoueur) {
        for (Pion* pionCapture : pair.second) {
            delete pionCapture;
        }
    }
    capturesParJoueur.clear();
}

int Butin::pointsPion(const Pion* pion) const {
    string symbole = pion->getSymbole();
    if (symbole == "N") {
        return 3;  // Pion noir
    } else if (symbole == "R") {
        return 2;  // Pion rouge
    } else {
        return 1;  // Pion jaune 
    }
}

int Butin::pointsSymbole(string symbole) const {
    if (symbole == "N") {
        return 3;  // Pion noir
    } else if (symbole == "R") {
        return 2;  // Pion rouge
    } else {
        return 1;  // Pion jaune
    }
}


bool Butin::Score(int joueur) const {
    // Calculer les scores initiaux des joueurs à partir des pions capturés
    std::map<int, int> scores;
    for (const std::pair<const int, std::vector<Pion*>>& joueur_pions : capturesParJoueur) {
        int scoreJoueur = 0;
        for (const Pion* pion : joueur_pions.second) {
            scoreJoueur += pointsPion(pion);  
        }
        scores[joueur_pions.first] = scoreJoueur;
    }

    // Calculer les points des pions restants sur le plateau
    int pointsPionsRestants = 0;
    for (int x = 0; x < damier.getTaille(); ++x) {
        for (int y = 0; y < damier.getTaille(); ++y) {
            string symbole = damier.getCellule(x, y);
            pointsPionsRestants += pointsSymbole(symbole);  // pointsSymbole retourne les points en fonction du symbole
        }
    }

    // Déduire les points des pions restants du score du dernier joueur
    scores[joueur] -= pointsPionsRestants;

    // Afficher les scores
    for (const std::pair<const int, int>& score : scores) {
        std::cout << "Score du Joueur : " << score.first << "Score du Joueur " << score.second << std::endl;
    }
    return true;
}

void Butin::afficheIG() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Buttin Game");
    window.clear();

    int cellSize = 100; 

    for (int i = 0; i < damier.getTaille(); ++i) {
        for (int j = 0; j < damier.getTaille(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);

            if ((i + j) % 2 == 0) {
                cell.setFillColor(sf::Color(169, 169, 169));
            } else {
                cell.setFillColor(sf::Color::White);
            }

            window.draw(cell);

            std::string symbol = damier.getCellule(i, j);

            if (symbol == "J" || symbol == "R" || symbol == "N") {
                sf::CircleShape circle(cellSize / 3);
                circle.setPosition(i * cellSize + cellSize / 6, j * cellSize + cellSize / 6);

                if (symbol == "J") {
                    circle.setFillColor(sf::Color::Yellow);
                } else if (symbol == "R") {
                    circle.setFillColor(sf::Color::Red);
                } else if (symbol == "N") {
                    circle.setFillColor(sf::Color::Black);
                }
                
                window.draw(circle);
            }
        }
    }

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

