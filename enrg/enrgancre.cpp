#include "enrgancre.h"

/*
    Structure de données pour graphique ancre
*/

EnrgAncre::EnrgAncre(){}
EnrgAncre::EnrgAncre( const std::string &vico,
          const std::string &vcofon,
          const BlocPolice &vpoli,
          uint8_t  vlar,
          uint8_t  vhau )
{    Valeur( vico, vcofon, vpoli, vlar, vhau );}
void EnrgAncre::Valeur( const EnrgAncre &autre )
{
	DonneesAncre tmp = autre.Donnees();
	donneesancre = tmp;
}
void EnrgAncre::Valeur( const EnrgAncre *pautre )
{
	DonneesAncre tmp = pautre->Donnees();
	donneesancre = tmp;
}
void EnrgAncre::Valeur(  const std::string &vico,
              const std::string &vcofon,
              const BlocPolice &vpoli,
              uint8_t  vlar,
              uint8_t  vhau )
{
    if(vico.size()!=0)
        Nom( vico );
	memset( &donneesancre.symbole,0,sizeof(BlocSymbole));	
	donneesancre.symbole.dimension.hauteur = vhau;
	donneesancre.symbole.dimension.largeur = vlar;
	memcpy( &donneesancre.symbole.surface.couleur.coulbandeau.v, vcofon.data(),  vcofon.size() );
	memcpy( &donneesancre.symbole.surface.couleur.coulfond.v, vcofon.data(), vcofon.size() );
	memcpy( &donneesancre.symbole.surface.police, &vpoli, sizeof(BlocPolice) );
}
void EnrgAncre::Nom( const std::string &valeur)
{
    memset(&donneesancre.imicone,0,TAILLEGRANDECHAINE);
	memcpy( &donneesancre.imicone.v, valeur.data(), valeur.size());
}
ChaineGrandNom EnrgAncre::BNom() const {  return donneesancre.imicone; }
std::string EnrgAncre::Nom() const { return std::string((char*)&donneesancre.imicone.v); }


void EnrgAncre::Hauteur(  const uint16_t valeur )
{
	donneesancre.symbole.dimension.hauteur = valeur;
}
void EnrgAncre::Largeur(  const uint16_t valeur )
{
	donneesancre.symbole.dimension.largeur = valeur;
}

void EnrgAncre::CouleurFond( const std::string &valeur)
{
    memset( &donneesancre.symbole.surface.couleur,0,sizeof(BlocCouleurs) );
	memcpy( &donneesancre.symbole.surface.couleur.coulfond.v, valeur.data(), valeur.size() );
}
void EnrgAncre::Police( const BlocPolice &valeur ) {	donneesancre.symbole.surface.police = valeur; }
std::string EnrgAncre::CouleurFond() const { return std::string((char*)&donneesancre.symbole.surface.couleur.coulfond.v); }
uint16_t  EnrgAncre::Hauteur() const {return donneesancre.symbole.dimension.hauteur;}
uint16_t  EnrgAncre::Largeur() const {return donneesancre.symbole.dimension.largeur;}
BlocPolice EnrgAncre::Police() const { return donneesancre.symbole.surface.police; }

DonneesAncre EnrgAncre::Donnees() const {	return donneesancre;	}

bool EnrgAncre::EgaleA(const EnrgAncre &autre )
{
    DonneesAncre test = autre.Donnees();
    return ( memcmp( &donneesancre, &test , sizeof(DonneesAncre) ) ==0 );
}
void EnrgAncre::CopierVersBloc( BlocAncre &cible )
{
	memset(&cible,0,sizeof(BlocAncre));
	cible.donnees = donneesancre;
}
void EnrgAncre::CopierDepuisBloc( const BlocAncre &source )
{
	memset(&donneesancre,0,sizeof(DonneesAncre));
	donneesancre = source.donnees;
}
void EnrgAncre::Standard()
{
	std::string nomico("/icone/attache.png");
	Glib::RefPtr<Gdk::Pixbuf> icotest = Gdk::Pixbuf::create_from_resource(nomico);
	EnrgPolice tmpol( "DejaVu Sans Mono 4" , "rgb(0,0,0)" );
	Valeur( nomico, "rgb(186,221,242)", tmpol.Police(), icotest->get_width(), icotest->get_height() );
}
