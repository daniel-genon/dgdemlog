#ifndef ANCRAGE_H
#define ANCRAGE_H

#include "connexion.h"
#include "configurationobjet.h"
#include "../defdia/messagemsa.h"


class Ancrage : public GraphiqueSurface
{
public:

    Ancrage();
    Ancrage( Element *vbateau, ConfigurationObjet *ptrcfg );

    ~Ancrage();

    void Valeur( const DonneesAncre &valeur );
//    void Valeur( EnrgAncre *pobjetancre );
//    void Valeur( const std::string &imicon, uint8_t large, uint8_t haut, const BlocPolice &vpoli );
    //void Standard();

    //void EntrerUneConnexionTemporaire( Connexion *valeur );

//    bool AncreMaterialisee();
//    void Nettoyerconnexion();
    
	virtual GraphiqueSurface *ObjetConnecter();
    
protected:
    virtual void Dessiner();

private:

    Connexion   *pconextmp;
    Element     *bateau;
//    DGPoint     svdposition;
    MessageMSA  *messagemsa;
//    std::string	nomfichiericone;
	DonneesAncre donneesancre;
//   bool TransfererConnexion( Element *pelem );

};

#endif // ANCRAGE_H
