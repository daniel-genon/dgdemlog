#include "enrgliaisonctx.h"

EnrgLiaisonCtx::EnrgLiaisonCtx(){ Raz(); }
EnrgLiaisonCtx::EnrgLiaisonCtx( const DonneesContexteLiaison &valeur ){ donneesliaison = valeur; }
EnrgLiaisonCtx::EnrgLiaisonCtx( const BlocLiaisonCTX &valeur ){ donneesliaison = valeur.donnees; }

DonneesContexteLiaison EnrgLiaisonCtx::Donnees() const { return donneesliaison; }

void EnrgLiaisonCtx::ValeurSource( const uint16_t valeur ){ donneesliaison.idxsource = valeur; }
void EnrgLiaisonCtx::ValeurCible( const uint16_t valeur ){ donneesliaison.idxcible = valeur; }
uint16_t EnrgLiaisonCtx::ValeurSource() const { return donneesliaison.idxsource; }
uint16_t EnrgLiaisonCtx::ValeurCible() const { return donneesliaison.idxcible; }

void EnrgLiaisonCtx::Valeur( const DonneesContexteLiaison &source ){	 donneesliaison = source; }

void EnrgLiaisonCtx::Raz()
{
	size_t taille = sizeof(DonneesContexteLiaison);
	memset(&donneesliaison,0,taille);
}
void EnrgLiaisonCtx::CopierDepuisBloc( const BlocLiaisonCTX &source )
{
	donneesliaison = source.donnees;
}
void EnrgLiaisonCtx::CopierVersBloc( BlocLiaisonCTX &cible )
{
	memset(&cible,0,sizeof(BlocLiaisonCTX));
	cible.donnees = donneesliaison;
}

//    Liste d'enregistrement EnrgLogiciel

LstEnrgLiaisonCtx::LstEnrgLiaisonCtx(){}
LstEnrgLiaisonCtx::~LstEnrgLiaisonCtx()
{
	Nettoyer();
}
void LstEnrgLiaisonCtx::Ajouter( const DonneesContexteLiaison &source)
{
    ptrenrgliaisonctx nouveau = new EnrgLiaisonCtx( source );
    listepointeur.push_back(nouveau);
}
void LstEnrgLiaisonCtx::Ajouter( const BlocLiaisonCTX &valeur )
{
    ptrenrgliaisonctx nouveau = new EnrgLiaisonCtx(valeur);
    listepointeur.push_back(nouveau);
}
void LstEnrgLiaisonCtx::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
    listepointeur.clear();
}
uint32_t LstEnrgLiaisonCtx::TailleListe() const
{
	return listepointeur.size();
}
ptrenrgliaisonctx LstEnrgLiaisonCtx::Position(uint32_t nindex) const
{
	return listepointeur.at(nindex);
}
