#ifndef DAMIER_HPP
#define DAMIER_HPP

#include <vector>
using namespace std;

class Damier{
private: 
    int taille;
    /*Tableau de char à deux dimensions*/
    vector<vector<char>> grille;
public:
    Damier(int taille);
    void afficher() const;
    void setCellule(int x, int y, char valeur);
    char getCellule(int x, int y) const;
    int getTaille() const;
    bool CoordonneesValides(int x, int y) const;
};





#endif // DAMIER_HPP