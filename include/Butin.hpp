#ifndef BUTIN_HPP
#define BUTIN_HPP

#include <map>
#include "Jeu.hpp"
class Butin : public Jeu {
private :
    // Méthodes privées pour la logique interne du jeu
    void placerPionsAleatoirement();
    void creerPions();
    Pion* ChoixPion() const;
    void supprimerPionsJaunesInitiaux();
    void enregistrerCapture(Pion* pionCapturee, int joueur);
    std::map<int, std::vector<Pion*>> capturesParJoueur;    
    //Méthode pour les Sauts
    bool SautPossible(const Pion* pion) const;
    bool Deplacement(Pion* pion, int xDestination, int yDestination, int joueur) override;
    bool peutSauterVers(int xOrigine, int yOrigine, int xDestination, int yDestination) const;
    // Méthode virtuelle du Jeu
    bool estMouvementValide(int xDepart, int yDepart, int xArrivee, int yArrivee) const override;
    bool estVictoire() const  override;
public:
    Butin();
    virtual ~Butin();
    // Implémentation des méthodes virtuelles de Jeu
    void initialiserJeu() override;
    void afficherJeu() const override;
    bool jouerUnTour(int joueur) override;
};


#endif // BUTIN_HPP