#ifndef SAFARI_HPP
#define SAFARI_HPP

#include "Jeu.hpp"
#include "Barriere.hpp"
#include "Pion.hpp"   

#include "Damier.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class Safari : public Jeu {
public:
    // Constructeur
    Safari();

    virtual ~Safari();
    
    

    // Méthodes pour initialiser le jeu
    void initialiserJeu() override;
    void placerAnimal(int joueurId, int x, int y, const std::string& symbole); // Pour placer les animaux initialement

    // a changer
    
   
    //void afficherJeu() ;
    

    // Gestion du tour de jeu
    void placerBarriere(); // Place une nouvelle barrière
    void checkAnimal();
    bool estAnimalCapture(int x, int y)const;
    void enleverAnimauxCaptures();
    bool barrierePresente(int x, int y) const ;
    Pion* selectionnerAnimal(int joueur) ;

    // methode herité de jeu 
    bool estMouvementValide(const Pion* pion, int xDestination, int yDestination)const override;
    bool estVictoire(int joueur)const  override;
    bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) override;
    bool jouerUnTour(int joueur) override;
   
    
   
    
    // Vérification des conditions de fin
    
private:
    std::vector<Pion> animaux; // Animaux sur le plateau
    std::vector<Barriere> barrieres; // Barrières sur le plateau
    int  Maxbarrieres = 50; // nbres de barriers max
 

    
};

#endif // SAFARI_HPP
