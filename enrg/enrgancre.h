#ifndef ENRGANCRE_H
#define ENRGANCRE_H

#include <gdkmm/pixbuf.h>
#include "enrgpolice.h"

class EnrgAncre
{
public:
    EnrgAncre();
    EnrgAncre( const std::string &vico,
              const std::string &vcofon,
              const BlocPolice &vpoli,
              uint8_t  vlar,
              uint8_t  vhau );

    void Valeur( const EnrgAncre &autre );
    void Valeur( const EnrgAncre *pautre );
    void Valeur(  const std::string &vico,
                  const std::string &vcofon,
                  const BlocPolice &vpoli,
                  uint8_t  vlar,
                  uint8_t  vhau );

	void Nom( const std::string &valeur);
    void Hauteur(  const uint16_t valeur );
    void Largeur(  const uint16_t valeur );
    void CouleurFond( const std::string &valeur);
    void Police( const BlocPolice &valeur );
    
	std::string Nom() const;
	ChaineGrandNom BNom() const;
    std::string CouleurFond() const;
    uint16_t  Hauteur() const;
    uint16_t  Largeur() const;
    BlocPolice Police() const;
    
	DonneesAncre Donnees() const;
	
    bool EgaleA( const EnrgAncre &autre );
    void CopierVersBloc( BlocAncre &cible );
    void CopierDepuisBloc( const BlocAncre &source );
    void Standard();

private:
	DonneesAncre donneesancre;

};

#endif // ENRGANCRE_H
