#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include "Pion.hpp"  

class Joueur {
public:
    // Constructeur
    Joueur(const int id);

    // Méthodes pour gérer les animaux
    void ajouterAnimal(const Pion& animal);
    void retirerAnimal(const Pion& animal); // Pour gérer les animaux capturés
    std::vector<Pion>& getAnimaux();

    // Accesseurs
    int getId() const;
    int getNombreAnimaux() const;

private:
    int id;
    std::vector<Pion> animaux;
};

#endif // JOUEUR_HPP
