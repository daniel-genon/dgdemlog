/*
*/
#include "zonegraphique.h"
ZoneGraphique::ZoneGraphique()
{
	dimLzone = 730;
	dimHzone = 600;
	set_content_width(dimLzone);
	set_content_height(dimHzone);
	NettoyerSelection();
    set_draw_func(sigc::mem_fun(*this, &ZoneGraphique::Dessiner));    
}
ZoneGraphique::~ZoneGraphique()
{
	Nettoyer();
}
void ZoneGraphique::AjouterElement( GraphiqueSurface *pvaleur )
{
	lstgraphe.push_back(pvaleur);
	queue_draw();
}
void  ZoneGraphique::ActualiserGraphe( GraphiqueSurface *pvaleur )
{
	pvaleur->RetracerGraphique();
	queue_draw();
}
void ZoneGraphique::Dessiner(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
/**
 * symbole témoin en 0,0 de la zone		
**/	
//	cr->set_line_width(2.0);
//	cr->arc(0.0, 0.0, 10.0, 0.0, 2 * M_PI);
//***************
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
		lstgraphe[i]->ReDessiner(cr);
}
bool ZoneGraphique::CollecterGenreObjet( const uint16_t valgenre, std::vector<GraphiqueSurface*> &retlst )
{
	retlst.clear();
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
	{
		if( lstgraphe[i]->GenreElement() == valgenre )
		{
			retlst.push_back(lstgraphe[i]);
		}
	}
	return retlst.size() != 0;
}
GraphiqueSurface* ZoneGraphique::CollecterGenreObjet( const uint16_t valgenre )
{
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
	{
		if( lstgraphe[i]->GenreElement() == valgenre )
			return lstgraphe[i];
	}
	return nullptr;
}
void ZoneGraphique::AppuyerSouris(int n_press, double x, double y){ TesterObjet(x,y); }
void ZoneGraphique::LacherSouris(int n_press, double x, double y)
{
	if(ElementStocke())
	{
		if(graphestocke->GenreElement()==1000)
		{
			GraphiqueSurface *objetsource = graphestocke->ObjetConnecter();
			Supprimer( graphestocke );
			GraphiqueSurface *objtrv = ChercherAuPoint( x, y);
			if( objtrv!=nullptr )
			{
				objetsource->TransfererUneConnexionAncre( objtrv );
			}
		}
		NettoyerSelection();
	}
}
void ZoneGraphique::SourisBouge( double x, double y )
{
	if(ElementStocke())
	{
		ActualiserPositionElement(x,y);
	}
}
void ZoneGraphique::ChoisirObjet(int n_press, double x, double y)
{
	grapheselectionne = ChercherAuPoint( x, y);
}
GraphiqueSurface *ZoneGraphique::ChercherAuPoint(const double vx, const double vy)
{
	for ( uint32_t i=0; i<lstgraphe.size(); i++ )
	{
		if(lstgraphe[i]->ContientPoint(vx,vy))
			return lstgraphe[i];
	}
	return nullptr;
}
void ZoneGraphique::TesterObjet(const double vx, const double vy)
{
	if( (graphestocke = ChercherAuPoint( vx, vy)) != nullptr)
	{
		stx=vx;
		sty=vy;
	}
}
bool ZoneGraphique::ElementStocke(){ return graphestocke != nullptr;}
bool ZoneGraphique::ElementSelectionne(){ return grapheselectionne != nullptr;}
GraphiqueSurface* ZoneGraphique::LogicielSelectionne()
{
	if( ElementSelectionne() )
	{
		if( grapheselectionne->EstUnLogiciel() )
		{
			return grapheselectionne;
		}
	}
	return nullptr;
}
bool ZoneGraphique::UnObjetEstSelectionne()
{
	return grapheselectionne!=nullptr;
}
GraphiqueSurface* ZoneGraphique::ObjetSelectionne()
{
	return grapheselectionne;
}
void ZoneGraphique::ActualiserPositionElement(const double nx, const double ny)
{
	graphestocke->BougerElement((nx-stx),(ny-sty));
	stx=nx;
	sty=ny;
	queue_draw();
}
void ZoneGraphique::NettoyerSelection()
{
	stx = sty = 0;
	graphestocke = grapheselectionne = nullptr;
}
void ZoneGraphique::Supprimer( GraphiqueSurface *valeur )
{
	Delister( valeur );
	if(grapheselectionne!=nullptr)
	{
		delete grapheselectionne;
		grapheselectionne = nullptr;
		queue_draw();
	}
}
void ZoneGraphique::Delister( GraphiqueSurface *valeur )
{
	if(valeur!=nullptr)
		grapheselectionne = valeur;
	if(grapheselectionne!=nullptr)
	{
		std::vector<GraphiqueSurface*>::iterator ctmp;
		ctmp = std::find (lstgraphe.begin(), lstgraphe.end(), grapheselectionne);
		if (ctmp != lstgraphe.end())
			lstgraphe.erase( ctmp );
	}
}
bool ZoneGraphique::LaSceneNestPasVide(){ return lstgraphe.size()!=0; }
void ZoneGraphique::Nettoyer()
{
	NettoyerSelection();
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
		delete lstgraphe[i];
	lstgraphe.clear();
	queue_draw();
}
void ZoneGraphique::ChangerDimensionsScene( int znlarge, int znhaut )
{
	dimLzone = znlarge;
	dimHzone = znhaut;
//	CentrerSchema();
}
void ZoneGraphique::CentrerSchema()
{
	double decalx, decaly;
	double marge = 0;
	double minx = std::numeric_limits<double>::max();
	double maxx = std::numeric_limits<double>::min();
	double miny = minx;
	double maxy = maxx;
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
		lstgraphe[i]->LimiteEncombrement( minx, maxx, miny, maxy );
	decalx = -minx+marge;
	decaly = -miny+marge;
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
		lstgraphe[i]->RepositionnerDansScene( decalx, decaly );
		
	decalx = ( dimLzone - ( maxx-minx ) )/2.0;
	decaly = ( dimHzone - ( maxy-miny ) )/2.0;
	for ( uint32_t i=0; i<lstgraphe.size(); i++)
		lstgraphe[i]->RepositionnerDansScene( decalx, decaly );

	queue_draw();
}
