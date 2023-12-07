// Jeu.hpp
#ifndef JEU_HPP
#define JEU_HPP

#include <iostream>
#include <limits>
#include <utility>
#include "Damier.hpp"
#include "pion.hpp"
#include <vector>


class Jeu {
protected:
    Damier damier; // Damier du jeu
    std::vector<Pion*> pions; // Liste des pions avec pointeurs bruts
    virtual bool estMouvementValide(int xDepart, int yDepart, int xArrivee, int yArrivee) const = 0; 
    // Méthodes pour gérer les pièces
    void ajouterPion(Pion* pion);
    Pion* getPion(int x, int y) const;
    void supprimerPion(int x, int y);
    //Récupérer le déplacement d'un joueur 
    std::pair<int, int> CoordonneeDeplacement() const;

public:
    // Constructeur
    Jeu(int tailleDamier);

    // Destructeur virtuel pour une bonne gestion de la mémoire avec l'héritage
    virtual ~Jeu() = default;

    // Méthodes virtuelles pures - à implémenter dans les classes dérivées
    virtual void initialiserJeu() = 0; // Initialiser le jeu
    // Logique Interne du jeu
    virtual void afficherJeu() const = 0; // Afficher l'état du jeu
    virtual bool jouerUnTour(int joueur) = 0; // Jouer un tour de jeu
    virtual bool estVictoire() const = 0; // Condition pour gagner
    virtual bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) =0;
    
    
};

#endif // JEU_HPP
