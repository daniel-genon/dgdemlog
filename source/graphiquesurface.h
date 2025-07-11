#ifndef GRAPHIQUESURFACE_H
#define GRAPHIQUESURFACE_H

#include "element.h"
//#include "../enrg/enrggraph.h"
#include "../enrg/enrgpolice.h"

class GraphiqueSurface : public Element
{
public:

    GraphiqueSurface();

	void ValeurGraphe( const BlocSymbole &valeur );
	BlocPolice Police() const ;
	BlocPolice *PPolice();

    std::string CouleurFond() const;
    std::string CouleurBandeau() const;
      
	DonneesSurface ValSurface() const;
	BlocSymbole	Donnees() const ;

    bool EgaleA(const BlocSymbole &autre );
    void CopierVersBloc( BlocSymbole &cible );
    void CopierDepuisBloc( const BlocSymbole &source );

	void ReDessiner( const Cairo::RefPtr<Cairo::Context>& cr );
	void RetracerGraphique();
	
	virtual void TransfererUneConnexionAncre( GraphiqueSurface *ptrancre );
	virtual GraphiqueSurface *ObjetConnecter();
	virtual void RetirerLaConnexion( GraphiqueSurface *ptrconex );
	
protected:

	ChaineCouleur BCouleurFond() const;
	ChaineCouleur BCouleurBandeau() const;

    virtual void Dessiner();

private:

	DonneesSurface	valsurface;

	int lgimg, lgtxt, httxt;
	Pango::FontDescription lettrage;
	Glib::RefPtr<Gdk::Pixbuf> image;
	
    void ParametrerPolice();
    void EcrireTxtCadre();
    void EcrireTxtCartouche();

    virtual void DessinerIcone();
	virtual void ActualiserConnexion();
    virtual std::string LibelleTitre();
    virtual std::string LibelleNom();
	virtual Glib::RefPtr<Gdk::Pixbuf> ChargerIcone();
	
};

#endif // GRAPHIQUESURFACE_H
