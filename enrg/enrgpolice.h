#ifndef ENRGPOLICE_H
#define ENRGPOLICE_H

#include "../source/structureappli.h"

class EnrgPolice
{
public:

    EnrgPolice();
//    EnrgPolice( const BlocPolice &valeurs );
    EnrgPolice( const BlocPolice &source );
    EnrgPolice( const std::string &vnom, const std::string &vcoul );

    void Valeur( const EnrgPolice &autre );
    void Valeur( const std::string &vnom, const std::string &vcoul );
    void Valeur( const BlocPolice &autre );
 
    void Couleur( const std::string &valeur);
    void Nom( const std::string &valeur );
    
    BlocPolice Police() const;
    BlocPolice *PPolice();

    std::string Nom() const;
    std::string Couleur() const;
	int16_t		Hauteur() const;
    ChaineGrandNom	BNom() const;
    ChaineCouleur 	BCouleur() const;
	

    bool EgaleA( const EnrgPolice &autre );

    void CopierVersBloc( BlocPolice &cible );
    void CopierDepuisBloc( const BlocPolice &source );

private:
	BlocPolice contenu;
};

#endif // ENRGPOLICE_H
