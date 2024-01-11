#ifndef Pion_HPP
#define Pion_HPP
#include <string>

class Pion {
private:
    int x, y; // Positions de la pièce sur le damier
    std::string symbole; // Symbole représentant la pièce
public:
    Pion(int x, int y, const std::string& symbole);
    // Accesseurs
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    std::string getSymbole() const;
    void setSymbole(const std::string& symbole);
};

#endif 