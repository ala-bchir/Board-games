#ifndef BARRIERE_HPP
#define BARRIERE_HPP

#include <utility> 

class Barriere {
public:
    // Type Case
    using Case= std::pair<int, int>;

    // Constructeur (on distingue le barriere par sa position qui est entre deux cases)
    Barriere(int x1, int y1, int x2, int y2);

    // Accesseurs
    Case getPremier() const;
    Case getSecond() const;

    // Méthode statique pour obtenir le nombre total de barrières créées
    static int getNombreBarrieres();

private:
    // Coordonnées des deux cases entourant la barrière
    Case premier, second;

    // Compteur statique pour le nombre de barrières
    static int nombreBarrieres;
};

#endif // BARRIERE_HPP
