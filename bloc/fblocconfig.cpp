#include "fblocconfig.h"

FBlocConfig::FBlocConfig()
{
	InitHierarchie();
	taillebloc	= 0;
	typeformat	= 0;
	taillestrucfg	= tailletetestruc + sizeof(DonneesConfig);
	taillestruanc	= tailletetestruc + sizeof(DonneesAncre);
	taillestrucnx	= tailletetestruc + sizeof(DonneesLigne);
	taillestrulog	= tailletetestruc + sizeof(DonneesLogiciel);
	taillestrugra	= tailletetestruc + sizeof(DonneesGraphe)+sizeof(uint8_t)*2;
    NomFichier("cfgdgdemlog");
   	ExtensionFichier("gla");
}
void FBlocConfig::InitHierarchie()
{
	entetefichier.type	= 0x30303030434F4C42;//BLOC0000
	entetefichier.genre	= 0x30303030666E6F63;//conf0000
	CvtChaineEnBalise("generalites" ,&nompartCFG );//part
		CvtChaineEnBalise("application" ,&nomstruCFG );//struc
		CvtChaineEnBalise("ancrage" ,&nomstruANC );
	CvtChaineEnBalise("connexion" ,&nompartCNX );//part
		CvtChaineEnBalise("ligne" ,&nomstruCNX );//struc (1 à n)
	CvtChaineEnBalise("logiciel" ,&nompartLOG );//part
		CvtChaineEnBalise("processus" ,&nomstruLOG );//struc (1 à n)
	CvtChaineEnBalise("graphismelog", &nompartGRA );//part
		CvtChaineEnBalise("graphe logiciel" ,&nomstruGLG );//struc (1 à n)
	CvtChaineEnBalise("fichierlie", &nompartLIE );//part 
		CvtChaineEnBalise("fichier lie",&nomstruGRA );//struc (1 à n)
}
void FBlocConfig::FormaterDonnee()
{
	switch(typeformat)
	{
		case 1 ://cfg appli
			InitBlocData((char *)&strucCfg, taillestrucfg );
			memset(&strucCfg,0,taillestrucfg);
			enrgconfig.CopierVersBloc( strucCfg );
			strucCfg.clef.taille	= taillestrucfg;
			strucCfg.clef.nom	= nomstrucencours;			
			break;
		case 2 ://ancre
			InitBlocData((char *)&strucAnc, taillestruanc );
			memset(&strucAnc,0,taillestruanc);
			enrgancre.CopierVersBloc( strucAnc );
			strucAnc.clef.taille	= taillestruanc;
			strucAnc.clef.nom	= nomstrucencours;			
			break;
		case 3 ://logiciel
			InitBlocData((char *)&strucLog, taillestrulog );
			memset(&strucLog,0,taillestrulog);
			enrglogtmp.CopierVersBloc( strucLog );
			strucLog.clef.taille	= taillestrulog;
			strucLog.clef.nom	= nomstrucencours;			
			break;
		case 4 ://graphique
			InitBlocData((char *)&strucGra, taillestrugra );
			enrggraphlogtmp.CopierVersBloc( strucGra );
			strucGra.clef.taille	= taillestrugra;
			strucGra.clef.nom	= nomstrucencours;			
			break;
		case 5 ://fichier lié // 0:travail, 1:config
			InitBlocData((char *)&strucGra, taillestrugra );
			enrggraphlogtmp.CopierVersBloc( strucGra );
			strucGra.clef.taille	= taillestrugra;
			strucGra.clef.nom	= nomstrucencours;
			break;			
		case 6 ://connexion	
			InitBlocData((char *)&strucCnx, taillestrucnx );
			enrgconnexiontmp.CopierVersBloc( strucCnx );
			strucCnx.clef.taille	= taillestrucnx;
			strucCnx.clef.nom	= nomstrucencours;			
			break;
	}
}
void FBlocConfig::DeFormaterDonnee()
{
	switch(typeformat)
	{
		case 1 ://cfg appli
			enrgconfig.CopierDepuisBloc( strucCfg );
			break;
		case 2 ://ancrage
			enrgancre.CopierDepuisBloc( strucAnc );
			break;
		case 3 ://logiciel
			enrglogtmp.CopierDepuisBloc( strucLog );
			break;
		case 4 ://graphique
			enrggraphlogtmp.CopierDepuisBloc( strucGra );
			break;
		case 5 ://fichier lié // 0:travail, 1:config
			enrggraphlogtmp.CopierDepuisBloc( strucGra );
			break;
		case 6 ://connexion	0 conex logiciel 1 conex travail 2 conex config
			enrgconnexiontmp.CopierDepuisBloc( strucCnx );
	}
}
void FBlocConfig::AjouterDonneeVersListe()
{
	switch(typeformat)
	{
		//case 1 ://cfg appli
			//enrgconfig.CopierDepuisBloc( strucCfg );
			//break;
		//case 2 ://ancrage
			//enrgancre.CopierDepuisBloc( strucAnc );
			//break;
		case 3 ://logiciel
			lstenrlog.Ajouter(strucLog);
			break;
		case 4 ://graphique
			lstenrgralog.Ajouter(strucGra);
			break;
		case 5 ://fichier lié // 0:travail, 1:config
			lstgrhficlie.Ajouter(strucGra);
			break;
		case 6 ://connexion	0 conex logiciel 1 conex travail 2 conex config
			lstconnexion.Ajouter(strucCnx);
	}
}
/*
void FBlocConfig::InitPointeur(EnrgConfig *pv1, EnrgConnexion *ps2, LstEnrgLogiciel *pv2, LstEnrgGrLog *pv3, LstEnrgGrFic *pv4 )
{
    penrg       = pv1;
    plstlog     = pv2;
    plstpri     = pv3;
    pconnexion  = ps2;
    plstfic     = pv4;
}
*/
void FBlocConfig::CreerConfigurationStandard(){ EcrireConfig(); }
bool FBlocConfig::EcrireConfig()
{
    if(!FichierExiste()) CreerLeFichier();
	CvtChaineEnBalise(enrgconfig.Nom(), &nomblocencours );
	if(!CreerUnBloc()) return false;
	nompartencours = nompartCFG;
	if(!CreerUnPart()) return false;
		nomstrucencours = nomstruCFG;
		typeformat=1;
		if(!CreerLaStruc()) return false;
		nomstrucencours = nomstruANC;
		typeformat=2;
		if(!CreerLaStruc()) return false;
	nompartencours = nompartLOG;
	if(!CreerUnPart()) return false;
		nomstrucencours = nomstruLOG;
		typeformat=3;
		for( uint32_t i=0; i<lstenrlog.TailleListe() ;i++)
		{
			enrglogtmp = *lstenrlog.Position(i);
			if(!CreerLaStruc()) return false;
		}
	nompartencours = nompartGRA;
	if(!CreerUnPart()) return false;
		nomstrucencours = nomstruGLG;
		typeformat=4;
		for( uint32_t i=0; i<lstenrgralog.TailleListe() ;i++)
		{
			enrggraphlogtmp = *lstenrgralog.Position(i);
			if(!CreerLaStruc()) return false;
		}
	nompartencours = nompartLIE;
	if(!CreerUnPart()) return false;
		nomstrucencours = nomstruGRA;
		typeformat=5;
		for( uint32_t i=0; i<lstgrhficlie.TailleListe() ;i++)
		{// 0:travail 1:config
			enrggraphlogtmp = *lstgrhficlie.Position(i);
			if(!CreerLaStruc()) return false;
		}
	nompartencours = nompartCNX;
	if(!CreerUnPart()) return false;
		nomstrucencours = nomstruCNX;
		typeformat=6;
		for( uint32_t i=0; i<lstconnexion.TailleListe() ;i++)
		{// 0:logiciel 1:travail 2:config
			enrgconnexiontmp = *lstconnexion.Position(i);
			if(!CreerLaStruc()) return false;
		}
	return true;
}
EnrgConfig* FBlocConfig::ptrConfig(){	return &enrgconfig;}
EnrgAncre* FBlocConfig::ptrAncrage(){	return &enrgancre;}
LstEnrgLogiciel* FBlocConfig::ptrlstLogiciel(){	return &lstenrlog;}
LstEnrgGrLog* FBlocConfig::ptrlstgrlogiciel(){	return &lstenrgralog;}
LstEnrgGrFic* FBlocConfig::ptrlstgrfic(){	return &lstgrhficlie;}
LstEnrgConnexion* FBlocConfig::ptrlstconnexion(){	return &lstconnexion;}
bool FBlocConfig::LireConfiguration( const std::string &valeur )
{
	phrtest = valeur;
	if(CvtChaineEnBalise( valeur, &nomblocencours ))
	{
		if( BlocExiste() )
			LireBlocConfig();
	}
	else
		typerr=1305;
		
	return typerr==0;
}
bool FBlocConfig::LirePremiereConfig()
{
    if( LirePremierBloc()!=0 ) return false;
	return LireBlocConfig();
}
bool FBlocConfig::LireBlocConfig()
{
	nompartencours	= nompartCFG;//generalites
		nomstrucencours	= nomstruCFG;//application
			InitBlocData((char *)&strucCfg, taillestrucfg );
			typeformat = 1;
			if(LireStructure(0)!=0)
				enrgconfig.Standard();
		nomstrucencours	= nomstruANC;//ancre
			InitBlocData((char *)&strucAnc, taillestruanc);
			typeformat = 2;
			if(LireStructure(0)!=0)
				enrgancre.Standard();
	nompartencours	= nompartLOG;//logiciels
		nomstrucencours = nomstruLOG;
			InitBlocData((char *)&strucLog, taillestrulog );
			typeformat = 3;
			lstenrlog.Nettoyer();
			LireStructureDePartEnContinu();
			if( lstenrlog.TailleListe() == 0 )
				lstenrlog.Standard();
	nompartencours = nompartGRA;//graphique
		nomstrucencours = nomstruGLG;
			InitBlocData((char *)&strucGra, taillestrugra );
			typeformat = 4;
			lstenrgralog.Nettoyer();
			LireStructureDePartEnContinu();
			if( lstenrgralog.TailleListe() == 0 )
				lstenrgralog.Standard();
	nompartencours = nompartLIE;
		nomstrucencours = nomstruGRA;
			InitBlocData((char *)&strucGra, taillestrugra );
			typeformat = 5;
			lstgrhficlie.Nettoyer();
			LireStructureDePartEnContinu();
			if( lstgrhficlie.TailleListe() == 0 )
				lstgrhficlie.Standard();
	nompartencours = nompartCNX;
		nomstrucencours = nomstruCNX;
			InitBlocData((char *)&strucCnx, taillestrucnx );
			typeformat = 6;
			lstconnexion.Nettoyer();
			LireStructureDePartEnContinu();
			if( lstconnexion.TailleListe() == 0 )
				lstconnexion.Standard();
    return true;
}
bool FBlocConfig::Modifier()
{
	bool retresu	= false;
	uint32_t i		= 0;
    if(FichierExiste())
	{
		switch(typeformat)
		{
			case 1 ://cfg appli
					nompartencours = nompartCFG;
					nomstrucencours = nomstruCFG;
					retresu = ModifierStructure(0) == 0;
				break;
			case 2 ://ancre
					nompartencours = nompartCFG;
					nomstrucencours = nomstruANC;
					retresu = ModifierStructure(0) == 0;
				break;
			case 3 ://logiciel
					nompartencours	= nompartLOG;//logiciels
					nomstrucencours = nomstruLOG;
					ptrversboucle = &FBlocConfig::BoucleLogiciel;
					retresu = ModifierPartConfig();
				break;
			case 4 ://graphique
					nompartencours = nompartGRA;//graphique
					nomstrucencours = nomstruGLG;
					ptrversboucle = &FBlocConfig::BoucleGraphique;
					retresu = ModifierPartConfig();
				break;
			case 5 ://fichier lié // 0:travail, 1:config
					nompartencours = nompartLIE;
					nomstrucencours = nomstruGRA;
					ptrversboucle = &FBlocConfig::BoucleFichierLie;
					retresu = ModifierPartConfig();
				break;
			case 6 ://connexion // 0:logiciel 1:travail, 2:config
					nompartencours = nompartCNX;
					nomstrucencours = nomstruCNX;
					ptrversboucle = &FBlocConfig::BoucleConnexion;
					retresu = ModifierPartConfig();
		}
	}
	return retresu;
}
bool FBlocConfig::ModifierConfig( uint8_t codevalmodif )
{
	uint8_t i=1;
	typeformat = 1;
	while( i <= codevalmodif )
	{
		if( codevalmodif & i )
		{
			if( !Modifier() ) return false;
		}
		i = i<<1;
		typeformat++;
	}
    return true;
}
bool FBlocConfig::ModifierPartConfig()
{// nomblocencours, nompartencours, nomstrucencours initialisés
	bool toutok = false;
	Adresse adrpartorigine, adrpartcree, adrblocorigine;
	uint64_t taillepartorigine	= 0;
	uint64_t taillepartcree	= 0;
	std::string nomfictmp, extensionorigine;
	TaillePartEnCours( taillepartorigine );
	AdresseBlocTrouve( &adrblocorigine );
	AdressePartTrouve( &adrpartorigine );
	extensionorigine = ExtensionFichier();
	ExtensionFichier("tmp");
	nomfictmp = NomCompletFichier();
	if(CreerUnFichierAvecPart())
	{
		if((this->*ptrversboucle)())
		{
			TaillePartEnCours( taillepartcree );
			AdressePartTrouve( &adrpartcree );
			ExtensionFichier( extensionorigine );
			if( OuvrirEnLectureEcriture()==0 )
			{
				uint64_t differencetaille = 0;
				if( taillepartcree>taillepartorigine )
				{//étendre la place du part
						differencetaille = taillepartcree - taillepartorigine;
						seekg( adrpartorigine.finpaquet );
						Etendre( differencetaille );
				}
				else
				{
					if( taillepartcree<taillepartorigine )
					{//rétrécir la place du part
						differencetaille = taillepartorigine - taillepartcree; 
						seekg( adrpartorigine.debut );
						if( Retrecir( differencetaille ) )
							ModifierTaille( differencetaille, false );
					}
				}
				close();
				OuvrirEnLectureEcriture();
				if(toutok = (IntegrerFichier( nomfictmp, adrpartcree.debut, taillepartcree, adrpartorigine.debut ) == 0))
				{
					AjusterTailleBloc( adrblocorigine, differencetaille, (taillepartcree>taillepartorigine) );
				}
			}
		}
		FermerFichier();
		ExtensionFichier(extensionorigine);
		std::filesystem::remove( nomfictmp.data() );
	}
	return toutok;
}
bool FBlocConfig::BoucleLogiciel()
{
	for( uint32_t i=0; i<lstenrlog.TailleListe() ;i++)
	{
		enrglogtmp = *lstenrlog.Position(i);
		if( !CreerLaStruc() ) return false;
	}
	return true;
}
bool FBlocConfig::BoucleGraphique()
{
	for( uint32_t i=0; i<lstenrgralog.TailleListe() ;i++)
	{
		enrggraphlogtmp = *lstenrgralog.Position(i);
		if( !CreerLaStruc() ) return false;
	}
	return true;
}
bool FBlocConfig::BoucleFichierLie()
{
	for( uint32_t i=0; i<lstgrhficlie.TailleListe() ;i++)
	{
		enrggraphlogtmp = *lstgrhficlie.Position(i);
		if( !CreerLaStruc() ) return false;
	}
	return true;
}
bool FBlocConfig::BoucleConnexion()
{
	for( uint32_t i=0; i<lstconnexion.TailleListe() ;i++)
	{
		enrgconnexiontmp = *lstconnexion.Position(i);
		if( !CreerLaStruc() ) return false;
	}
	return true;
}
