// Jeu.hpp
#ifndef JEU_HPP
#define JEU_HPP

#include <map>
#include <iostream>
#include <limits>
#include <utility>
#include "Damier.hpp"
#include "Pion.hpp"
#include <vector>


class Jeu {
protected:
    Damier damier; // Damier du jeu
    std::vector<Pion*> pions; // Liste des pions avec pointeurs bruts
    std::map<int, std::vector<Pion*>> capturesParJoueur; // Liste des pions capturées par chaque joueurs
    virtual bool estMouvementValide(const Pion* pion, int xDestination, int yDestination) const = 0;
    // Méthodes pour gérer les pièces
    void ajouterPion(Pion* pion);
    Pion* getPion(int x, int y) const;
    void supprimerPion(int x, int y);
    void enregistrerCapture(Pion* pionCapturee, int joueur);
    //Récupérer le déplacement d'un joueur 
    std::pair<int, int> CoordonneeDeplacement() const;
    bool DemanderSaisieCoordonnees(int& x, int& y) const;
    virtual void initialiserJeu() = 0; // Initialiser le jeu
    virtual bool estVictoire(int joueur) const = 0; // Condition pour gagner
    virtual bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) = 0;
public:
    Jeu(int tailleDamier);

    virtual ~Jeu() = default;
    void afficherJeu() const; // Afficher l'état du jeu

    // Méthodes virtuelles pures
    virtual bool jouerUnTour(int joueur) = 0; // Jouer un tour de jeu
};

#endif 
