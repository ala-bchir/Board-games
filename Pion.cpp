#include "pion.hpp"

// Constructeur
Pion::Pion(int x, int y, char symbole) : x{x}, y{y}, symbole{symbole} {}

// Accesseurs et mutateurs
int Pion::getX() const { return x; }
int Pion::getY() const { return y; }
void Pion::setPosition(int newX, int newY) { x = newX; y = newY; }
char Pion::getSymbole() const { return symbole; }
void Pion::setSymbole(char newSymbole) { symbole = newSymbole; }

// Autres méthodes pourraient être définies ici selon les besoins