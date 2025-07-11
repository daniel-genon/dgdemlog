#include "enrggraph.h"
#include <stdio.h>
#include <string.h>

EnrgGraph::EnrgGraph(){}
EnrgGraph::EnrgGraph(const std::string &vnom,
           const std::string &vcf,
           const std::string &vcb,
           const BlocPolice &vpol,
           uint16_t vlar, uint16_t vhau, uint8_t vprio)
{
    Valeur( vnom, vcf, vcb, vpol,vlar, vhau, vprio) ;
}

void EnrgGraph::Valeur( const std::string &vnom,
                   const std::string &vcf,
                   const std::string &vcb,
                   const BlocPolice &vpol,
                   uint16_t vlar, uint16_t vhau, uint8_t vprio )
{
    if(vnom.size()!=0)
        Nom( vnom );
    DimSymbole( vhau, vlar );
    ValeurPriorite(vprio);
    CouleurFond(vcf);
    CouleurBandeau( vcb );
	contenu.symbole.surface.police = vpol;
}

void EnrgGraph::Valeur( const EnrgGraph &autre )
{
    Nom(autre.Nom());
    CouleurFond(autre.CouleurFond());
    CouleurBandeau( autre.CouleurBandeau());
    Hauteur(autre.Hauteur());
    Largeur(autre.Largeur());
    ValeurPriorite( autre.ValeurPriorite() );
    contenu.symbole.surface.police = autre.Police();
}

void EnrgGraph::Valeur( const EnrgGraph *autre )
{
	contenu = autre->Donnees();
}

void EnrgGraph::Nom( const std::string &valeur)
{
    memset(&contenu.libelle,0,TAILLECHAINENOM);
	memcpy( &contenu.libelle.v, valeur.data(), valeur.size());
}
void EnrgGraph::DimSymbole( const uint16_t htr, const uint16_t lgr )
{
	Hauteur(htr);
	Largeur(lgr);
}
void EnrgGraph::Hauteur( const uint16_t valeur ){	contenu.symbole.dimension.hauteur = valeur; }
void EnrgGraph::Largeur( const  uint16_t valeur ){ contenu.symbole.dimension.largeur = valeur; }
void EnrgGraph::ValeurPriorite( const uint8_t valeur ){ contenu.idxpriorite = valeur;}
void EnrgGraph::CouleurFond( const std::string &valeur)
{
    memset( &contenu.symbole.surface.couleur.coulfond,0,TAILLECHAINECOULEUR );
	memcpy( &contenu.symbole.surface.couleur.coulfond.v, valeur.data(), valeur.size() );
}
void EnrgGraph::CouleurBandeau( const std::string &valeur)
{
    memset( &contenu.symbole.surface.couleur.coulbandeau,0,TAILLECHAINECOULEUR );
	memcpy( &contenu.symbole.surface.couleur.coulbandeau.v, valeur.data(), valeur.size() );
}

void EnrgGraph::Police( const BlocPolice &valeur ) {	contenu.symbole.surface.police = valeur; }

DonneesGraphe EnrgGraph::Donnees() const {	return contenu;	}

std::string EnrgGraph::Nom() const { return std::string((char*)&contenu.libelle.v); }
ChaineNom EnrgGraph::BNom() const { return contenu.libelle; }
std::string EnrgGraph::CouleurFond() const { return std::string((char*)&contenu.symbole.surface.couleur.coulfond.v); }
std::string EnrgGraph::CouleurBandeau() const{ return std::string((char*)&contenu.symbole.surface.couleur.coulbandeau.v); }
uint16_t  EnrgGraph::Hauteur() const {return contenu.symbole.dimension.hauteur;}
uint16_t  EnrgGraph::Largeur() const {return contenu.symbole.dimension.largeur;}
uint8_t  EnrgGraph::ValeurPriorite() const { return contenu.idxpriorite; }
BlocPolice EnrgGraph::Police() const { return contenu.symbole.surface.police; }

//BlocPolice *EnrgGraph::PPolice(){    return &contenu.surface.police;}
//std::string *EnrgGraph::PtrCouleurFond(){return &coulfond;}
//std::string *EnrgGraph::PtrCouleurBandeau(){return &coulband;}

bool EnrgGraph::EgaleA( const EnrgGraph &autre )
{
	DonneesGraphe test = autre.Donnees();
	return memcmp( &contenu, &test , sizeof(DonneesGraphe)) == 0;
}
bool EnrgGraph::EgaleA( EnrgGraph *autre )
{
	DonneesGraphe test = autre->Donnees();
	return memcmp( &contenu, &test , sizeof(DonneesGraphe)) == 0;
}

void EnrgGraph::CopierVersBloc( BlocGraphLog &cible )
{
	memset(&cible,0,sizeof(BlocGraphLog));
	cible.donnees = contenu;
}

void EnrgGraph::CopierDepuisBloc( const BlocGraphLog &source )
{
	memset(&contenu,0,sizeof(DonneesGraphe));
	contenu = source.donnees;
}


/*
    Liste d'enregistrement EnrgGraph
*/

LstEnrgGraph::LstEnrgGraph(){}
LstEnrgGraph::LstEnrgGraph( ptrenrgraphique nouveau ){listepointeur.push_back(nouveau);}

LstEnrgGraph::~LstEnrgGraph()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
	listepointeur.clear();
}

void LstEnrgGraph::Ajouter( const std::string &vnom,
                            const std::string &vcf,
                            const std::string &vcb,
                            const BlocPolice &vpol,
                            uint16_t vlar, uint16_t vhau, uint8_t vprio  )
{
    ptrenrgraphique pnouveau = new EnrgGraph( vnom,vcf,vcb,vpol,vlar,vhau,vprio );
    listepointeur.push_back(pnouveau);
}

void LstEnrgGraph::Ajouter( const BlocGraphLog &source)
{
    ptrenrgraphique nouveau = new EnrgGraph();
    listepointeur.push_back(nouveau);
    nouveau->CopierDepuisBloc(source);
}

//void LstEnrgGraph::CopierSimple( const LstEnrgGraph *source)
//{
//    clear();
//    for(int i=0;i<source->length();i++)
//        append(source->at(i));
//}
void LstEnrgGraph::CopierSimple( const LstEnrgGraph &source)
{
    listepointeur.clear();
    for(uint32_t i=0;i<source.TailleListe();i++)
        listepointeur.push_back(source.Position(i));
}

//void LstEnrgGraph::Copier( const LstEnrgGraph *source)
//{
//    clear();
//    for(int i=0;i<source->length();i++)
//    {
//        ptrenrgraphique nouveau = new EnrgGraph();
//        append(nouveau);
//        nouveau->Valeur(source->at(i));
//    }
//}
void LstEnrgGraph::Copier( const LstEnrgGraph &source)
{
    listepointeur.clear();
    for(uint32_t i=0;i<source.TailleListe();i++)
    {
        ptrenrgraphique nouveau = new EnrgGraph();
        listepointeur.push_back(nouveau);
        nouveau->Valeur(source.Position(i));
    }
}

bool LstEnrgGraph::EgaleA( const LstEnrgGraph &autre )
{
    if(autre.TailleListe() != TailleListe()) return false;
    for(uint32_t i=0;i<autre.TailleListe();i++)
    {
        if(!autre.Position(i)->EgaleA(Position(i))) return false;
    }
    return true;
}

void LstEnrgGraph::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
    listepointeur.clear();
}
void LstEnrgGraph::Supprimer( uint32_t nindex )
{
	if( nindex < listepointeur.size() )
	{
		ctmp = listepointeur.begin()+nindex;
		delete listepointeur.at(nindex);
		listepointeur.erase(ctmp);
	}
}
uint32_t LstEnrgGraph::TailleListe() const
{
	return listepointeur.size();
}
ptrenrgraphique LstEnrgGraph::Position(uint32_t nindex) const
{
	return listepointeur.at(nindex);
}

bool LstEnrgGraph::TrouverNom( const std::string &valeur, uint32_t &retindex )
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



void LstEnrgGraph::Standard(){}

#ifdef OKGTKMMSTRINGLIST 
void LstEnrgGraph::ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr )
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


//    Liste d'enregistrement pour graphique logiciel

LstEnrgGrLog::LstEnrgGrLog(){}

void LstEnrgGrLog::Standard()
{
	Nettoyer();
    EnrgPolice policetmp("DejaVu Sans Mono 8","rgb(0,0,0)");
    Ajouter("final contexte","rgb(115,45,45)","rgb(215,125,80)",policetmp.Police(),170,40,0);
    Ajouter("immédiat","rgb(137,251,250)","rgb(255,255,0)",policetmp.Police(),160,50,254);
    Ajouter("normal","rgb(251,174,54)","rgb(255,255,0)",policetmp.Police(),150,50,126);
    Ajouter("finale","rgb(235,113,132)","rgb(255,255,0)",policetmp.Police(),140,50,1);
}

//    Liste d'enregistrement pour graphique fichier lié

LstEnrgGrFic::LstEnrgGrFic(){}

void LstEnrgGrFic::Standard()
{
	Nettoyer();
    EnrgPolice policetmp("DejaVu Sans Mono 8","rgb(0,0,0)");
    Ajouter("configuration","rgb(137,251,250)","rgb(255,255,0)",policetmp.Police(),180,50,0);
    Ajouter("fichier travail","rgb(251,174,54)","rgb(255,255,0)",policetmp.Police(),210,60,0);
}
