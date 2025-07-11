#ifndef ELEMENT_H
#define ELEMENT_H

//#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <cairomm/context.h>
#include <pangomm.h>
#include "../source/structureappli.h"
#include "../tmpbibl/dgpoint.h"

class Element
{
public:

    Element();
    ~Element();

    uint16_t GenreElement()  const;
    std::string NomElement() const;
    bool EstUnLogiciel();

    void PositionDansScene( double valx, double valy );
	void RepositionnerDansScene( double decaleX, double decaleY );
	void RecalculerPositionDansScene();
    void PositionDansScene( DGPoint &retvaleur );
    double PositionXDansScene() const;
    double PositionYDansScene() const;
    void AnnulerCartouche();
    uint16_t HauteurElement() const;
    uint16_t LargeurElement() const;
	BlocRectangle Dimensions() const;
    DGPoint PointDeContact( uint8_t idx );
	void LimiteEncombrement( double &xmin, double &xmax, double &ymin, double &ymax );
    
    bool DimEgaleA( const BlocRectangle &valeur );
    void DimCopierDepuisBloc( const BlocRectangle &source );

    virtual bool ContientPoint( const double x, const double y );
	virtual void BougerElement( const double dx, const double dy );

protected:
	Cairo::RefPtr<Cairo::Context> tmpcr;
	Glib::RefPtr<Gdk::Pixbuf> image;
	
	double xctr, yctr, hautcart;
	
	void InitLigneDeBase( const DonneesLigne &valeur );
	
    bool objetselectionne;
    bool objetenmouvement;
    bool objetappuye;
    void GenreElement( uint16_t valeur );
    void NomElement(const std::string &valeur);
	void ConversionCouleur( const ChaineCouleur &valeur );
	void AppliquerValeurLigne();
	
    virtual void DessinerSymbole();
	virtual void DessinerCartouche();
	
// virtuelles vides
    virtual std::string LirePhraseInfo() const;
    virtual void Dessiner();
	
private :

	double xg, xd, yh, yb;
    std::string nomelement;
    uint16_t genre;// 100=logiciel  1000=ancre (graphtemporaire)
    
    BlocRectangle	dimsymbole;
    DonneesLigne	donneesligne;
/**
BlocSymbole
    BlocRectangle dimension;
		uint16_t largeur;
		uint16_t hauteur;
	DonneesSurface	surface;
		BlocCouleurs couleur;
			ChaineCouleur coulbandeau;
			ChaineCouleur coulfond;
		BlocPolice police;
			int16_t			hauteur;
			ChaineCouleur	couleur;
			ChaineGrandNom	nom;
**/
    
};

#endif // ELEMENT_H
