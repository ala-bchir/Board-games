#ifndef BUTIN_HPP
#define BUTIN_HPP

#include "Jeu.hpp"
class Butin : public Jeu {
private :
    // Méthodes privées pour la logique interne du jeu
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
    int pointsSymbole(string symbole) const;
    int pointsPion(const Pion* pion) const;
    bool Score(int joueur) const ;
    
public:
    Butin();
    virtual ~Butin();
    // Implémentation des méthodes virtuelles de Jeu
    void initialiserJeu() override;

    bool jouerUnTour(int joueur) override;
};


#endif // BUTIN_HPP