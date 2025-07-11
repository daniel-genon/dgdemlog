#ifndef FBLOCCONFIG_H
#define FBLOCCONFIG_H

#include "tmp_chemin_bibliodg.h"
#include "../source/structureappli.h"
#include "../enrg/enrgconfig.h"
#include "../enrg/enrglogiciel.h"
#include "../enrg/enrggraph.h"
#include "../enrg/enrgconnexion.h"
#include "../enrg/enrgancre.h"

/**
 * descriptif du contenu fichier binaire

BLOC0000
conf0000
taille (taille de tout le bloc qui suit
BLOC : nom de la configuration nb cars 32max
	taille (taille de tout le part qui suit
	part = "generalites";
		taille (taille de toute la structure qui suit
		struc = application
			BlocConfig
		taille (taille de toute la structure qui suit
		struc = connexion
			BlocConnexion
		taille (taille de toute la structure qui suit
		struc = graphisme
			BlocSymbole
	taille (taille de tout le part qui suit
	part = "logiciel";
		taille (taille de toute la structure qui suit
		struc = processus
			BlocLogiciel
		struc = processus
			BlocLogiciel
		* etc...
	taille (taille de tout le part qui suit
	part = "demarrage";
		taille (taille de toute la structure qui suit
		struc = priorite
			BlocPriorite
taille (taille de tout le bloc qui suit
BLOC : nom de la configuration nb cars 32max
	taille (taille de tout le part qui suit
	
etc...
**/

class FBlocConfig : public DGFicBloc
{
public:

    FBlocConfig();

    void CreerConfigurationStandard();
    bool ModifierConfig( uint8_t codevalmodif );
    bool LireConfiguration( const std::string &valeur );
    bool LirePremiereConfig();
	bool EcrireConfig();
	
	EnrgConfig*			ptrConfig();
	EnrgAncre*			ptrAncrage();
	LstEnrgLogiciel*	ptrlstLogiciel();
	LstEnrgGrLog*		ptrlstgrlogiciel();
	LstEnrgGrFic*		ptrlstgrfic();
    LstEnrgConnexion*	ptrlstconnexion();
	

//    void InitPointeur(EnrgConfig *pv1, EnrgConnexion *ps2, LstEnrgLogiciel *pv2, LstEnrgGrLog *pv3, LstEnrgGrFic *pv4 );

protected:

    EnrgConfig		enrgconfig;
    EnrgAncre		enrgancre;
    LstEnrgLogiciel lstenrlog;
    LstEnrgGrLog    lstenrgralog;
    LstEnrgGrFic    lstgrhficlie;
    LstEnrgConnexion   lstconnexion;


	virtual void InitHierarchie();
	virtual void FormaterDonnee();
	virtual void DeFormaterDonnee();
	virtual void AjouterDonneeVersListe();

private:

	typedef bool (FBlocConfig::*PtrFnctboucle)();
    
    EnrgLogiciel	enrglogtmp;
    EnrgGraph		enrggraphlogtmp;
    EnrgConnexion	enrgconnexiontmp;

    BlocConfig      strucCfg;
	BlocConnexion	strucCnx;
	BlocLogiciel    strucLog;
	BlocGraphLog	strucGra;
	BlocAncre		strucAnc;
	
    ChaineBalise	nompartCFG,nompartCNX,nompartLOG,nompartGRA,nompartLIE;// nom des partx
    ChaineBalise	nomstruCFG,nomstruANC,nomstruLOG,nomstruCNX,nomstruGLG,nomstruGRA;// nom des structures
	uint32_t	taillestrucfg, taillestrucnx, taillestrulog, taillestrugra, taillestruanc;
	uint16_t	typeformat;
	
	PtrFnctboucle	ptrversboucle;
    
    bool Modifier();
    bool LireBlocConfig();
    bool ModifierPartConfig();
    
    bool BoucleLogiciel();
	bool BoucleGraphique();
	bool BoucleFichierLie();
	bool BoucleConnexion();
};

#endif // FBLOCCONFIG_H
