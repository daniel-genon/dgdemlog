#include "enrglogiciel.h"
#include <stdio.h>
#include <string.h>

/*
    Structure de données pour logiciel
*/
EnrgLogiciel::EnrgLogiciel(){}
EnrgLogiciel::EnrgLogiciel( const EnrgLogiciel &autre ){ Valeur( autre );}
EnrgLogiciel::EnrgLogiciel(const std::string &vnom,
              const std::string &vcla,
              const std::string &vopt,
              const std::string &vaid,
              const std::string &vdos,
              const std::string &vico,
              const std::string &vdep, uint16_t vdelai, uint8_t vuni , uint8_t vclas,
              const std::string &vstcfg, const std::string &vsttrv,
              const std::string &opcfg, const std::string &optrv  )
{
    Valeur(vnom,vcla,vopt,vaid,vdos,vico,vdep, vdelai, vuni, vclas, vstcfg, vsttrv, opcfg, optrv);
}

void EnrgLogiciel::Valeur( const EnrgLogiciel *pautre )
{
	contenu = pautre->Donnees();
}
void EnrgLogiciel::Valeur( const EnrgLogiciel &autre )
{
	contenu = autre.Donnees();
}
void EnrgLogiciel::Valeur(const std::string &vnom,
              const std::string &vcla,
              const std::string &vopt,
              const std::string &vaid,
              const std::string &vdos,
              const std::string &vico,
              const std::string &vdep,
              uint16_t  vdelai,
              uint8_t  vuni, uint8_t vclas,
              const std::string &vstcfg,
              const std::string &vsttrv ,
              const std::string &opcfg,
              const std::string &optrv)
{
    if(vcla.size()!=0) CvtChaineNom( vcla , &contenu.nomclair );
	CvtChaineNom( vnom , &contenu.nomprocessus );
	CvtChaineNom( opcfg , &contenu.optcfg );
	CvtChaineNom( optrv , &contenu.opttrv );
	CvtChaineNom( vopt , &contenu.options );
	CvtChaineGrandNom( vico , &contenu.imicone );
	CvtChaineGrandNom( vstcfg , &contenu.stdcfg );
	CvtChaineGrandNom( vsttrv , &contenu.stdtrv );
	CvtChaineGrandNom( vaid , &contenu.phraide );
	CvtChaineGrandNom( vdos , &contenu.dosproc );
	CvtChaineGrandNom( vdep , &contenu.dependance );
    contenu.delai	= vdelai;
    contenu.unique	= vuni;
    contenu.classe	= vclas;

}

void EnrgLogiciel::NomProcessus( const std::string &valeur){ CvtChaineNom( valeur , &contenu.nomprocessus ); }
void EnrgLogiciel::NomClair( const std::string&valeur){ CvtChaineNom( valeur , &contenu.nomclair ); }
void EnrgLogiciel::OptCFG( const std::string &valeur){ CvtChaineNom( valeur , &contenu.optcfg ); }
void EnrgLogiciel::OptTRV( const std::string &valeur){ CvtChaineNom( valeur , &contenu.opttrv ); }
void EnrgLogiciel::Options( const std::string &valeur){ CvtChaineNom( valeur , &contenu.options ); }

void EnrgLogiciel::Icone( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.imicone ); }
void EnrgLogiciel::StdCFG( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.stdcfg ); }
void EnrgLogiciel::StdTRV( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.stdtrv ); }
void EnrgLogiciel::Aide( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.phraide ); }
void EnrgLogiciel::Dossier( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.dosproc ); }
void EnrgLogiciel::Dependance( const std::string &valeur){ CvtChaineGrandNom( valeur , &contenu.dependance ); }

void EnrgLogiciel::Delai( uint16_t valeur) { contenu.delai  = valeur; }
void EnrgLogiciel::Unique( uint8_t valeur) { contenu.unique = valeur; }
void EnrgLogiciel::Classe( uint8_t valeur) { contenu.classe = valeur; }
void EnrgLogiciel::Unique( bool valeur) { if(valeur) contenu.unique=1; else contenu.unique=0; }

std::string EnrgLogiciel::NomProcessus() const	{ return std::string((char *)&contenu.nomprocessus.v); }
std::string EnrgLogiciel::NomClair() const		{ return std::string((char *)&contenu.nomclair.v); }
ChaineNom	EnrgLogiciel::BNomClair() const 	{ return contenu.nomclair; }
std::string EnrgLogiciel::Options() const		{ return std::string((char *)&contenu.options.v); }
std::string EnrgLogiciel::Aide() const			{ return std::string((char *)&contenu.phraide.v);}
std::string EnrgLogiciel::Dossier() const		{ return std::string((char *)&contenu.dosproc.v); }
std::string EnrgLogiciel::Icone() const			{ return std::string((char *)&contenu.imicone.v); }
std::string EnrgLogiciel::StdCFG() const		{ return std::string((char *)&contenu.stdcfg.v); }
std::string EnrgLogiciel::StdTRV() const		{ return std::string((char *)&contenu.stdtrv.v); }
std::string EnrgLogiciel::OptCFG() const		{ return std::string((char *)&contenu.optcfg.v); }
std::string EnrgLogiciel::OptTRV() const		{ return std::string((char *)&contenu.opttrv.v); }
std::string EnrgLogiciel::Dependance() const	{ return std::string((char *)&contenu.dependance.v); }

uint16_t  EnrgLogiciel::Delai() const { return contenu.delai; }
uint8_t  EnrgLogiciel::Unique() const { return contenu.unique; }
uint8_t  EnrgLogiciel::Classe() const { return contenu.classe; }
bool    EnrgLogiciel::UniqueB() { return contenu.unique==1; }

DonneesLogiciel EnrgLogiciel::Donnees() const {	return contenu;	}

bool EnrgLogiciel::EgaleA( const EnrgLogiciel &autre )
{
    DonneesLogiciel tmpdon = autre.Donnees();
    return memcmp( &contenu, &tmpdon , sizeof(DonneesLogiciel)) == 0;
}

bool EnrgLogiciel::EgaleA( const EnrgLogiciel *autre, bool testnom )
{
    DonneesLogiciel tmpdon = autre->Donnees();
    return memcmp( &contenu, &tmpdon , sizeof(DonneesLogiciel)) == 0;
}

void EnrgLogiciel::CopierVersBloc( BlocLogiciel &cible ) { cible.donnees = contenu; }
void EnrgLogiciel::CopierDepuisBloc( const BlocLogiciel &source ) { contenu = source.donnees; }

void EnrgLogiciel::CvtChaineNom( const std::string &valeur , void *memdestinataire )
{
    memset( memdestinataire,0,TAILLECHAINENOM);
	memcpy( memdestinataire, valeur.data(), valeur.size());
}
void EnrgLogiciel::CvtChaineGrandNom( const std::string &valeur , void *memdestinataire )
{
    memset( memdestinataire,0,TAILLEGRANDECHAINE);
	memcpy( memdestinataire, valeur.data(), valeur.size());
}

//    Liste d'enregistrement EnrgLogiciel


LstEnrgLogiciel::LstEnrgLogiciel(){}
LstEnrgLogiciel::~LstEnrgLogiciel(){ Nettoyer(); }
LstEnrgLogiciel::LstEnrgLogiciel( ptrenrglogiciel nouveau ){listepointeur.push_back(nouveau);}
void LstEnrgLogiciel::Ajouter(const std::string &vnom,
              const std::string &vcla,
              const std::string &vopt,
              const std::string &vaid,
              const std::string &vdos,
              const std::string &vico,
              const std::string &vdep,
              uint16_t vdelai, uint8_t vuni, uint8_t vclas,
              const std::string &vstcfg, const std::string &vsttrv,
              const std::string &opcfg, const std::string &optrv )
{
    ptrenrglogiciel pnouveau = new EnrgLogiciel(vnom,vcla,vopt,vaid,vdos,vico,vdep,vdelai,vuni,vclas,vstcfg,vsttrv,opcfg,optrv);
    listepointeur.push_back(pnouveau);
}
void LstEnrgLogiciel::Ajouter( const BlocLogiciel &source)
{
    ptrenrglogiciel nouveau = new EnrgLogiciel();
    listepointeur.push_back(nouveau);
    nouveau->CopierDepuisBloc(source);
}
void LstEnrgLogiciel::CopierSimple( const LstEnrgLogiciel &source)
{
    listepointeur.clear();
    for(unsigned long i=0;i<source.TailleListe();i++)
        listepointeur.push_back(source.Position(i));
}
void LstEnrgLogiciel::Copier(const LstEnrgLogiciel &source)
{
	Nettoyer();
    for(unsigned long i=0;i<source.TailleListe();i++)
    {
        ptrenrglogiciel nouveau = new EnrgLogiciel();
        listepointeur.push_back(nouveau);
        nouveau->Valeur(source.Position(i));
    }
}
void LstEnrgLogiciel::Copier(const LstEnrgLogiciel *source)
{
    Nettoyer();
    for( unsigned long i=0;i<source->TailleListe();i++)
    {
        ptrenrglogiciel nouveau = new EnrgLogiciel();
        listepointeur.push_back(nouveau);
        nouveau->Valeur(source->Position(i));
    }
}
bool LstEnrgLogiciel::EgaleA(const LstEnrgLogiciel &autre , bool testnom)
{
    if(autre.TailleListe() != TailleListe()) return false;
    for(unsigned long i=0;i<autre.TailleListe();i++)
    {
        if(!autre.Position(i)->EgaleA(Position(i),testnom)) return false;
    }
    return true;
}
void LstEnrgLogiciel::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
    listepointeur.clear();
}
void LstEnrgLogiciel::Supprimer( uint32_t nindex )
{
	if( nindex < listepointeur.size() )
	{
		ctmp = listepointeur.begin()+nindex;
		delete listepointeur.at(nindex);
		listepointeur.erase(ctmp);
	}
}
uint32_t LstEnrgLogiciel::TailleListe() const { return listepointeur.size(); }
ptrenrglogiciel LstEnrgLogiciel::Position(uint32_t nindex) const {	return listepointeur.at(nindex); }
bool LstEnrgLogiciel::TrouverNom( const std::string &valeur, uint32_t &retindex )
{
	ChaineNom testnom, retnom; 
    memset(&testnom,0,TAILLECHAINENOM);
	memcpy( &testnom, valeur.data(), valeur.size());
	for( uint32_t i=0; i<TailleListe(); i++) 
	{
		retnom = listepointeur[i]->BNomClair(); 
		if( memcmp( &testnom, &retnom , TAILLECHAINENOM) == 0 )
		{
			retindex = i;
			return true;
		}
	}
	return false;
}
ptrenrglogiciel LstEnrgLogiciel::FinDeListe() const { return listepointeur.back(); }
ptrenrglogiciel LstEnrgLogiciel::DebutDeListe() const { return listepointeur.front(); }
void LstEnrgLogiciel::Standard()
{
	Nettoyer();
//    Ajouter("fermerauto","Quitter automatiquement","","Fermer dgdemlog après le lancement du contexte","~/MultiApp/","icone/autoquitter.png","",10,1,1,"","","","");
}
#ifdef OKGTKMMSTRINGLIST 
void LstEnrgLogiciel::ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr )
{
	std::vector<Glib::ustring> lstphr;
	Glib::ustring	phrtmp;
	for( uint32_t i=0;i<TailleListe();i++)
	{
		phrtmp = listepointeur[i]->NomClair();
		lstphr.push_back(phrtmp);
	}
	gtkliststr = Gtk::StringList::create(lstphr);
}
#endif /*OKGTKMMSTRINGLIST*/

