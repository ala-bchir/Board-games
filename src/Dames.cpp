#include "Dames.hpp"
#include <iostream>

using namespace std;

Dames::Dames():Jeu(8) { // Taille du damier fixée à 8x8
    initialiserJeu(); 
}

bool Dames::estDame(const Pion* pion) const{
    if(pion->getSymbole()=="ND"||pion->getSymbole()=="BD"){
        return true;
    }
    else{return false;}
}

void Dames::placerPions() {
    int taille = damier.getTaille();

    // Placer les pions noirs
    for (int y = 0; y < 3; ++y) { // Les 3 premières rangées
        for (int x = (y % 2); x < taille; x += 2) { // Placer sur les cases noires (alternance)
            Pion* pionNoir = new Pion(x, y, "N"); // 'N' pour un pion noir
            ajouterPion(pionNoir);
            damier.setCellule(x, y, pionNoir->getSymbole());
        }
    }

    // Placer les pions blancs
    for (int y = taille - 3; y < taille; ++y) { // Les 3 dernières rangées
        for (int x = (y % 2); x < taille; x += 2) { // Placer sur les cases noires (alternance)
            Pion* pionBlanc = new Pion(x, y, "B"); // 'B' pour un pion blanc
            ajouterPion(pionBlanc);
            damier.setCellule(x, y, pionBlanc->getSymbole());
        }
    }
}

void Dames::initialiserJeu() {

    placerPions();  
}
// Verifie si chaque le Mouvement est valide
bool Dames::estMouvementValideDame(const Pion* pion, int xDestination, int yDestination) const {
    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    int deltaX = xDestination - xOrigine;
    int deltaY = yDestination - yOrigine;
    char couleurPion = pion->getSymbole().at(0);

    // Vérification du Mouvement Diagonal :
    if (abs(deltaX) != abs(deltaY) || deltaX == 0) {
        std::cout << "Mouvement impossible, doit être diagonal.\n";
        return false;
    }

    int xDirection = deltaX > 0 ? 1 : -1;
    int yDirection = deltaY > 0 ? 1 : -1;
    int compteurPions = 0;

    for (int i = 1; i < abs(deltaX); i++) {
        std::string symboleSurChemin = damier.getCellule(xOrigine + i * xDirection, yOrigine + i * yDirection);
        if (symboleSurChemin != ".") {
            compteurPions++;
            if (compteurPions > 2 || symboleSurChemin.at(0) == couleurPion) {
                std::cout << "Mouvement impossible, au moins 2 pions consécutif sur le chemin.\n";
                return false;
            }
        }
    }

    return true;
}
bool Dames::estMouvementValidePion(const Pion* pion, int xDestination, int yDestination) const {
    //Position du Pion
    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    //Nombre de case 
    int deltaX = xDestination - xOrigine;
    int deltaY = yDestination - yOrigine;
    char couleurPion = pion->getSymbole().at(0); // Prendre le premier caractère pour la couleur
    // Mouvement des pions normaux
        if (abs(deltaX) == 1 && abs(deltaY) == 1) {
            // Mouvement vers l'avant d'une case en diagonale en fonction de la couleur
            if ((couleurPion == 'N' && deltaY == 1) || (couleurPion == 'B' && deltaY == -1)) {
                return true;
            }
        }

        // Règles pour les prises par les pions normaux
        // La prise s'effectue toujours en diagonale mais vers le haut ou le bas et gauche/droite
        if (abs(deltaX) == 2 && abs(deltaY) == 2) {
            int xMilieu = (xOrigine + xDestination) / 2;
            int yMilieu = (yOrigine + yDestination) / 2;
            string pionPris = damier.getCellule(xMilieu, yMilieu);
            
            if (pionPris != "." && pionPris.at(0) != couleurPion) {
                return true; // Prise valide
            }
            else {
                return false;
            }
        }
    return false;
}
bool Dames::estMouvementValide(const Pion* pion, int xDestination, int yDestination) const {
    if (!pion) {
        return false;  // Vérification de base pour s'assurer que le pion est valide
    }
    if (damier.getCellule(xDestination, yDestination) != ".") {
        return false;
    }

    // Vérifier la direction en fonction de la couleur du pion et s'il s'agit d'une dame
    bool estDame = this->estDame(pion);
    //Si c'est une dame
    if (estDame) {
        return estMouvementValideDame(pion, xDestination, yDestination);
    } else {
       return estMouvementValidePion(pion, xDestination, yDestination);
    }

    return false; // Si aucun des cas ci-dessus n'est vrai, le mouvement n'est pas valide
}
//Vérifie si le mouvement s'effectue avec une prise
bool Dames::estMouvementAvecPrise(const Pion* pion, int xDestination, int yDestination) const {
    // Vérifier d'abord si le mouvement est valide
    if (!estMouvementValide(pion, xDestination, yDestination)) {
        return false;
    }

    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    int deltaX = std::abs(xDestination - xOrigine);
    int deltaY = std::abs(yDestination - yOrigine);

    // Si le mouvement est plus grand qu'une case, il pourrait y avoir une prise
    if (deltaX > 1 || deltaY > 1) {
        int xDirection = (xDestination > xOrigine) ? 1 : -1;
        int yDirection = (yDestination > yOrigine) ? 1 : -1;

        // Parcourir les cases entre l'origine et la destination
        for (int i = 1; i < std::max(deltaX, deltaY); ++i) {
            int x = xOrigine + i * xDirection;
            int y = yOrigine + i * yDirection;
            std::string symboleSurChemin = damier.getCellule(x, y);

            // Si une case intermédiaire est occupée par un pion adverse, c'est une prise
            if (symboleSurChemin != "." && symboleSurChemin.at(0) != pion->getSymbole().at(0)) {
                return true;
            }
        }
    }

    return false; 
}
//Vérifie si une prise obligatoire est disponible pour un joueur/Pion
bool Dames::priseObligatoireDisponible(int joueur) const {
    char symboleJoueur = (joueur == 1) ? 'B' : 'N'; // 'B' pour le joueur 1 et 'N' pour le joueur 2

    for (const Pion* pion : pions) {
        // Vérifiez seulement les pions du joueur actuel
        if (pion->getSymbole().at(0) == symboleJoueur) {
            bool estDame = this->estDame(pion);
            int portee = estDame ? damier.getTaille() : 2; // Portée de la dame est la taille du damier, pour un pion c'est 2

            int xOrigine = pion->getX();
            int yOrigine = pion->getY();

            // Vérifier toutes les directions diagonales possibles
            for (int dx = -portee; dx <= portee; dx++) {
                for (int dy = -portee; dy <= portee; dy++) {
                    if (abs(dx) != abs(dy) || dx == 0) continue; // Ignorer les mouvements non diagonaux

                    int xDestination = xOrigine + dx;
                    int yDestination = yOrigine + dy;

                    // S'assurer que les coordonnées de destination sont valides
                    if (xDestination >= 0 && xDestination < damier.getTaille() && yDestination >= 0 && yDestination < damier.getTaille()) {
                        // Vérifiez si le mouvement est une prise
                        if (estMouvementAvecPrise(pion, xDestination, yDestination)) {
                            return true; // Une prise obligatoire est disponible
                        }
                    }
                }
            }
        }
    }
    return false; 
}

bool Dames::priseDisponible(const Pion* pion) const {
    if (!pion) return false;

    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    bool estDame = this->estDame(pion);

    int portee = estDame ? damier.getTaille() : 2;

    for (int dx = -portee; dx <= portee; dx++) {
        for (int dy = -portee; dy <= portee; dy++) {
            if (abs(dx) != abs(dy) || dx == 0) continue; // Ignorer les mouvements non diagonaux

            int xDestination = xOrigine + dx;
            int yDestination = yOrigine + dy;

            // S'assurer que la destination est à l'intérieur des limites du damier
            if (xDestination >= 0 && xDestination < damier.getTaille() &&
                yDestination >= 0 && yDestination < damier.getTaille()) {

                if (estMouvementAvecPrise(pion, xDestination, yDestination)) {
                    return true; // Une prise est possible
                }
            }
        }
    }
    return false; // Aucune prise n'est possible
}

bool Dames::effectuerPrise(Pion* pion, int xDestination, int yDestination, int joueur) {
    if (!pion || !estMouvementValide(pion, xDestination, yDestination)) {
        return false;  // Le mouvement n'est pas valide
    }

    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    int deltaX = xDestination - xOrigine;
    int deltaY = yDestination - yOrigine;

    // Déplacer le pion
    damier.setCellule(xOrigine, yOrigine, ".");
    damier.setCellule(xDestination, yDestination, pion->getSymbole());
    pion->setPosition(xDestination, yDestination);

    // Vérifier si une prise est possible sur le chemin
    bool priseEffectuee = false;
    if (abs(deltaX) > 1 || abs(deltaY) > 1) {  // Si le mouvement est une prise
        int xDirection = (deltaX > 0) ? 1 : -1;
        int yDirection = (deltaY > 0) ? 1 : -1;
        for (int i = 1; i < abs(deltaX); ++i) {
            int x = xOrigine + i * xDirection;
            int y = yOrigine + i * yDirection;
            std::string symboleSurChemin = damier.getCellule(x, y);

            if (symboleSurChemin != "." && symboleSurChemin.at(0) != pion->getSymbole().at(0)) {
                Pion* pionCapture = getPion(x, y);
                if (pionCapture) {
                    enregistrerCapture(pionCapture, joueur);
                    supprimerPion(x, y);
                    priseEffectuee = true;
                }
            }
        }
    }

    return priseEffectuee;
}

//Promotion en Dame
void Dames::promouvoirPion(Pion* pion) {
    if (!pion) return; // Vérifier si le pion est valide
    int x= pion->getX();
    int y = pion->getY();
    char couleurPion = pion->getSymbole().at(0); // Prendre le premier caractère pour la couleur

    // Vérifier si le pion doit être promu
    if ((couleurPion == 'N' && y == damier.getTaille() - 1) || // Pion noir à la dernière rangée du bas
        (couleurPion == 'B' && y == 0)) {                      // Pion blanc à la première rangée du haut
        string symboleDame = (couleurPion == 'N') ? "ND" : "BD"; // Nouveau symbole pour la dame
        pion->setSymbole(symboleDame); // Promouvoir le pion en dame
        damier.setCellule(x, y, symboleDame);
    }
}
//Effectue le déplacement du pion ainsi que les prises sur le passage
bool Dames::Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) {

    if (!pion) return false;

    bool EffectueUnePrise = false;
    do {
        if (!estMouvementValide(pion, xDestination, yDestination)){cout << "Le mouvement pour ce pion n'est pas valide reessayer"<< endl;
        return false;
        }
        else{ 
            EffectueUnePrise = effectuerPrise(pion, xDestination, yDestination, joueur);
            if (EffectueUnePrise) {
                // Vérifier si d'autres prises sont possibles à partir de la nouvelle position
                int xNouveau = pion->getX();
                int yNouveau = pion->getY();
                if (!priseDisponible(pion)) break; // Sortir de la boucle si aucune prise supplémentaire n'est possible
                // Demander les nouvelles coordonnées de destination pour la prochaine prise
                cout <<"Une prise nouvelle prise est disponible, faites la " << endl;
                DemanderSaisieCoordonnees(xDestination, yDestination); 
            }
        }
    } while (EffectueUnePrise);

    // Vérifier si le pion doit être promu en dame
    promouvoirPion(pion);

    return true;

}
bool Dames::estVictoire(int joueur) const{
    char symboleAdversaire = (joueur == 1) ? 'B' : 'N';  // 'B' pour le joueur 2 et 'N' pour le joueur 1
    int pionsAdversaire = 0;

    // Compter les pions de l'adversaire
    for (const Pion* pion : pions) {
        if (pion->getSymbole().at(0) == symboleAdversaire) {
            pionsAdversaire++;
        }
    }

    // Si l'adversaire n'a plus de pions, le joueur actuel a gagné
    if (pionsAdversaire == 0) {
        return true;
    }

    // Vérifier si l'adversaire a des mouvements valides
    for (const Pion* pion : pions) {
        if (pion->getSymbole().at(0) == symboleAdversaire) {
            if (seDeplacer(pion)) {
                return false; // L'adversaire a encore des mouvements valides
            }
        }
    }
    return true;
}

//Vérifie si un pion peut se déplacer.
bool Dames::seDeplacer(const Pion* pion) const {
    if (!pion) return false; 

    int xOrigine = pion->getX();
    int yOrigine = pion->getY();
    bool estDame = this->estDame(pion); // Vérifie si le pion est une dame

    int portee = estDame ? damier.getTaille() : 2;

    for (int dx = -portee; dx <= portee; ++dx) {
        for (int dy = -portee; dy <= portee; ++dy) {
            if (dx == 0 || dy == 0 || abs(dx) != abs(dy)) continue;

            int xDestination = xOrigine + dx;
            int yDestination = yOrigine + dy;

            // Vérifier si la destination est valide et dans les limites du damier
            if (xDestination >= 0 && xDestination < damier.getTaille() &&
                yDestination >= 0 && yDestination < damier.getTaille()) {
                if (estMouvementValide(pion, xDestination, yDestination)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Dames::jouerUnTour(int joueur) {
    afficherJeu();
    std::cout << "Tour du Joueur " << joueur << std::endl;

    bool mouvementRealise = false;
    bool priseObligatoire = priseObligatoireDisponible(joueur);
    while (!mouvementRealise) {
        // Choisir un pion à déplacer
        int xOrigine, yOrigine;
        std::cout << "Choisissez un pion a deplacer (format: x y): ";
        DemanderSaisieCoordonnees(xOrigine, yOrigine);

        Pion* pionChoisi = getPion(xOrigine, yOrigine);
        if (!pionChoisi || pionChoisi->getSymbole().at(0) != (joueur == 1 ? 'B' : 'N')) {
            std::cout << "Choix invalide, veuillez choisir un de vos pions." << std::endl;
            continue;
        }
        // Si une prise est obligatoire, vérifier que le pion choisi peut effectuer une prise
        if (priseObligatoire && !priseDisponible(pionChoisi)) {
            std::cout << "Une prise est obligatoire avec un autre pion. Veuillez reessayer." << std::endl;
            continue;
        }
        if(!seDeplacer(pionChoisi)){
        cout << "Le Pion n'a aucun deplacement possible \n";
        continue;
        }
        // Effectuer le déplacement
        // Choisir la destination
        int xDestination, yDestination;
        std::cout << "Choisissez une destination pour le pion (format: x y): ";
        DemanderSaisieCoordonnees(xDestination, yDestination);
        
        // Vérifier si le mouvement est une prise si une prise est obligatoire
        if (priseObligatoire && !estMouvementAvecPrise(pionChoisi, xDestination, yDestination)) {
            std::cout << "Une prise est obligatoire. Veuillez choisir un mouvement qui capture un pion." << std::endl;
            continue;
        }
        if (Deplacement(pionChoisi, xDestination, yDestination, joueur)) {
            mouvementRealise = true;
            std::cout << "Mouvement effectue." << std::endl;
        } else {
            std::cout << "Mouvement non effectue, veuillez reessayer." << std::endl;
        }
    }
    // Vérifier si le jeu est terminé
    return estVictoire(joueur);
}


Dames::~Dames(){
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
