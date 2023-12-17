#ifndef SAFARI_HPP
#define SAFARI_HPP

#include "Jeu.hpp"
#include "Barriere.hpp"
#include <vector>

class Safari : public Jeu {
public:
    // Constructeur
    Safari();

    // Méthode pour ajouter une barrière
    void addBarriere(const Barriere& nouvelleBarriere);

private:
    // Tableau (vector) pour stocker les barrières
    std::vector<Barriere> barrieres;
};

#endif // SAFARI_HPP
