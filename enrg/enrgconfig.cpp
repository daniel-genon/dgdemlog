#include "enrgconfig.h"
#include <stdio.h>
#include <string.h>

/*
    Structure de données pour config generale
*/

EnrgConfig::EnrgConfig(){}
EnrgConfig::EnrgConfig( const std::string &vnom,
				   const std::string &vcogra,
				   const std::string &vcomen,
                   const BlocPolice &vpoli,
                   uint8_t vhidrt,
                   uint8_t vhigah,
                   uint8_t vhidso )
{
    Valeur( vnom, vcogra, vcomen, vpoli, vhidrt, vhigah, vhidso );
}

void EnrgConfig::Valeur( const std::string &vnom,
           const std::string &vcogra,
           const std::string &vcomen,
           const BlocPolice &vpoli,
           uint8_t vhidrt,
           uint8_t vhigah,
           uint8_t vhidso )
{
    Nom( vnom );
    CouleurGraphique( vcogra );
    CouleurMenu( vcomen );
    contenu.police = vpoli;
    Icones( vhidso, vhidrt, vhigah );
}

void EnrgConfig::Valeur( const EnrgConfig &autre )
{
    Nom( autre.Nom() );
    CouleurGraphique( autre.CouleurGraphique());
    CouleurMenu( autre.CouleurMenu() );
    Icones( autre.IconeDessus(), autre.IconeGestion(), autre.IconeSymbole() );
    contenu.police = autre.Police();
}
void EnrgConfig::Valeur( const EnrgConfig *pautre )
{
    Nom( pautre->Nom() );
    CouleurGraphique( pautre->CouleurGraphique());
    CouleurMenu( pautre->CouleurMenu() );
    Icones( pautre->IconeDessus(), pautre->IconeGestion(), pautre->IconeSymbole() );
    contenu.police = pautre->Police();
}

void EnrgConfig::Nom( const std::string &valeur)
{
    memset(&contenu.nom,0,TAILLECHAINENOM);
	memcpy( &contenu.nom, valeur.data(), valeur.size());
}
void EnrgConfig::CouleurGraphique( const std::string &valeur)
{
    memset(&contenu.couleurs.coulfond,0,TAILLECHAINECOULEUR);
	memcpy( &contenu.couleurs.coulfond, valeur.data(), valeur.size());
}
void EnrgConfig::CouleurMenu( const std::string &valeur)
{
    memset(&contenu.couleurs.coulbandeau,0,TAILLECHAINECOULEUR);
	memcpy( &contenu.couleurs.coulbandeau, valeur.data(), valeur.size());
}
void EnrgConfig::CouleurGraphique( const ChaineCouleur &valeur){ contenu.couleurs.coulfond = valeur;}
void EnrgConfig::CouleurMenu( const ChaineCouleur &valeur){ contenu.couleurs.coulbandeau = valeur;}
void EnrgConfig::IconeGestion( uint8_t valeur ){ contenu.hticodroite = valeur;}
void EnrgConfig::IconeSymbole(uint8_t valeur ){ contenu.hticogauche = valeur;}
void EnrgConfig::IconeDessus( uint8_t valeur ){contenu.hticodessus = valeur;}
void EnrgConfig::Icones( uint8_t vdeo, uint8_t vdrt, uint8_t vgah )
{
    contenu.hticodessus = vdeo;
    contenu.hticodroite = vdrt;
    contenu.hticogauche = vgah;
}
void EnrgConfig::Police( const BlocPolice &valeur ){ contenu.police = valeur; }

std::string EnrgConfig::Nom() const {	return std::string((char *)&contenu.nom.v); }
ChaineNom EnrgConfig::BNom() const {	return contenu.nom; }
std::string EnrgConfig::CouleurGraphique() const {	return std::string((char *)&contenu.couleurs.coulfond.v); }
std::string EnrgConfig::CouleurMenu() const {	return std::string((char *)&contenu.couleurs.coulbandeau.v); }

DonneesConfig EnrgConfig::Donnees() const {	return contenu;	}

uint8_t  EnrgConfig::IconeGestion() const{ return contenu.hticodroite; }
uint8_t  EnrgConfig::IconeSymbole() const{ return contenu.hticogauche; }
uint8_t  EnrgConfig::IconeDessus() const{ return contenu.hticodessus; }

BlocPolice EnrgConfig::Police() const{    return contenu.police;}
BlocPolice *EnrgConfig::PPolice(){    return &contenu.police;	}

ChaineCouleur *EnrgConfig::PCouleurGraphique(){return &contenu.couleurs.coulfond;}
ChaineCouleur *EnrgConfig::PCouleurMenu(){return &contenu.couleurs.coulbandeau;}

bool EnrgConfig::EgaleA( const EnrgConfig &autre, bool testnom )
{
    DonneesConfig tmpdon = autre.Donnees();
    if(testnom)
    {
		if(memcmp( &contenu.nom, &tmpdon.nom , sizeof(ChaineNom)) != 0) return false;
	}
    return memcmp( &contenu, &tmpdon , sizeof(DonneesConfig)) == 0;
}
void EnrgConfig::CopierVersBloc( BlocConfig &cible )
{
    memset(&cible,0,sizeof(cible));
    cible.donnees = contenu;
}
void EnrgConfig::CopierDepuisBloc( const BlocConfig &source ) {	contenu = source.donnees; }

void EnrgConfig::Standard()
{
    EnrgPolice	tmppolice("DejaVu Sans Mono 10","rgb(0,0,0)");
    Valeur( "STANDARD", "rgb(60,100,131)", "rgb(59,59,59)", tmppolice.Police(), 40, 20, 20 );
}
