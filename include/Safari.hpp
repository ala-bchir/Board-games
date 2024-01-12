#ifndef SAFARI_HPP
#define SAFARI_HPP

#include "Jeu.hpp"
#include "Barriere.hpp"
#include "Pion.hpp"  
#include "JoueurSafari.hpp" 

#include "Damier.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class Safari : public Jeu {
public:
    
    Safari();

    virtual ~Safari();
    
    JoueurSafari joueurL;
    JoueurSafari joueurG;

    // Méthodes pour initialiser le jeu
    void initialiserJeu() override;
    bool placerAnimal(JoueurSafari& joueur, int x, int y);  
    
    // a changer
    
    void afficheIG ();
    //void afficherJeu() ;
    

    // Gestion du tour de jeu
    void placerBarriere(); 
    void checkAnimal();
    bool estAnimalCapture(int x, int y)const;
    void enleverAnimauxCaptures();
    bool barrierePresente(int x, int y) const ;
    Pion* selectionnerAnimal(JoueurSafari& joueur) ;
    bool jouerUnTourSafari(JoueurSafari& joueur);
    
    // methode herité de jeu 
    bool estMouvementValide(const Pion* pion, int xDestination, int yDestination)const override;
    bool estVictoire(int joueur)const  override;
    bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) override;
    bool jouerUnTour(int joueur) override;
   
    
   
    
    // verification des conditions de fin
    bool estVictoireSafari();

    
private:
    std::vector<Pion> animaux; // Animaux sur le plateau
    std::vector<Barriere> barrieres; // Barrières sur le plateau
    int  Maxbarrieres = 50; // nbres de barriers max
    
 

    
};

#endif // SAFARI_HPP
