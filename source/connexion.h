#ifndef CONNEXION_H
#define CONNEXION_H

#include "../enrg/enrgconnexion.h"
#include "configurationobjet.h"
#include "graphiquesurface.h"

class Connexion : public GraphiqueSurface
{
public:

	Connexion( ptrenrconnexion ptr,  GraphiqueSurface *valeur = nullptr );
    bool EntrerContacts ( GraphiqueSurface *ptrsource, GraphiqueSurface *ptrcible );
    void EntrerSource ( GraphiqueSurface *valeur );
    void EntrerCible ( GraphiqueSurface *valeur );

    //void RemplacerContact( Element *pexistant, Element *pnouveau );
    GraphiqueSurface *ValeurCible() const;
    GraphiqueSurface *ValeurSource() const;
    //Element *ValeurAutreConnecter(Element *pexistant ) const;
    void Actualiser();
    void Deconnecter();
    
protected:

	virtual void Dessiner();

private:
    GraphiqueSurface *pcible;
    GraphiqueSurface *psource;

    DGPoint pntcible;
    DGPoint pntsource;
    
};

typedef Connexion *ptrconnexion;


#endif // CONNEXION_H
