#ifndef DAMES_HPP
#define DAMES_HPP

#include "Jeu.hpp"
#include "Pion.hpp"

//Le joueur 1 est le joueur qui joue les blancs, le joueur 2 est celui qui joue les noirs
class Dames : public Jeu {

private:
     // Méthodes privées - logique interne du jeu des dames
    bool estMouvementValide(const Pion* pion, int xDestination, int yDestination) const override;
    bool estMouvementValideDame(const Pion* pion, int xDestination, int yDestination) const;
    bool estMouvementValidePion(const Pion* pion, int xDestination, int yDestination) const;
    bool estMouvementAvecPrise(const Pion* pion, int xDestination, int yDestination) const;
    bool priseObligatoireDisponible(int joueur) const;
    bool priseDisponible(const Pion* pion) const;
    void promouvoirPion(Pion* pion);
    bool estVictoire(int joueur) const override;
    bool effectuerPrise(Pion* pion, int xDestination, int yDestination, int joueur);
    bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) override;
    void placerPions();
    bool seDeplacer(const Pion* pion)const;
    bool estDame(const Pion* pion) const;
public:
    Dames();
    virtual ~Dames();
    // Méthodes virtuelles de Jeu
    virtual void initialiserJeu() override;
    virtual bool jouerUnTour(int joueur) override;
    void afficheIG();

};

#endif // DAMES_HPP
