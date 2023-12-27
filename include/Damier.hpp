#ifndef DAMIER_HPP
#define DAMIER_HPP

#include <vector>
#include <string>
using namespace std;

class Damier{
protected: 
    int taille;
    /*Tableau de char à deux dimensions*/
    std::vector<vector<string>> grille;
public:
    Damier(int taille);
    void afficher() const;
    void setCellule(int x, int y, const std::string& valeur);
    string getCellule(int x, int y) const;
    int getTaille() const;
    bool CoordonneesValides(int x, int y) const;

};




#endif // DAMIER_HPP