#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "Pion.hpp"
using namespace std;


class JoueurSafari {
public:
    JoueurSafari(int _id , string _symbole );

    
    int getId() const;
    string getSymbole() const ;
    void ajouterPion(Pion* pion) ;
    const vector<Pion>& getPions() const ;

    static int nbJoueur ;
    
private:
    int id;  
    string symbole;
    vector<Pion> pions;

};

#endif // JOUEUR_H
