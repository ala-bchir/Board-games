// pion.hpp

#ifndef Pion_HPP
#define Pion_HPP

class Pion {
private:
    int x, y; // Positions de la pièce sur le damier
    char symbole; // Symbole représentant la pièce

public:
    Pion(int x, int y, char symbole);
    // Accesseurs et mutateurs
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    char getSymbole() const;
    void setSymbole(char symbole);


};

#endif // Pion_HPP
