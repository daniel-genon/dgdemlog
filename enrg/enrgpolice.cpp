#include "enrgpolice.h"
#include <gtkmm/fontchooser.h>
#include <stdio.h>
#include <string.h>
#include "../bloc/utilficbinbloc.h"
/*
    Structure de données pour police de caractères
*/
EnrgPolice::EnrgPolice(){}
//EnrgPolice::EnrgPolice( const BlocPolice &valeurs ){	contenu = valeurs;}
EnrgPolice::EnrgPolice( const std::string &vnom, const std::string &vcoul ){Valeur( vnom, vcoul );}
EnrgPolice::EnrgPolice( const BlocPolice &source )
{
    contenu.nom  =		source.nom;
    contenu.couleur =	source.couleur;
	contenu.hauteur =	source.hauteur;
}

void EnrgPolice::Valeur( const std::string &vnom, const std::string &vcoul )
{
    if(vnom.size()!=0)
    {
		Nom( vnom );
		contenu.hauteur = Hauteur();
	}
	Couleur( vcoul );
}

void EnrgPolice::Valeur( const EnrgPolice &autre )
{
	Valeur( autre.Nom(), autre.Couleur() );
}
void EnrgPolice::Valeur( const BlocPolice &autre )
{
    contenu = autre;
}

//void EnrgPolice::Nom( const std::string &vnom ){ contenu.nom  = vnom;}
void EnrgPolice::Nom( const std::string &valeur)
{
    memset(&contenu.nom,0,TAILLEGRANDECHAINE);
	memcpy( &contenu.nom.v, valeur.data(), valeur.size());
}

void EnrgPolice::Couleur( const std::string &valeur)
{
    memset(&contenu.couleur,0,TAILLECHAINECOULEUR);
	memcpy( &contenu.couleur.v, valeur.data(), valeur.size());
}
std::string EnrgPolice::Nom() const
{
	return std::string((char *)&contenu.nom.v);
}
std::string EnrgPolice::Couleur() const
{
	return std::string((char *)&contenu.couleur.v);
}
ChaineCouleur EnrgPolice::BCouleur() const {    return contenu.couleur;}
ChaineGrandNom EnrgPolice::BNom() const {    return contenu.nom; }

int16_t	EnrgPolice::Hauteur() const
{
	std::string test = Nom();
	std::size_t dep = test.find_last_of(' ');
	std::string reste = test.substr( dep );
	return (int16_t)std::stoi( reste );
}
BlocPolice EnrgPolice::Police() const {	return contenu;}
BlocPolice *EnrgPolice::PPolice(){    return &contenu;}


bool EnrgPolice::EgaleA( const EnrgPolice &autre )
{
	BlocPolice test = autre.Police();
    return memcmp( &contenu, &test , sizeof(BlocPolice) ) == 0 ;
    //ChainBlocPolice vnom = autre.BNom();
    //if( memcmp( &contenu.nom.v, &vnom , TAILLEGRANDECHAINE) !=0 ) return false;
    //ChaineCouleur valeur = autre.BCouleur();
    //return memcmp( &contenu.couleur.v, &valeur , TAILLECHAINECOULEUR) == 0 ;
}

void EnrgPolice::CopierVersBloc( BlocPolice &cible )
{
	cible.hauteur =	contenu.hauteur;
	cible.nom =	contenu.nom;
    cible.couleur = contenu.couleur;
}
void EnrgPolice::CopierDepuisBloc( const BlocPolice &source )
{
    contenu.nom  =		source.nom;
    contenu.couleur =	source.couleur;
	contenu.hauteur =	source.hauteur;
}

