#include "Butin.hpp"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructeur de Butin
Butin::Butin():Jeu(8) { // Taille du damier fixée à 8x8
    initialiserJeu(); 
}

void Butin::creerPions() {
    // Créer les pions et les ajouter au vecteur 'Pions'
    // Ajouter les pions noirs
    for (int i = 0; i < 10; ++i) {
        ajouterPion(new Pion(-1, -1, 'N'));
    }

    // Ajouter les pions rouges
    for (int i = 0; i < 20; ++i) {
        ajouterPion(new Pion(-1, -1, 'R'));
    }

    // Ajouter les pions jaunes
    for (int i = 0; i < 32; ++i) {
        ajouterPion(new Pion(-1, -1, 'J'));
    }
}

void Butin::placerPionsAleatoirement() {
    std::random_device rd;
    std::mt19937 g(rd());
    int pionsPlaces = 0;

    while (pionsPlaces < pions.size()) {
        int x = g() % 8;
        int y = g() % 8;

        if (damier.getCellule(x, y) == '.') { // '.' représente une cellule vide
            Pion* Pion = pions[pionsPlaces];
            Pion->setPosition(x, y);
            damier.setCellule(x, y, Pion->getSymbole());
            pionsPlaces++;
        }
    }
}

void Butin::initialiserJeu() { 
    creerPions();
    placerPionsAleatoirement();
    supprimerPionsJaunesInitiaux();
}

void Butin::supprimerPionsJaunesInitiaux() {
    for (int joueur = 0; joueur < 2; ++joueur) {
        bool pionSupprime = false;
        while (!pionSupprime) {
            int x, y;
            cout << "Joueur " << (joueur + 1) << ", entrez les coordonnées du pion jaune à supprimer (format: x y): ";
            //Vérifier si il y a une erreur de Saisie
            if (!(std::cin >> x >> y)) {
                cerr << "Erreur : Saisie invalide. Veuillez entrer des nombres.\n";
                cin.clear(); // Effacer l'état d'erreur de cin
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer les caractères erronés entré auparavant
                continue; // Recommencer la boucle
            }
            // Vérifier si les coordonnées sont valides et correspondent à un pion jaune
            if (damier.CoordonneesValides(x, y) && damier.getCellule(x, y) == 'J') {
                damier.setCellule(x, y, '.'); // Supprimer le pion jaune du damier
                supprimerPion(x, y); // Supprimer le pion correspondant dans 'Pions'
                pionSupprime = true;
            } else {
                if(damier.getCellule(x, y) != 'J'){
                    cerr << "Veuillez choisir un pion Jaune réessayer.\n";
                }
                else{
                    cerr << "Coordonnées invalides, Veuillez réessayer.\n";
                }
            }
        }
    }
}


bool Butin::estVictoire() const{
    // Vérifier s'il reste des sauts possibles avec des pions jaunes
    for (Pion* pion : pions) {
        if (pion->getSymbole() == 'J' && SautPossible(pion)) {
            return false;  // Il reste des sauts possibles, donc la partie n'est pas terminée
        }
    }
    return true;
}

bool Butin::estMouvementValide(int xOrigine, int yOrigine, int xDestination, int yDestination) const {
    // Vérifier la distance entre l'origine et la destination
    if (std::abs(xOrigine - xDestination) > 2 || std::abs(yOrigine - yDestination) > 2) {
        std::cerr << "Erreur : Le mouvement doit se faire à une distance de deux cases." << std::endl;
        return false;
    }
    // Vérifier si la case de destination est dans les limites du damier
    if(!damier.CoordonneesValides(xDestination, yDestination)){ return false;}

    // Vérifier si la case de destination est libre et la case intermédiaire est occupée
    int xMilieu = (xOrigine + xDestination) / 2;
    int yMilieu = (yOrigine + yDestination) / 2;
    return damier.getCellule(xMilieu, yMilieu) != '.' && damier.getCellule(xDestination, yDestination) == '.';
}

bool Butin::SautPossible(const Pion* Pion) const{
    int x = Pion->getX();
    int y = Pion->getY();

    // Vérifier chaque direction pour un saut possible
    return (estMouvementValide(x, y, x + 2, y) ||    // Droite
            estMouvementValide(x, y, x - 2, y) ||    // Gauche
            estMouvementValide(x, y, x, y + 2) ||    // Bas
            estMouvementValide(x, y, x, y - 2) ||    // Haut
            estMouvementValide(x, y, x + 2, y + 2) ||// Diagonale Bas Droite
            estMouvementValide(x, y, x - 2, y - 2) ||// Diagonale Haut Gauche
            estMouvementValide(x, y, x + 2, y - 2) ||// Diagonale Haut Droite
            estMouvementValide(x, y, x - 2, y + 2));  // Diagonale Bas Gauche
}

bool Butin::jouerUnTour(int joueur) {
    std::cout << "Tour du Joueur " << joueur << std::endl;

    Pion* pionChoisi = nullptr;
    bool sautRealise = false;

    while (true) {
        if (!sautRealise) {  // Le joueur peut choisir un pion seulement si aucun saut n'a été réalisé
            pionChoisi = ChoixPion();
        }

        if (!SautPossible(pionChoisi)) {
            break;  // Si aucun saut n'est possible avec le pion actuel, le tour est terminé
        }

        char reponse;
        std::cout << "Voulez-vous sauter avec ce pion ? (o/n): ";
        std::cin >> reponse;

        if (reponse == 'o' || reponse == 'O') {
            std::pair<int, int> coordonnees = CoordonneeDeplacement();
            int xDestination = coordonnees.first;
            int yDestination = coordonnees.second;

            if (!damier.CoordonneesValides(xDestination, yDestination)) {
                std::cout << "Coordonnées invalides. Veuillez réessayer.\n";
            } else {
                sautRealise = Deplacement(pionChoisi, xDestination, yDestination, joueur);
            }
        } else if (reponse == 'n' || reponse == 'N') {
            if (!sautRealise) {  // Si aucun saut n'a été réalisé, le joueur peut choisir de changer de pion
                continue;
            } else {
                break;  // Si un saut a déjà été réalisé, le tour est terminé
            }
        } else {
            std::cout << "Réponse invalide. Veuillez répondre par 'o' (oui) ou 'n' (non).\n";
        }
    }

    return !estVictoire();  // Vérifier si le jeu est terminé
}




Pion* Butin::ChoixPion() const{
    int x,y;
    Pion* pionChoisi=nullptr;
    /*Choisir un pion jaune qui peut se déplacer*/
    do {
        std::cout << "Entrez les coordonnées du pion jaune à déplacer (format: x y): ";
        std::cin >> x >> y;
        pionChoisi = getPion(x, y);
    } while (pionChoisi == nullptr || pionChoisi->getSymbole() != 'J' || !SautPossible(pionChoisi));
    return pionChoisi;
}

void Butin::enregistrerCapture(Pion* PionCapturee, int joueur) {
    capturesParJoueur[joueur].push_back(PionCapturee);
}

bool Butin::Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) {
    // Vérifiez si le saut est possible
    if (!estMouvementValide(pion->getX(), pion->getY(), xDestination, yDestination)) {
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
    damier.setCellule(xOrigine, yOrigine, '.');
    damier.setCellule(xDestination, yDestination, pion->getSymbole());
    pion->setPosition(xDestination, yDestination);

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

void Butin::afficherJeu()const {
    for (int y = 0; y < damier.getTaille(); ++y) {
        for (int x = 0; x < damier.getTaille(); ++x) {
            std::cout << damier.getCellule(x, y) << " ";
        }
        std::cout << std::endl;
    }
}