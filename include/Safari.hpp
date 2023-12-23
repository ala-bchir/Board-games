#ifndef SAFARI_HPP
#define SAFARI_HPP

#include "Jeu.hpp"
#include "Barriere.hpp"
#include "Pion.hpp"   
#include "Joueur.hpp" 
#include <vector>

class Safari : public Jeu {
public:
    // Constructeur
    Safari();

    virtual ~Safari();
    
    

    // Méthodes pour initialiser le jeu
    void initialiserJeu() override;
    void placerAnimal(int joueurId, int x, int y, char symbole); // Pour placer les animaux initialement

    // a changer
    
   

    

    // Gestion du tour de jeu
    void  jouerTour(int joueurId); // Gère le tour d'un joueur spécifique
    void deplacerAnimal(int x, int y, int newX, int newY); // Déplace l'animal 
    void placerBarriere(const Barriere& nouvelleBarriere); // Place une nouvelle barrière

    // Vérification des conditions de fin
    bool estCapture(const Pion& animal); // Vérifie si un animal est capturé
    int determinerGagnant(); // Détermine le gagnant du jeu

private:
    Joueur joueur1;  // Joueur 1 avec un ID de 1
    Joueur joueur2;  // Joueur 2 avec un ID de 2
    std::vector<Pion> animaux; // Animaux sur le plateau
    std::vector<Barriere> barrieres; // Barrières sur le plateau
    int  Maxbarrieres = 50; // nbres de barriers max
 

    
};

#endif // SAFARI_HPP
