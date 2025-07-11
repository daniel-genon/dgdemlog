#ifndef GRAPHOBJETACTIF_H
#define GRAPHOBJETACTIF_H

#include "graphiquesurface.h"

#include "zonegraphique.h"
#include "configurationobjet.h"
#include "ancrage.h"

class GraphObjetActif : public GraphiqueSurface
{
public:

    GraphObjetActif();
    ~GraphObjetActif();
    
    void EntrerUneConnexion( Connexion *valeur );
    bool ConnecterElement( GraphObjetActif *valeur );
    void SupprimerLesConnexions();
	GraphiqueSurface *ValeurConnexion();
	void EntrerUneAncre( Ancrage *pvaleur, GraphiqueSurface *vbateau, EnrgConnexion *pvalconex );
    void RetirerAncre();
    
	virtual void TransfererUneConnexionAncre( GraphiqueSurface *ptrcible );
	virtual void RetirerLaConnexion( GraphiqueSurface *ptrconex );
	
    ConfigurationObjet *PtrConfObjet() const;

protected:

    void EntrerSourceConnexion( GraphiqueSurface *valeur );
    bool CreerConnexion( GraphObjetActif *ptrcible );
    Connexion *TrouverConnexion(  uint16_t valgenre );

    ConfigurationObjet	*cfgobjet;
    ZoneGraphique		*pscene;

    Element				*pelemresu;

private:

    Connexion *pconexencours;
    std::vector<Connexion*> lstconex;
    Ancrage *pancretmp;
    
    void MiseAJourConnexion();

    void SupprimerLesItemsAncre();
    
	virtual void ActualiserConnexion();

};

#endif // GRAPHOBJETACTIF_H
