/*
    v 4.1
*/
#include "dgficbloc.h"

DGFicBloc::DGFicBloc()
{
/** initialisation pour l'entete générale des fichiers IFF **/
	tailleenrgbloc	= sizeof(uint64_t)+TAILLECHAINEBALISE;
	tailleenrgpart	= sizeof(uint64_t)+TAILLECHAINEBALISE;
	tailleentete	= sizeof(uint64_t)*2;
	tailletetestruc	= sizeof(uint32_t)+TAILLECHAINEBALISE;
    posoctetadebutfic	= 0;
	tailleadresse	= sizeof(uint64_t)*4;
	indicemaxi	= 0;
	tailledata	= 0;
	Razadrbloc();
	Razadrpart();
	memset( &balisevide,0,TAILLECHAINEBALISE);
	nomblocencours = balisevide;
	nompartencours = balisevide;
	nomstrucencours = balisevide;
}
DGFicBloc::~DGFicBloc(){}
void DGFicBloc::InitHierarchie()
{
	entetefichier.type	= 0x41544144434F4C42;//BLOCDATA
	entetefichier.genre	= 0x3432333065676164;//dage0324
}
void DGFicBloc::InitBlocData ( char *vadrpart, uint32_t vtaille )
{
	taillestruc	= vtaille;
	adrstruc	= vadrpart;
}

/*************************************
	Fonctions d'écriture
**************************************/
 
bool DGFicBloc::CreerUnFichierAvecPart()
{// nomblocencours, nompartencours initialisés
	CreerLeFichier();
	if(CreerBloc())
		return CreerPart();
    return false;
}
void DGFicBloc::CreerLeFichier()
{
	EcrireEntete();
    FermerFichier();
}
bool DGFicBloc::CreerUnBloc( const std::string &nombloc )
{
	if(!CvtChaineEnBalise( nombloc, &nomblocencours )) return (typerr=1305) == 0;
	return CreerBloc();
}
bool DGFicBloc::CreerUnBloc()
{
	if(memcmp(&nomblocencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1305) == 0;
	return CreerBloc();
}
bool DGFicBloc::CreerUnPart( const std::string &nombloc,  const std::string &nompart )
{
	if(!CvtChaineEnBalise( nombloc, &nomblocencours )) return (typerr=1305) == 0;
	if(!CvtChaineEnBalise( nompart, &nompartencours )) return (typerr=1306) == 0;
	return CreerPart();
}
bool DGFicBloc::CreerUnPart()
{
	if(memcmp(&nomblocencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1305) == 0;
	if(memcmp(&nompartencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1306) == 0;
	return CreerPart();
}
bool DGFicBloc::CreerLaStruc( const std::string &nombloc, const std::string &nompart, const std::string &nomstruc )
{
	if(!CvtChaineEnBalise( nombloc, &nomblocencours )) return (typerr=1305) == 0;
	if(!CvtChaineEnBalise( nompart, &nompartencours )) return (typerr=1306) == 0;
	if(!CvtChaineEnBalise(  nomstruc, &nomstrucencours  )) return (typerr=1307) == 0;
	return CreerStruc();
}
bool DGFicBloc::CreerLaStruc()
{
	if(memcmp(&nomblocencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1305) == 0;
	if(memcmp(&nompartencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1306) == 0;
	if(memcmp(&nomstrucencours,&balisevide,TAILLECHAINEBALISE)==0) return (typerr=1307) == 0;
	return CreerStruc();
}

/*************************************
	Fonctions lecture
**************************************/
uint16_t DGFicBloc::LirePremierBloc()
{
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		typerr = 1128;
		posoctetadebutfic = tailleentete;
		seekg(posoctetadebutfic);
		if(good())
		{
			LireValeur();
			if(typerr==0)
				nomblocencours = blocbloc.nom ;
		}
		clear();
	}
	FermerFichier();
	return typerr;
}

uint16_t DGFicBloc::LirePremiereStructure()
{
//	return LirePositionStructure(0);
	return 1;
}
uint16_t DGFicBloc::LirePositionStructure( const std::string &nombloc, const std::string &nompart, const std::string &nomstruc )
{
//	InitNumPack( posenrg, true );
//	InitNumPack( pospack );
//	return Lire( posstruc );
	return 1;
}

uint16_t DGFicBloc::Lire( const std::string &nombloc, 
							const std::string &nompart, 
							const std::string &nomstruc, 
							uint32_t norang )
{
	if(!CvtChaineEnBalise( nombloc, &nomblocencours )) return 1305;
	if(!CvtChaineEnBalise( nompart, &nompartencours )) return 1306;
	if(!CvtChaineEnBalise(  nomstruc, &nomstrucencours  )) return 1307;
	return LireStructure( norangstruc );
}
uint16_t DGFicBloc::LireStructure( int32_t norang )
{
/**	&nomblocencours, &nompartencours et &nomstrucencours doivent être initialisés au préalable; **/
	norangstruc = norang;
	if(LireStructure()==0)
	{
		DeFormaterDonnee();
	}
	return typerr;
}
uint16_t  DGFicBloc::ModifierStructure( int32_t norang )
{
/**	&nomblocencours, &nompartencours et &nomstrucencours doivent être initialisés au préalable; **/
	norangstruc = norang;
	ModifierStruc();
	if( typerr==1313 && modeokcreer )
	{
		CreerStruc();
	}
	return typerr;
}


//bool DGFicBloc::LirePositionPack( std::string &rtnompack, uint32_t position )
//{
	//InitEnrgBloc( true );
	//if(OuvrirEnLecture()==0)
	//{
		//typerr = 1128;
		//posoctetadebutfic = tailleentete;
		//seekg(posoctetadebutfic);
		//if(good())
		//{
			//uint32_t positionlue = 0;
			//do{
				//if(!LireEnContinu()) break;
				//if(positionlue==position) break;
				//positionlue++;
				//posoctetadebutfic	+= tailleenrgbloc + blocbloc.taille;
				//seekg(posoctetadebutfic);
				//if(!good()) typerr=1128;
			//}while(typerr==0);
			//if(typerr==0)
			//{
				//rtnompack.assign(4,' ');
				//memcpy(rtnompack.data(),&blocbloc.nom,TAILLECHAINEBALISE);
			//}
		//}
		//clear();
	//}
	//FermerFichier();
	//return typerr==0;
//}
//bool DGFicBloc::LirePositionENRG( const uint16_t pospack, std::string &rtnomenrg, uint32_t position )
//{
	//InitEnrgBloc( true );
	//if(OuvrirEnLecture()==0)
	//{
		//if(TrouverBloc())
		//{
			//Razadrpart();
			//posoctetadebutfic = adrbloc.fin;
			//adrpart.limite = adrbloc.finpaquet;
			//InitEnrgPart( true );
			//seekg(posoctetadebutfic);
			//if(good())
			//{
				//uint32_t positionlue = 0;
				//do{
					//if(!LireEnContinu()) break;
					//if(positionlue==position) break;
					//positionlue++;
					//posoctetadebutfic	+= tailleenrgpart + blocbloc.taille;
					//seekg(posoctetadebutfic);
					//if(!good()) typerr=1128;
				//}while(typerr==0);
				//if(typerr==0)
				//{
					//rtnomenrg.assign(4,' ');
					//memcpy(rtnomenrg.data(),&blocbloc.nom,sizeof(blocbloc.nom));
				//}
			//}
			//else typerr=1128;
		//}
		//else typerr = 1312;
		//clear();
	//}
	//FermerFichier();
	//return typerr==0;
//}
bool DGFicBloc::BlocExiste()
{
/**
 * initialisations préalables et impératives :
	* nomblocencours
	* tailleentete
**/
	typerr = 1312;
	if( nomblocencours.v[0] == 0 ) return false;
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		if(TrouverBloc()) typerr=0;
	}
	FermerFichier();
	return typerr==0;
}
bool DGFicBloc::AjusterTailleBloc( const Adresse adrblocrectifie, uint64_t dimdifference, bool sens )
{//le fichier est ouvert en lecture/ecriture.
	InitEnrgBloc( true );
	typerr=1125;
	seekg(adrblocrectifie.debut);
	if(good())
	{
		LireValeur();
		if(typerr==0)
		{
//			dimdifference -= tailleenrgpart;
			if(sens)
				blocbloc.taille += dimdifference;
			else
			{
				if(blocbloc.taille>dimdifference)
					blocbloc.taille -= dimdifference;
				else
					blocbloc.taille =0;
			}
			typerr=1125;
			seekg(adrblocrectifie.debut);
			if(good())
				EcrireValeur();
		}
	}
	return typerr==0;
}
uint64_t DGFicBloc::TailleDuBloc()
{// nomblocencours est initialisé
	if( nomblocencours.v[0] != 0 )
	{
		InitEnrgBloc( true );
		if(OuvrirEnLecture()==0)
		{
			if(TrouverBloc())
				return  adrbloctrv.finpaquet - adrbloctrv.debut;
		}
		FermerFichier();
	}
	return 0;
}
uint64_t DGFicBloc::TailleDuBlocTrouve()
{// TrouverBloc a été appelé récemment
	return adrbloctrv.finpaquet - adrbloctrv.debut;
}
uint16_t DGFicBloc::TaillePartEnCours( uint64_t &rettaille )
{//nomblocencours, nompartencours doivent être initialisés.
	InitEnrgBloc( true );
	rettaille = 0;
	if(OuvrirEnLecture()==0)
	{
		typerr = 1115;
		if(TrouverBloc())
		{
			InitEnrgPart( true );
			if(TrouverPart()==1314)
			{
				rettaille = adrparttrv.finpaquet - adrparttrv.debut;
//				rettaille = blocbloc.taille;
			}
		}
	}
	FermerFichier();
	return typerr;	
}
void DGFicBloc::AdresseBlocTrouve( Adresse *valret )
{
	memcpy( valret, &adrbloctrv, tailleadresse );
}
void DGFicBloc::AdressePartTrouve( Adresse *valret )
{
	memcpy( valret, &adrparttrv, tailleadresse );
}

bool DGFicBloc::ListerLesBlocs( std::vector<std::string> *ptrlstchaine )
{
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		typerr = 1128;
		posoctetadebutfic = tailleentete;
		seekg(posoctetadebutfic);
		if(good())
		{
			std::string tmpphr('0',TAILLECHAINEBALISE);
			while(LireEnContinu())
			{
				memcpy(tmpphr.data(),&blocbloc.nom,TAILLECHAINEBALISE);
				ptrlstchaine->push_back(std::string (tmpphr.data()));
				posoctetadebutfic	+= tailleenrgbloc + blocbloc.taille;
				seekg(posoctetadebutfic);
				if(!good()) break;
			}
			if(ptrlstchaine->size()>0)
				typerr = 0;
			else
				typerr = 1312;
		}
		clear();
	}
	FermerFichier();
	return typerr==0;
}

bool DGFicBloc::ListerLesParts( const std::string &nombloc, std::vector<std::string> *ptrlstchaine )
{
	if(nombloc.empty()) return (typerr=1305) == 0;
	CvtChaineEnBalise( nombloc, &nomblocencours );
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		if(TrouverBloc())
		{
			Razadrpart();
			posoctetadebutfic = adrbloc.fin;
			adrpart.limite = adrbloc.finpaquet;
			InitEnrgPart( true );
			seekg(posoctetadebutfic);
			if(good())
			{
				std::string tmpphr('0',TAILLECHAINEBALISE);
				do
				{
					if(LireEnContinu())
					{
						memcpy(tmpphr.data(),&blocbloc.nom,TAILLECHAINEBALISE);
						ptrlstchaine->push_back(tmpphr);
						posoctetadebutfic	+= tailleenrgpart + blocbloc.taille;
						if(posoctetadebutfic<adrpart.limite)
						{
							seekg(posoctetadebutfic);
							if(!good()) typerr=1128;
						}
						else typerr=1309;
					}
				}while(typerr==0);
				if(ptrlstchaine->size()>0) typerr = 0; else typerr = 1315;
			}
			else typerr=1128;
		}
		else typerr = 1312;
			
		clear();
	}
	FermerFichier();
	return typerr==0;
}
/*************************************
	Fonctions recherche
**************************************/
bool DGFicBloc::ChercherTexte( const std::string &ptrchainestock, const uint16_t pospack, const uint16_t posenrg )
{
	typerr = 1115;
	rtnumstruc = 0;
	InitEnrgBloc( true );
	if(OuvrirEnLectureEcriture()==0)
	{
		if(TrouverBloc())
		{
			InitEnrgPart( true );
			if(TrouverPart()==1314)
			{
				memset( &rtvaleurtmp, 0, tailletetestruc );
				posoctetadebutfic	= adrpart.fin;
				uint64_t limite		= adrpart.finpaquet;
				bool tourne = true;
				do{
					tourne = false;
					ReinitEnrg((char *)&rtvaleurtmp,tailletetestruc);
					seekg( posoctetadebutfic );
					if(good())
					{
						LireValeur();
						if(typerr==0)
						{
							ReinitEnrg((char *)adrstruc,rtvaleurtmp.taille);
							seekg(-tailletetestruc, std::ios_base::cur );
							LireValeur();
							if(typerr==0)
							{
								DeFormaterDonnee();
								if(phrtest.compare(ptrchainestock)!=0)
								{
									posoctetadebutfic += rtvaleurtmp.taille;
									if(posoctetadebutfic < limite)
									{
										rtnumstruc++;
										tourne = true;
									}
									else
										typerr = 1313;
								}
							}
						}
					}
					else
						typerr=1128;
				}while(tourne);
			}
		}
	}
	FermerFichier();
	return typerr==0;
}

/*************************************
	Fonctions privées
**************************************/
bool DGFicBloc::CreerBloc()
{
	typerr = 1115;
	InitEnrgBloc( true );
	if(OuvrirEnLectureEcriture()==0)
	{
		if(!TrouverBloc())
		{
			RazBloc();
			memcpy(&blocbloc.nom,&nomblocencours,TAILLECHAINEBALISE);
			blocbloc.taille	= 0;
			adrbloc.debut	= std::filesystem::file_size( nomcomplet.data() );
			adrbloctrv.debut	= adrbloc.debut;
			adrbloctrv.fin		= adrbloc.debut + tailleenrgbloc;
			adrbloctrv.finpaquet	= adrbloctrv.fin;
			Inserer(adrbloc.debut);
		}
		else
			typerr = 1311;
	}
	FermerFichier();
	return typerr == 0;
}
bool DGFicBloc::CreerPart()
{
	typerr = 1115;
	InitEnrgBloc( true );
	if(OuvrirEnLectureEcriture()==0)
	{
		if(TrouverBloc())
		{
			NettoyerStocAdrMaj();
			InitEnrgPart( true );
			stocadrmaj.push(adrbloc.debut);
			switch(TrouverPart())
			{
				case 1309 : adrpart.debut = adrpart.limite;typerr=0;break;
				case 1315 : adrpart.debut = std::filesystem::file_size( nomcomplet.data() );typerr=0;break;
			}
			clear();
			if(typerr==0)
			{
				RazPart();
				memcpy(&blocbloc.nom,&nompartencours,TAILLECHAINEBALISE);
				blocbloc.taille	= 0;
//				adrparttrv.debut	= adrpart.debut;
//				adrparttrv.fin		= adrpart.debut + tailleenrgpart;
//				adrparttrv.finpaquet	= adrparttrv.fin;
				if(Inserer(adrpart.debut)==0)
				{
					if(!stocadrmaj.empty())
					{
						tailledata = tailleenrgpart;
						MajTailleMarque();
					}
				}
			}
		}
		else
			typerr = 1312;
	}
	FermerFichier();
	return typerr == 0;
}
bool DGFicBloc::CreerStruc()
{
	typerr = 1115;
	InitEnrgBloc( true );
	if(OuvrirEnLectureEcriture()==0)
	{
		if(TrouverBloc())
		{
			NettoyerStocAdrMaj();
			stocadrmaj.push(adrbloc.debut);
			InitEnrgPart( true );
			if(TrouverPart()==1314)
			{
				stocadrmaj.push(adrpart.debut);
				FormaterDonnee();
				ReinitEnrg((char *)adrstruc,taillestruc);
				if(Inserer(adrpart.finpaquet)==0)
				{
					if(!stocadrmaj.empty())
					{
						tailledata = taillestruc;
						MajTailleMarque();
					}
				}
				
			}
		}
	}
	FermerFichier();
	return typerr == 0;
}
bool DGFicBloc::ModifierStruc()
{//nomblocencours, nompartencours, nomstrucencours, norangstruc doivent être initialisés.
	InitEnrgBloc( true );
	if(OuvrirEnLectureEcriture()==0)
	{
		if(PointerStruc())
		{ 			
//iostate titi = rdstate();
			FormaterDonnee();
			if( rtvaleurtmp.taille == taillestruc )
			{
				ReinitEnrg((char *)adrstruc,taillestruc);
				EcrireValeur();
			}
			else
			{
///////////   ICI RECOUVRIR la STRUCTURE
				uint64_t poscur = tellg();//adr struc
				uint64_t decaler = abs( taillestruc - rtvaleurtmp.taille );
				if( taillestruc < rtvaleurtmp.taille )
				{
					Retrecir( decaler );
					tailledata = -decaler;
				}
				else
				{
					Etendre( decaler );
					tailledata = decaler;
				}
				if(typerr==0)
				{
					seekp(poscur);
					if(good())
					{	
						ReinitEnrg((char *)adrstruc,taillestruc);
						EcrireValeur();
						MajTailleMarque();
					}
					else
					 typerr = 1116;
				}
			}
		}
	}
	FermerFichier();
	return typerr;
}

//bool DGFicBloc::SupprimerStruc()
//{
	//InitEnrgBloc( true );
	//std::uintmax_t total	= std::filesystem::file_size( nomcomplet.data() );
	//if(OuvrirEnLectureEcriture()==0)
	//{
		//if(PointerStruc())
		//{
			//uint64_t decaler = rtvaleurtmp.taille;
			//Retrecir( decaler );
			//tailledata = -decaler;
			//MajTailleMarque();
		//}
	//}
	//FermerFichier();
	//if(typerr==0)
		//std::filesystem::resize_file( nomcomplet.data(), total-rtvaleurtmp.taille);
	//return typerr;
//}
void DGFicBloc::EcrireEntete()
{
	memset(&entete,0,tailleentete);
    ReinitEnrg((char *)&entetefichier,tailleentete);
    OuvrirEnREcriture();
    EcrireEnContinu();
}

/*************************************
	Fonctions d'ouverture (création) des balises
**************************************/
//void DGFicBloc::OuvrirEnrg()
//{
	//memset(&blocbloc,0,tailleenrgbloc);
    //ReinitEnrg((char *)&blocbloc,tailleenrgbloc);
    //blocbloc.nom	= lstidstruct.at(indblocencours);//nomenrg
    //blocbloc.taille = tailledata;
    //EcrireEnContinu();
//}


/*************************************
	Fonctions de lecture
**************************************/
uint16_t DGFicBloc::LireEntete()
{
    if(FichierExiste())
    {
        ReinitEnrg((char *)&entete,tailleentete);
        if(FicBase::Lire()==0)
        {
            if(std::memcmp( &entete, &entetefichier , tailleentete)==0)
                typerr=0;
            else
                typerr=1303;// n'est pas fichier bloc souhaité
        }
        else
            typerr=1302;// problème de lecture
    }
    else
        typerr=1301;// fichier inconnu

    return typerr;
}
uint16_t DGFicBloc::LireStructure()
{
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		if(PointerStruc())
		{
			ReinitEnrg((char *)adrstruc,rtvaleurtmp.taille);
			LireValeur();
		}
	}
	NettoyerStocAdrMaj();
	FermerFichier();
	return typerr;
}
bool DGFicBloc::PointerStruc()
{
/**
 * initialisations préalables et impératives :
	* nomblocencours, nompartencours
	* tailleentete
	* nomstrucencours
	* norangstruc de struc si plusieurs occurences prévue

**/
	typerr = 1115;
	if(TrouverBloc())
	{
		NettoyerStocAdrMaj();
		stocadrmaj.push(adrbloc.debut);
		InitEnrgPart( true );
		if(TrouverPart()==1314)
		{
			stocadrmaj.push(adrpart.debut);
			if(TrouverStruc()==0)
			{
				seekg(-tailletetestruc, std::ios_base::cur );
			}
		}
	}
	return typerr==0;
/**
 * retour si ok OK :
	* curseur positionné sur adresse début bloc structure
**/
}
uint16_t DGFicBloc::LireStructureDePartEnContinu()
{//nomblocencours, nompartencours, nomstrucencours, doivent être initialisés.
	InitEnrgBloc( true );
	if(OuvrirEnLecture()==0)
	{
		typerr = 1115;
		if(TrouverBloc())
		{
			InitEnrgPart( true );
			if(TrouverPart()==1314)
			{				
				bool tourne = true;
				posoctetadebutfic	= adrpart.fin;
				uint64_t limite		= adrpart.finpaquet;
				ReinitEnrg( (char *)adrstruc, taillestruc );
				do{
					tourne = false;
					seekg( posoctetadebutfic );
					if(good())
					{
						LireValeur();
						if(typerr==0)
						{
							memcpy( &rtvaleurtmp, adrstruc, tailletetestruc );
							if(memcmp( &nomstrucencours, &rtvaleurtmp.nom, TAILLECHAINEBALISE)==0)
								AjouterDonneeVersListe();
							posoctetadebutfic += rtvaleurtmp.taille;
							if( posoctetadebutfic < limite )
								tourne = true;
						}
					}
					else
						typerr=1128;
				}while(tourne);
			}
		}
		else
			typerr=1128;
	}
	FermerFichier();
	return typerr;
}

void DGFicBloc::MajTailleMarque()
{
/**
 * initialisations préalables et impératives :
	* stocadrmaj
	* tailledata
**/
	Enrg64	bloctmp;
	ReinitEnrg((char *)&bloctmp,sizeof(uint64_t)+sizeof(uint32_t));
	while (!stocadrmaj.empty())
	{
		posoctetadebutfic = stocadrmaj.top();
		stocadrmaj.pop();
		seekg( posoctetadebutfic );
		if(good())
		{
			LireValeur();
			if(typerr==0)
			{
				bloctmp.taille += tailledata;
				seekp( posoctetadebutfic );
				EcrireValeur();
				if(typerr!=0) break;
			}
		}
	}
}

/*************************************
	Fonctions de pointage
**************************************/
bool DGFicBloc::TrouverBloc()
{
/**
 * initialisations préalables et impératives :
	* nomblocencours
	* tailleentete
**/
	typerr = 1128;
	Razadrbloc();
	posoctetadebutfic = tailleentete;
	ChaineBalise nomtmp;
	memcpy(&nomtmp,&nomblocencours,TAILLECHAINEBALISE);
	seekg(posoctetadebutfic);
	if(good())
	{
		while(LireEnContinu())
		{
			if(memcmp(&nomtmp,&blocbloc.nom,TAILLECHAINEBALISE)==0)
			{
				adrbloc.debut		= posoctetadebutfic;
				adrbloc.fin			= adrbloc.debut + tailleenrgbloc;
				adrbloc.finpaquet	= adrbloc.fin + blocbloc.taille;
				adrbloctrv = adrbloc;
				return true;
			}
			posoctetadebutfic	+= tailleenrgbloc + blocbloc.taille;
			seekg(posoctetadebutfic);
			if(!good()) break;
		}
		typerr = 1312;
	}
	clear();
	return false;
/**
 * affectation des variables si OK :
	* adrbloc.debut
	* adrbloc.fin
	* adrbloc.finpaquet
**/
}
uint16_t DGFicBloc::TrouverPart()
{
/**
 * initialisations préalables et impératives :
	* nompartencours
	* adrbloc.fin
	* adrbloc.finpaquet
**/
	
	Razadrpart();
	posoctetadebutfic = adrbloc.fin;
	adrpart.limite = adrbloc.finpaquet;
	ChaineBalise nomtmp;
	memcpy(&nomtmp,&nompartencours,TAILLECHAINEBALISE);
	seekg(posoctetadebutfic);
	if(!good()) return typerr=1128;
	while(LireEnContinu())
	{
		if(memcmp(&nomtmp,&blocbloc.nom,TAILLECHAINEBALISE)==0)
		{
			adrpart.debut		= posoctetadebutfic;
			adrpart.fin			= adrpart.debut + tailleenrgpart;
			adrpart.finpaquet	= adrpart.fin + blocbloc.taille;
			adrparttrv			= adrpart;
			return typerr=1314;
		}
		posoctetadebutfic	+= tailleenrgpart + blocbloc.taille;
		if(posoctetadebutfic>=adrpart.limite) return typerr=1309;
		seekg(posoctetadebutfic);
		if(!good()) break;
	}
	return typerr = 1315;
/**
 * affectation des variables si OK :
	* adrpart.debut
	* adrpart.fin
	* adrpart.finpaquet
**/
}
//uint16_t DGFicBloc::TrouverBlocRang()
//{
///**
 //* initialisations préalables et impératives :
	//* adrpart
	//* nomstrucencours
//**/
	//memset(&rtvaleurtmp,0,tailletetestruc);
	//posoctetadebutfic	= adrpart.fin;
	//uint64_t limite		= adrpart.finpaquet;
	//ReinitEnrg((char *)&rtvaleurtmp,tailletetestruc);
	//uint32_t i=0;
	//bool tourne = true;
	//do{
		//tourne = false;
		//seekg( posoctetadebutfic );
		//if(good())
		//{
			//LireValeur();
			//if(typerr==0)
			//{
				//if(i<norangstruc)
				//{
					//posoctetadebutfic += rtvaleurtmp.taille;
					//if(posoctetadebutfic >= limite)
					//{
						//typerr = 1313;
					//}
					//else
					//{
						//i++;
						//tourne = true;
					//}
				//}
				//else
					//typerr=0;
			//}
		//}
		//else
			//typerr=1128;
	//}while(tourne);
	//return typerr;
///**
 //* retour si OK :
	//* rtvaleurtmp
	//* typerr = 0 si bloc trouvé
//**/
	
//}

uint16_t DGFicBloc::TrouverStruc()
{
/**
 * initialisations préalables et impératives :
	* adrpart
	* nomstrucencours
	* norangstruc de strucc si plusieurs occurences prévue
**/
	memset(&rtvaleurtmp,0,tailletetestruc);
	posoctetadebutfic	= adrpart.fin;
	uint64_t limite		= adrpart.finpaquet;
	ReinitEnrg((char *)&rtvaleurtmp,tailletetestruc);
	uint32_t i=0;
	bool tourne = true;
	do{
		tourne = false;
		seekg( posoctetadebutfic );
		if(good())
		{
			LireValeur();
			if(typerr==0)
			{
				typerr = 1316;
				if(memcmp(&nomstrucencours,&rtvaleurtmp.nom,TAILLECHAINEBALISE)==0)
				{
					if(i==norangstruc)
						typerr=0;
					else
						i++;
				}
				if(typerr!=0)
				{
					posoctetadebutfic += rtvaleurtmp.taille;
					if(posoctetadebutfic < limite)
						tourne = true;
					else
						typerr = 1313;
				}
			}
		}
		else
			typerr=1128;
	}while(tourne);
	return typerr;
/**
 * retour si OK :
	* rtvaleurtmp
	* typerr = 0 si bloc trouvé
**/
	
}

//std::string DGFicBloc::ValeurChaine() const {    return std::string((char *)&tamponchaine);}
//void DGFicBloc::RecupererChaine( std::string &cible, char *psource )
//{
	//cible = std::string(psource);
//}
//bool DGFicBloc::Lireblocblociculier ()
//{
        //if((tailledereference<blocbloc.taille)&&(tailledereference!=0))
            //ReinitEnrg( adrpartparticulier, tailledereference );
        //else
            //ReinitEnrg( adrpartparticulier, blocbloc.taille );
    //return LireEnContinu();
//}
//bool DGFicBloc::LireEnrg()
//{
    //InitEnrgPart();
    //if(LireEnContinu())
        //return (blocbloc.balise==nomenrg);

    //return false;
//}
//bool DGFicBloc::LireListe()
//{
    //InitEnrgNomListe();
    //if(LireEnContinu())
    //{
        //if(blocnomlist.balise==nomliste)
        //{
           //posoctetadebutfic += sizeof(blocnomlist);
           //return true;
        //}
    //}
    //return false;
//}
//bool DGFicBloc::OkNomListe()
//{
	//return blocnomlist.balise == lstbalise.at(2).first;
//}
	    
//unsigned long DGFicBloc::TailleNomListe(){    return blocnomlist.taille;}
//unsigned long DGFicBloc::TailleBlocData(){    return blocdata.taille;}
//bool DGFicBloc::LireBloc()
//{
    //InitEnrgBloc();
    //if(LireEnContinu())
    //{
        //if(blocdata.balise==nombalise)
        //{
            //posoctetadebutfic += sizeof(blocdata);
            //return true;
        //}
    //}
    //return false;
//}
//bool DGFicBloc::PointerProchainNomListe()
//{
    //posoctetadebutfic += blocnomlist.taille;
    //return PointerOctetCible();
//}
//bool DGFicBloc::PointerProchainEnrg()
//{
    //posoctetadebutfic += sizeof(blocdata);
    //posoctetadebutfic += blocbloc.taille;
    //return PointerOctetCible();
//}
//bool DGFicBloc::RetourPointageDeBloc(){    return RePositionnerpointage(-sizeof(blocdata));}
//bool DGFicBloc::PointerDebutListe()
//{
    //ReinitEnrg((char *)&entete,sizeof(entete));
    //OuvrirEnLecture();
    //LireEnContinu();
    //posoctetadebutfic = sizeof(entete);
    //InitEnrgListe();
    //while(LireEnContinu())
    //{
        //posoctetadebutfic += sizeof(blocnomlist);
        //if(baliselist.balise==nombornelist)
        //{
            //if(nomliste!=0)
            //{
                //if(LireListe()) return true;
                //InitEnrgListe();
            //}
            //else
                //return true;
        //}
        //PasserListeSuivante();
    //}
    //FermerFichierContinu();
    //return false;
//}
void DGFicBloc::NettoyerStocAdrMaj()
{
	while(!stocadrmaj.empty()) stocadrmaj.pop();
}
void DGFicBloc::InitEnrgBloc( bool raz )
{
	ReinitEnrg((char *)&blocbloc,tailleenrgbloc);
	if(raz) RazBloc();
}
void DGFicBloc::InitEnrgPart( bool raz )
{
	ReinitEnrg((char *)&blocbloc,tailleenrgpart);
	if(raz) RazPart();
}
void DGFicBloc::RazBloc()
{
	memset(&blocbloc,0,tailleenrgbloc);
}
void DGFicBloc::RazPart()
{
	memset(&blocbloc,0,tailleenrgpart);
}
void DGFicBloc::Razadrbloc()
{
	memset(&adrbloc,0,tailleadresse);
}
void DGFicBloc::Razadrpart()
{
	memset(&adrpart,0,tailleadresse);
}
bool DGFicBloc::CvtChaineEnBalise( const std::string &vchaine, ChaineBalise *rtbalise )
{
	if(vchaine.empty()) return false;
	if(vchaine.size()<TAILLECHAINEBALISE)
	{
		memset( rtbalise,0,TAILLECHAINEBALISE);
		memcpy( rtbalise , vchaine.data(), vchaine.size() );
	}
	else
		memcpy( rtbalise, vchaine.data(), TAILLECHAINEBALISE );
	
	return true;
}

void DGFicBloc::AutoriserCreationEnModification() { modeokcreer = true; }
void DGFicBloc::InterdireCreationEnModification() { modeokcreer = false; }
//void DGFicBloc::InitTamponChaine()
//{
    //memset(&tamponchaine,0,sizeof(tamponchaine));
    //ReinitEnrg((char *)&tamponchaine[0],blocdata.taille);
//}
//bool DGFicBloc::ReEcrireBloc()
//{
    //volumeexpansion = abs(differencedetaille);
    //Decaler();
    //if(!PointerObjet()) return false;
    //Superposer();
    //EcrireTailleFichier();
    //return true;
//}
//bool DGFicBloc::Ecrire(bool FACancien)
//{
    //EcrireEnteteFichier(FACancien);
    //EcrirePreBalise();
    //EcrireLeBloc();
    //typerr=0;
    //return true;
//}
//bool DGFicBloc::Modifier()
//{// initialiser : phrtest;
    //differencedetaille = 0;
    //if(PointerObjet())
    //{
        //unsigned long vtanci = TailleBlocData();
        //if(vtanci==tailledereference)
            //return RemplacerBloc();
        //else
        //{
            //differencedetaille = abs(tailledereference-vtanci);
            //if(vtanci<tailledereference)
            //{
				//long	posenrg = tellg();
				//if(posenrg!=-1)
				//{
					//posoctetadebutfic = posenrg-differencedetaille;
					//FermerFichierContinu();
					//return ReEcrireBloc();
				//}
				//else
				//{
					//noerreur=1304;
					//return false;
				//}
            //}
            //else
                //return RemplacerBloc();
        //}
    //}
    //else
        //return Ecrire();
//}

/****************************************
        Fonctions virtuelles vides
****************************************/

void DGFicBloc::FormaterDonnee(){typerr = 1112;}
void DGFicBloc::DeFormaterDonnee(){typerr = 1112;}
void DGFicBloc::AjouterDonneeVersListe(){typerr = 1112;}

/****************************************
 obsolète
 * 
 * 
bool DGFicBloc::PointerProchaineBalise()
{
    posoctetadebutfic += sizeof(blocdata);
    posoctetadebutfic += blocdata.taille;
    return PointerOctetCible();
}
*****************************************/
