#include "Pion.hpp"

using namespace std;

// Constructeur
Pion::Pion(int x, int y, const std::string& symbole) : x{x}, y{y}, symbole{symbole} {}

// Accesseurs et mutateurs
int Pion::getX() const { return x; }
int Pion::getY() const { return y; }
void Pion::setPosition(int x, int y) { this->x = x; this->y = y; }
string Pion::getSymbole() const { return symbole; }
void Pion::setSymbole(const std::string& symbole) { this->symbole = symbole; }
// Autres méthodes pourraient être définies ici selon les besoins