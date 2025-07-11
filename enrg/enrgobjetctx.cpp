#include "enrgobjetctx.h"

EnrgObjetCtx::EnrgObjetCtx(){ Raz(); }
EnrgObjetCtx::EnrgObjetCtx( const DonneesContexte &source ){ valeurobjet = source; }
EnrgObjetCtx::EnrgObjetCtx( const BlocObjetCTX &valeur ){ valeurobjet = valeur.donnees; }

DonneesContexte EnrgObjetCtx::Donnees() const {	return valeurobjet; }
void EnrgObjetCtx::Valeur( const DonneesContexte &source ){	 valeurobjet = source; }
void EnrgObjetCtx::Raz()
{
	size_t taille = sizeof(DonneesContexte);
	memset(&valeurobjet,0,taille);
}
void EnrgObjetCtx::CopierDepuisBloc( const BlocObjetCTX &source ){ valeurobjet = source.donnees; }
void EnrgObjetCtx::CopierVersBloc( BlocObjetCTX &cible )
{
	memset(&cible,0,sizeof(BlocObjetCTX));
	cible.donnees = valeurobjet;
}

//    Liste d'enregistrement EnrgLogiciel

LstEnrgObjetCtx::LstEnrgObjetCtx(){}
LstEnrgObjetCtx::~LstEnrgObjetCtx()
{
	Nettoyer();
}
void LstEnrgObjetCtx::Ajouter( const DonneesContexte &source)
{
    ptrenrgobjetctx nouveau = new EnrgObjetCtx( source );
    listepointeur.push_back(nouveau);
}
void LstEnrgObjetCtx::Ajouter( const BlocObjetCTX &valeur )
{
    ptrenrgobjetctx nouveau = new EnrgObjetCtx(valeur);
    listepointeur.push_back(nouveau);
}
//bool LstEnrgObjetCtx::Trouver( uint32_t indexrt, ptrenrgobjetctx valeurptr )
//{
	//ctmp = std::find (listepointeur.begin(), listepointeur.end(), valeurptr);
    //if(ctmp != listepointeur.end())
    //{
		//indexrt = ctmp-listepointeur.begin();
		//return true;
	//}
    //else
		//return false;
//}
void LstEnrgObjetCtx::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
    listepointeur.clear();
}
uint32_t LstEnrgObjetCtx::TailleListe() const {	return listepointeur.size(); }
ptrenrgobjetctx LstEnrgObjetCtx::Position(uint32_t nindex) const{ return listepointeur.at(nindex); }
