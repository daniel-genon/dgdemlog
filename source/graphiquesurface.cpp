#include "graphiquesurface.h"

GraphiqueSurface::GraphiqueSurface(){}

void GraphiqueSurface::ValeurGraphe( const BlocSymbole &valeur )
{
    DimCopierDepuisBloc( valeur.dimension );
    valsurface = valeur.surface;
    hautcart = valsurface.police.hauteur*2;
}

std::string GraphiqueSurface::CouleurFond() const { return std::string((char *)valsurface.couleur.coulfond.v ); }
std::string GraphiqueSurface::CouleurBandeau() const { return std::string((char *)valsurface.couleur.coulbandeau.v ); }
ChaineCouleur GraphiqueSurface::BCouleurFond() const {    return valsurface.couleur.coulfond; }
ChaineCouleur GraphiqueSurface::BCouleurBandeau() const {    return valsurface.couleur.coulbandeau; }
BlocPolice GraphiqueSurface::Police() const { return valsurface.police; }
BlocPolice *GraphiqueSurface::PPolice() { return &valsurface.police; }
//
DonneesSurface GraphiqueSurface::ValSurface() const { return valsurface; }
BlocSymbole	GraphiqueSurface::Donnees() const
{
	BlocSymbole rtsymbole;
	memset( &rtsymbole, 0 , sizeof(BlocSymbole));
	rtsymbole.dimension = Dimensions();
	rtsymbole.surface	= valsurface;
	return rtsymbole;
}

bool GraphiqueSurface::EgaleA( const BlocSymbole &autre )
{
	if( !DimEgaleA( autre.dimension )) return false;
	return memcmp( &valsurface, &autre.surface , sizeof(DonneesSurface)) == 0;
}

void GraphiqueSurface::CopierVersBloc( BlocSymbole &cible )
{
	cible.dimension = Dimensions();
	cible.surface	= valsurface;
}
void GraphiqueSurface::CopierDepuisBloc(const BlocSymbole &source )
{
	ValeurGraphe( source );
}

void GraphiqueSurface::ReDessiner(const Cairo::RefPtr<Cairo::Context>& cr)
{
	tmpcr = cr;
	Dessiner();
	ActualiserConnexion();
}

void GraphiqueSurface::RetracerGraphique()
{
	Dessiner();
}



//// ****************** Routines graphiques  *********************

Glib::RefPtr<Gdk::Pixbuf> GraphiqueSurface::ChargerIcone()
{
	return Gdk::Pixbuf::create_from_resource( "/icone/quitter2.png" );
}
void GraphiqueSurface::DessinerIcone()
{
	Glib::RefPtr<Gdk::Pixbuf> imagetmp = ChargerIcone();
	if( imagetmp == nullptr )
		imagetmp = Gdk::Pixbuf::create_from_resource( "/icone/demarre.png" );
	if( HauteurElement()>LargeurElement() )
		lgimg = LargeurElement()*0.8;
	else
		lgimg = HauteurElement()*0.8;
	image = imagetmp->scale_simple( lgimg, lgimg, Gdk::InterpType::BILINEAR );
	lgimg = image->get_width();
}
void GraphiqueSurface::EcrireTxtCadre()
{
	Glib::RefPtr<Pango::Layout> cadrecorp = Pango::Layout::create(tmpcr);
		cadrecorp->set_font_description(lettrage);
		cadrecorp->set_text(LibelleTitre());
			cadrecorp->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to( xctr-lgimg, yctr-httxt/2);
	cadrecorp->show_in_cairo_context(tmpcr);
}
void GraphiqueSurface::EcrireTxtCartouche()
{
	Glib::RefPtr<Pango::Layout> cadrecart = Pango::Layout::create(tmpcr);
		cadrecart->set_font_description(lettrage);
		cadrecart->set_text(LibelleNom());
			cadrecart->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to( xctr-lgtxt/2, yctr- HauteurElement()/2 - hautcart/2 - httxt/2 );
	cadrecart->show_in_cairo_context(tmpcr);
}
void GraphiqueSurface::ParametrerPolice()
{
	lettrage.set_family( std::string((char *)valsurface.police.nom.v ) );
	lettrage.set_weight(Pango::Weight::NORMAL);
	lettrage.set_size( Pango::SCALE * PANGO_SCALE_MEDIUM * valsurface.police.hauteur );
}

void GraphiqueSurface::Dessiner()
{
	ConversionCouleur( valsurface.couleur.coulfond );	
		DessinerSymbole();
	ConversionCouleur( valsurface.couleur.coulbandeau );	
		DessinerCartouche();
	ConversionCouleur( valsurface.police.couleur );	
		ParametrerPolice();
	DessinerIcone();
	EcrireTxtCadre();
	EcrireTxtCartouche();
	
	Gdk::Cairo::set_source_pixbuf(tmpcr, image, xctr+LargeurElement()/2-lgimg*1.1, yctr-image->get_height()*0.5);
	tmpcr->paint();
}

std::string GraphiqueSurface::LibelleTitre(){ return "nom clair";}
std::string GraphiqueSurface::LibelleNom(){ return "nom processus";}
void GraphiqueSurface::ActualiserConnexion(){}
void GraphiqueSurface::TransfererUneConnexionAncre( GraphiqueSurface *ptrancre ){}
GraphiqueSurface *GraphiqueSurface::ObjetConnecter(){ return nullptr; }
void GraphiqueSurface::RetirerLaConnexion( GraphiqueSurface *ptrconex ){}
