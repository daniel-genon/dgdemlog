#ifndef ENRGCONFIG_H
#define ENRGCONFIG_H

//#include "../source/structureappli.h"
#include "enrgpolice.h"

class EnrgConfig
{
public:
    EnrgConfig();
    EnrgConfig( const std::string &vnom,
				const std::string &vcogra,
				const std::string &vcomen,
			   const BlocPolice &vpoli,
			   unsigned char vhidrt,
			   unsigned char vhigah,
			   unsigned char vhidso );

void Valeur( const std::string &vnom,
			   const std::string &vcogra,
			   const std::string &vcomen,
               const BlocPolice &vpoli,
               unsigned char vhidrt,
               unsigned char vhigah,
               unsigned char vhidso );

    void Valeur( const EnrgConfig &autre );
    void Valeur( const EnrgConfig *pautre );

    void Nom( const std::string &valeur);
    void CouleurGraphique( const std::string &valeur);
    void CouleurMenu( const std::string &valeur);
    void CouleurGraphique( const ChaineCouleur &valeur);
    void CouleurMenu( const ChaineCouleur &valeur);
    void IconeGestion( uint8_t valeur );
    void IconeSymbole(uint8_t valeur );
    void IconeDessus( uint8_t valeur );
    void Icones( uint8_t vdeo, uint8_t vdrt, uint8_t vgah );
    void Police( const BlocPolice &valeur );


    std::string Nom() const;
	ChaineNom BNom() const;
	std::string CouleurGraphique() const;
    std::string CouleurMenu() const;

    uint8_t  IconeGestion() const;
    uint8_t  IconeSymbole() const;
    uint8_t  IconeDessus() const;
    BlocPolice Police() const;
    BlocPolice *PPolice();
    DonneesConfig Donnees() const;

    ChaineCouleur *PCouleurGraphique();
    ChaineCouleur *PCouleurMenu();

    bool EgaleA(const EnrgConfig &autre , bool testnom=true);
    void CopierDepuisBloc( const BlocConfig &source );
    void CopierVersBloc( BlocConfig &cible );
    void Standard();

private:
	DonneesConfig	contenu;
//	EnrgPolice	police;
};

#endif // ENRGCONFIG_H
