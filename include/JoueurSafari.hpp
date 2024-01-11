#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "Pion.hpp"
using namespace std;


class JoueurSafari {
public:
    JoueurSafari(string _symbole );

    
    int getId() const;
    string getSymbole() const ;
    void ajouterPion(const Pion& pion) ;
    const vector<Pion>& getPions() const ;

    static int nbJoueur = 1 ;
    
private:
    const int id;  
    const string symbole;
    vector<Pion> pions;

};

#endif // JOUEUR_H
