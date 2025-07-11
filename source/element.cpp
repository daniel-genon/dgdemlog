#include "element.h"
#include "../enrg/enrgconnexion.h"

Element::Element()
{
    genre = 9999;
    dimsymbole.largeur = 40;
    dimsymbole.hauteur = 40;
    hautcart = 0;
    nomelement  = "élément";
    EnrgConnexion lignetmp;
    lignetmp.Standard();
    donneesligne = lignetmp.Donnees();
}
Element::~Element(){}
void Element::GenreElement( uint16_t valeur ){ genre = valeur;}
void Element::NomElement(const std::string &valeur) {	nomelement = valeur; }

uint16_t Element::GenreElement() const {    return genre; }
std::string Element::NomElement() const {	return nomelement; }
bool Element::EstUnLogiciel(){    return ( genre == 100 ); }

void Element::InitLigneDeBase( const DonneesLigne &valeur ){	donneesligne = valeur; }

void Element::PositionDansScene(  double valx, double valy  )
{
	xctr = valx;
	yctr = valy;
	RecalculerPositionDansScene();
}
void Element::RepositionnerDansScene( double decaleX, double decaleY )
{
	xctr += decaleX;
	yctr += decaleY;
	RecalculerPositionDansScene();
}
void Element::RecalculerPositionDansScene()
{
	xg = xctr-dimsymbole.largeur/2;
	yh = yctr-dimsymbole.hauteur/2;
	xd = xg+dimsymbole.largeur;
	yb = yh+dimsymbole.hauteur;
}
bool Element::ContientPoint( const double x, const double y )
{
	return (((x>xg)&&(x<xd))&&((y>yh)&&(y<yb)));
}
void Element::PositionDansScene( DGPoint &retvaleur ){	retvaleur.Set( xctr, yctr ); }
BlocRectangle Element::Dimensions() const {	return dimsymbole; }
//double Element::PositionXDansScene() const {    return xctr-dimsymbole.largeur/2;}
//double Element::PositionYDansScene() const {    return yctr-dimsymbole.hauteur/2;}
double Element::PositionXDansScene() const {    return xctr;}
double Element::PositionYDansScene() const {    return yctr;}
uint16_t Element::HauteurElement() const{    return dimsymbole.hauteur;}
uint16_t Element::LargeurElement() const{    return dimsymbole.largeur;}

bool Element::DimEgaleA( const BlocRectangle &valeur )
{
	return  memcmp( &dimsymbole, &valeur , sizeof(BlocRectangle)) == 0;
}

void Element::DimCopierDepuisBloc(const BlocRectangle &source ) { dimsymbole = source; }
void Element::AnnulerCartouche(){ hautcart = 0; }

DGPoint Element::PointDeContact( uint8_t idx )
{
    DGPoint pctr( xctr, yctr );
    switch(idx)
    {
        case 0:{//dessous
            pctr.ValY(pctr.ValY()+dimsymbole.hauteur/2);
        }break;
        case 1:{//gauche
            pctr.ValX(pctr.ValX()+dimsymbole.largeur/2);
        }break;
        case 2:{//dessus
            pctr.ValY(pctr.ValY()-dimsymbole.hauteur+hautcart/2);
        }break;
        case 3:{//droit
            pctr.ValX(pctr.ValX()-dimsymbole.largeur/2);
        }break;
//        default:{

//        }
    }
    return ( pctr );
}
void Element::ConversionCouleur( const ChaineCouleur &valeur )
{
	GdkRGBA tmpcoul;
	gdk_rgba_parse ( &tmpcoul, (char *)valeur.v );
	tmpcr->set_source_rgba( tmpcoul.red, tmpcoul.green, tmpcoul.blue, 1.0 );
}

///******************* Routines Graphiques perso ****************************/
void Element::AppliquerValeurLigne()
{
	tmpcr->set_line_width( donneesligne.epaisseur );
	ConversionCouleur( donneesligne.couleur );
}

void Element::DessinerSymbole()
{
	tmpcr->set_line_width(1.0);
	tmpcr->rectangle( xg, yh, dimsymbole.largeur, dimsymbole.hauteur );
	tmpcr->fill();
	ConversionCouleur( donneesligne.couleur );
	tmpcr->set_line_width( donneesligne.epaisseur );
		tmpcr->move_to(xg,yh);
		tmpcr->line_to(xd,yh);
		tmpcr->set_line_width(2.0);
		tmpcr->line_to(xd,yb);
		tmpcr->line_to(xg,yb);
		tmpcr->close_path();
		tmpcr->stroke();
}
void Element::DessinerCartouche()
{
	tmpcr->set_line_width(1.0);
	tmpcr->rectangle( xg, yh-hautcart, dimsymbole.largeur, hautcart );
	tmpcr->fill();
	ConversionCouleur( donneesligne.couleur );
	tmpcr->set_line_width( donneesligne.epaisseur );
	tmpcr->move_to(xg,yh);
	tmpcr->line_to(xg,yh-hautcart);
	tmpcr->line_to(xg+dimsymbole.largeur,yh-hautcart);
	tmpcr->line_to(xg+dimsymbole.largeur,yh);
	tmpcr->stroke();
}
void Element::LimiteEncombrement(  double &xmin, double &xmax, double &ymin, double &ymax  )
{
	if( xg < xmin )
		xmin=xg;
	if( xd > xmax )
		xmax = xd;
	if( yh < ymin )
		ymin = yh;
	if( yb > ymax )
		ymax = yb;
}

//////************************************************************
//////    Gestion des événements
//////************************************************************
void Element::BougerElement( const double dx, const double dy )
{
	xctr += dx;
	yctr += dy;
	xg += dx;
	xd += dx;
	yh += dy;
	yb += dy;
	Dessiner();
}
//////************************************************************
//////    Virtuelles vides
//////************************************************************
std::string Element::LirePhraseInfo() const { return std::string("");}
void Element::Dessiner(){}
