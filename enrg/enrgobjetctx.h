#ifndef ENRGOBJETCTX_H
#define ENRGOBJETCTX_H

#include "../source/structureappli.h"
//#include "../tmpbibl/dgpoint.h"

class EnrgObjetCtx
{
public:

    EnrgObjetCtx();
    EnrgObjetCtx( const DonneesContexte &source );
    EnrgObjetCtx( const BlocObjetCTX &valeur );

	void Valeur( const DonneesContexte &source );
    
	DonneesContexte Donnees() const;
	
    void Raz();
    
	void CopierDepuisBloc( const BlocObjetCTX &source );
	void CopierVersBloc( BlocObjetCTX &cible );

protected :

private :

    DonneesContexte	valeurobjet;

};

typedef EnrgObjetCtx *ptrenrgobjetctx;

class LstEnrgObjetCtx
{
public:
    LstEnrgObjetCtx();
    ~LstEnrgObjetCtx();
    
	void Ajouter( const DonneesContexte &source);
	void Ajouter( const BlocObjetCTX &valeur );

//	bool Trouver( uint32_t indexrt, ptrenrgobjetctx valeurptr );
    void Nettoyer();
    
    uint32_t TailleListe() const;
    ptrenrgobjetctx Position( uint32_t nindex ) const;
    
private :
	std::vector<ptrenrgobjetctx> listepointeur;
	std::vector<ptrenrgobjetctx>::iterator ctmp;

};

#endif // ENRGOBJETCTX_H
