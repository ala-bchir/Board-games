#include <iostream>
#include "Joueur.hpp"
#include "Pion.hpp"
#include <string>
#include <vector>

int main() {
    // Test de la classe Pion
    std::cout << "Test de la classe Pion:" << std::endl;
    Pion pion(1, 2, 'L'); // Crée un pion avec la position (1,2) et le symbole 'L'
    std::cout << "Position initiale du pion: (" << pion.getX() << ", " << pion.getY() << ")" << std::endl;
    pion.setPosition(3, 4); // Change la position du pion
    std::cout << "Nouvelle position du pion: (" << pion.getX() << ", " << pion.getY() << ")" << std::endl;
    
    // Test de la classe Joueur
    std::cout << "\nTest de la classe Joueur:" << std::endl;
    Joueur joueur(1);
    joueur.ajouterAnimal(pion);
    std::cout << "Nombre d'animaux après ajout: " << joueur.getNombreAnimaux() << std::endl;
    joueur.retirerAnimal(pion);
    std::cout << "Nombre d'animaux après retrait: " << joueur.getNombreAnimaux() << std::endl;

    return 0;
}
