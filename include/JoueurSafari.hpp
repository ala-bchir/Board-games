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
    
    
private:
    int id;  
    string symbole;
    
};

#endif // JOUEUR_H
