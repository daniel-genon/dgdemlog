#include "enrgconnexion.h"
#include <string.h>

/*
    Structure de données pour connexion
*/
EnrgConnexion::EnrgConnexion(){}
EnrgConnexion::EnrgConnexion( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr  ){Valeur( vnom, vcou, vtyp, vepr  );}
void EnrgConnexion::Valeur( const EnrgConnexion &autre ){	donneesligne = autre.Donnees();}
void EnrgConnexion::Valeur( const EnrgConnexion *autre ){	donneesligne = autre->Donnees();}
void EnrgConnexion::Valeur( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr  )
{
	donneesligne.epaisseur = vepr;
	donneesligne.typeligne = vtyp;
    memset( &donneesligne.couleur,0,TAILLECHAINECOULEUR );
	memcpy( &donneesligne.couleur.v, vcou.data(), vcou.size() );
	if(vnom.size()!=0)
		Nom( vnom );
}

void EnrgConnexion::Nom( const std::string &valeur)
{
    memset( &donneesligne.nom,0,TAILLECHAINENOM );
	memcpy( &donneesligne.nom.v, valeur.data(), valeur.size() );
}

std::string EnrgConnexion::Nom() const { return std::string((char*)&donneesligne.nom.v); }
std::string EnrgConnexion::Couleur() const { return std::string((char*)&donneesligne.couleur.v); }
ChaineNom EnrgConnexion::BNom() const { return donneesligne.nom; }
uint8_t EnrgConnexion::TypeLigne() const {	return donneesligne.typeligne; }
uint8_t EnrgConnexion::Epaisseur() const {	return donneesligne.epaisseur; }

DonneesLigne  EnrgConnexion::Donnees() const { return donneesligne; }

bool EnrgConnexion::EgaleA( const EnrgConnexion &autre )
{
	DonneesLigne test = autre.Donnees();
	return memcmp( &donneesligne, &test , sizeof(DonneesLigne)) == 0;
}
bool EnrgConnexion::EgaleA( EnrgConnexion *autre )
{
	DonneesLigne test = autre->Donnees();
	return memcmp( &donneesligne, &test , sizeof(DonneesLigne)) == 0;
}
void EnrgConnexion::CopierVersBloc( BlocConnexion &cible )
{
	memset(&cible,0,sizeof(BlocConnexion));
	cible.valeurligne = donneesligne;
}
void EnrgConnexion::CopierDepuisBloc( const BlocConnexion &source )
{
	memset(&donneesligne,0,sizeof(DonneesLigne));
	donneesligne = source.valeurligne;
}

void EnrgConnexion::Standard(){ Valeur( "liaison std", "rgb(0,0,0)", 1, 1.0 ); }


/*
    Liste d'enregistrement EnrgConnexion
*/

LstEnrgConnexion::LstEnrgConnexion(){}
LstEnrgConnexion::LstEnrgConnexion( ptrenrconnexion nouveau ){listepointeur.push_back(nouveau);}

LstEnrgConnexion::~LstEnrgConnexion()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
	listepointeur.clear();
}

void LstEnrgConnexion::Ajouter( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr  )
{
    ptrenrconnexion pnouveau = new EnrgConnexion( vnom, vcou, vtyp, vepr );
    listepointeur.push_back(pnouveau);
}

void LstEnrgConnexion::Ajouter( const BlocConnexion &source)
{
    ptrenrconnexion nouveau = new EnrgConnexion();
    listepointeur.push_back(nouveau);
    nouveau->CopierDepuisBloc(source);
}

void LstEnrgConnexion::CopierSimple( const LstEnrgConnexion &source)
{
    listepointeur.clear();
    for(uint32_t i=0;i<source.TailleListe();i++)
        listepointeur.push_back(source.Position(i));
}

void LstEnrgConnexion::Copier( const LstEnrgConnexion &source)
{
    listepointeur.clear();
    for(uint32_t i=0;i<source.TailleListe();i++)
    {
        ptrenrconnexion nouveau = new EnrgConnexion();
        listepointeur.push_back(nouveau);
        nouveau->Valeur( source.Position(i) );
    }
}

bool LstEnrgConnexion::EgaleA( const LstEnrgConnexion &autre )
{
    if(autre.TailleListe() != TailleListe()) return false;
    for(uint32_t i=0;i<autre.TailleListe();i++)
    {
        if(!autre.Position(i)->EgaleA(Position(i))) return false;
    }
    return true;
}

void LstEnrgConnexion::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
    listepointeur.clear();
}
bool LstEnrgConnexion::TrouverNom( const std::string &valeur, uint32_t &retindex )
{
	ChaineNom testnom, retnom; 
    memset(&testnom,0,TAILLECHAINENOM);
	memcpy( &testnom, valeur.data(), valeur.size());
	for( uint32_t i=0; i<TailleListe(); i++) 
	{
		retnom = listepointeur[i]->BNom(); 
		if( memcmp( &testnom, &retnom , TAILLECHAINENOM) == 0 )
		{
			retindex = i;
			return true;
		}
	}
	return false;
}
uint32_t LstEnrgConnexion::TailleListe() const
{
	return listepointeur.size();
}
ptrenrconnexion LstEnrgConnexion::Position(uint32_t nindex) const
{
	return listepointeur.at(nindex);
}

void LstEnrgConnexion::Standard()
{
	Nettoyer();
	Ajouter( "entre logiciel", "rgb(90,190,90)", 1, 2 );
	Ajouter( "fichier travail", "rgb(140,40,60)", 2, 2 );
	Ajouter( "fichier configuration", "rgb(30,30,170)", 3, 2 );
}

#ifdef OKGTKMMSTRINGLIST 
void LstEnrgConnexion::ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr )
{
	std::vector<Glib::ustring> lstphr;
	Glib::ustring	phrtmp;
	for(uint32_t i=0;i<TailleListe();i++)
	{
		phrtmp = listepointeur[i]->Nom();
		lstphr.push_back(phrtmp);
	}
	gtkliststr = Gtk::StringList::create(lstphr);
}
#endif /*OKGTKMMSTRINGLIST*/
