#ifndef ENRGLIAISONCTX_H
#define ENRGLIAISONCTX_H

#include "../source/structureappli.h"

class EnrgLiaisonCtx
{
public:

    EnrgLiaisonCtx();
    EnrgLiaisonCtx( const DonneesContexteLiaison &valeur );
    EnrgLiaisonCtx( const BlocLiaisonCTX &valeur );
	void ValeurSource( const uint16_t valeur );
	void ValeurCible( const uint16_t valeur );
	void Valeur( const DonneesContexteLiaison &source );
	uint16_t ValeurSource() const;
	uint16_t ValeurCible() const;
    
	DonneesContexteLiaison Donnees() const;
	
    void Raz();
    
	void CopierDepuisBloc( const BlocLiaisonCTX &source );
	void CopierVersBloc( BlocLiaisonCTX &cible );

protected :

private :
    DonneesContexteLiaison donneesliaison;

};

typedef EnrgLiaisonCtx *ptrenrgliaisonctx;

class LstEnrgLiaisonCtx
{
public:
    LstEnrgLiaisonCtx();
    ~LstEnrgLiaisonCtx();
    
	void Ajouter( const DonneesContexteLiaison &source);
	void Ajouter( const BlocLiaisonCTX &valeur );

    void Nettoyer();
    
    uint32_t TailleListe() const;
    ptrenrgliaisonctx Position( uint32_t nindex ) const;
    
private :
	std::vector<ptrenrgliaisonctx> listepointeur;
	std::vector<ptrenrgliaisonctx>::iterator ctmp;

};

#endif // ENRGLIAISONCTX_H
