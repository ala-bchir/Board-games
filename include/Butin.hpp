#ifndef BUTIN_HPP
#define BUTIN_HPP

#include "Jeu.hpp"
class Butin : public Jeu {
private :
    void placerPionsAleatoirement();
    void creerPions();
    Pion* ChoixPion() const;
    void supprimerPionsJaunesInitiaux();
    //Méthode pour les Sauts
    bool SautPossible(const Pion* pion) const;
    bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) override;
    bool peutSauterVers(int xOrigine, int yOrigine, int xDestination, int yDestination) const;
    // Méthode virtuelle du Jeu
    bool estMouvementValide(const Pion* pion, int xDestination, int yDestination)const override;
    bool estVictoire(int joueur) const  override;
    // Méthode pour calculer le Score
    int pointsSymbole(string symbole) const;
    int pointsPion(const Pion* pion) const;
    bool Score(int joueur) const ;

    // affichage SFML
    
    
public:
    Butin();
    virtual ~Butin();
    // Méthodes virtuelles du Jeu
    void initialiserJeu() override;

    bool jouerUnTour(int joueur) override;
    void afficheIG();
};


#endif 