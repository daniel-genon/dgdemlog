/*
*/
#ifndef ZONEGRAPHIQUE_H_
#define ZONEGRAPHIQUE_H_

#include <gtkmm.h>
#include "graphiquesurface.h"

class ZoneGraphique : public Gtk::DrawingArea
{
public:
	ZoneGraphique();
	virtual ~ZoneGraphique();
	
	void AjouterElement( GraphiqueSurface *pvaleur );
	void ActualiserGraphe( GraphiqueSurface *pvaleur );
	bool CollecterGenreObjet( const uint16_t valgenre, std::vector<GraphiqueSurface*> &retlst );
	GraphiqueSurface* CollecterGenreObjet( const uint16_t valgenre );
	void ChoisirObjet(int n_press, double x, double y);
	void AppuyerSouris( int n_press, double x, double y );
	void LacherSouris( int n_press, double x, double y );
	void SourisBouge( double x, double y );
	
	bool UnObjetEstSelectionne();	
	GraphiqueSurface* LogicielSelectionne();
	GraphiqueSurface* ObjetSelectionne();
	
	void Nettoyer();
	void Supprimer( GraphiqueSurface *valeur );
	void Delister( GraphiqueSurface *valeur );
	
	bool LaSceneNestPasVide();
	void CentrerSchema();
	void ChangerDimensionsScene( int znlarge, int znhaut );
	
protected:
	void Dessiner(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	
private:	
	double	stx, sty;
	int		dimLzone, dimHzone;
	std::vector<GraphiqueSurface*> lstgraphe;
	GraphiqueSurface *graphestocke, *grapheselectionne;
	
	void TesterObjet(const double vx, const double vy);
	bool ElementStocke();
	bool ElementSelectionne();
	void ActualiserPositionElement(const double nx, const double ny);
	void SelectionnerObjet(const double nx, const double ny);
	void NettoyerSelection();
	GraphiqueSurface *ChercherAuPoint(const double vx, const double vy);

};

#endif /* ZONEGRAPHIQUE_H_ */
