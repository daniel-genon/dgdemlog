#ifndef FBLOCOBJETCONTEXTE_H
#define FBLOCOBJETCONTEXTE_H

#include "tmp_chemin_bibliodg.h"
#include "../enrg/enrgobjetctx.h"
#include "../enrg/enrgliaisonctx.h"
/**
 * descriptif du contenu fichier binaire

BLOC0000
ocnx0000
taille (taille de tout le bloc qui suit
BLOC : nom du contexte nb cars 32max
	taille (taille de tout le part qui suit
	part = "objets";
		taille (taille de toute la structure qui suit
		struc = processus
			BlocLogiciel
		struc = processus
			BlocLogiciel
		* etc...
	taille (taille de tout le part qui suit
	part = "liaisons";
		taille (taille de toute la structure qui suit
		struc = priorite
			BlocPriorite
		* etc...
taille (taille de tout le bloc qui suit
BLOC : nom de la configuration nb cars 32max
	taille (taille de tout le part qui suit
	


*/

class FBlocObjetContexte : public DGFicBloc
{
public:
    
    FBlocObjetContexte( const std::string &cheminprojet );

//    void AjouterObjetContexte();
    bool EcrireObjetContexte( const std::string &valeur );
//    bool ModifierObjetContexte( const std::string &valeur );
    bool LireObjetContexte( const std::string &valeur );
	bool ContexteExiste( const std::string &valeur );
    void PointerObjet( uint32_t rang );
    void PointerLiaison( uint32_t rang );
    void AjouterObjet();
    void AjouterLiaison();
    
    EnrgObjetCtx *PtrEnrgObj();
    EnrgLiaisonCtx *PtrEnrgLia();
    uint32_t MaxObjet() const;
    uint32_t MaxLiaison() const;

private:
    EnrgObjetCtx	enrgobjtmp;
    EnrgLiaisonCtx	enrgliatmp;
    LstEnrgObjetCtx lstobjetsCtx;
    LstEnrgLiaisonCtx lstliaisonCtx;
	uint16_t	typeformat;

    std::string nomducontexte;

	BlocObjetCTX	strucObj;
	BlocLiaisonCTX	strucLia;
    ChaineBalise	nompartOBJ,nompartLIA;// nom des partx
    ChaineBalise	nomstruOBJ,nomstruLIA;// nom des structures
	uint32_t	taillestruobj, taillestrulia;

	virtual void InitHierarchie();
	virtual void FormaterDonnee();
	virtual void DeFormaterDonnee();
};

#endif // FBLOCOBJETCONTEXTE_H
