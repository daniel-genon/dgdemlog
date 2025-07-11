#include "fblocobjetcontexte.h"

FBlocObjetContexte::FBlocObjetContexte( const std::string &cheminprojet )
{
	InitHierarchie();
	InitDescription( cheminprojet, "contexte", "gla" );
    lstobjetsCtx.Nettoyer();
    lstliaisonCtx.Nettoyer();
}
void FBlocObjetContexte::InitHierarchie()
{
	taillebloc	= 0;
	typeformat	= 0;
	taillestruobj	= tailletetestruc + sizeof(DonneesContexte);
	taillestrulia	= tailletetestruc + sizeof(DonneesContexteLiaison);
	entetefichier.type	= 0x584E434F434F4C42;//BLOCOCNX
	entetefichier.genre	= 0x65747865746E6F63;//contexte
	CvtChaineEnBalise("lstobjets" ,&nompartOBJ );//part
		CvtChaineEnBalise("objet" ,&nomstruOBJ );//struc (1 à n)
	CvtChaineEnBalise("lstliaisons" ,&nompartLIA );//part
		CvtChaineEnBalise("liaison" ,&nomstruLIA );//struc (1 à n)
}
void FBlocObjetContexte::FormaterDonnee()
{
	switch(typeformat)
	{
		case 1 ://objets
			InitBlocData((char *)&strucObj, taillestruobj );
			memset(&strucObj,0,taillestruobj);
			enrgobjtmp.CopierVersBloc( strucObj );
			strucObj.clef.taille	= taillestruobj;
			strucObj.clef.nom	= nomstrucencours;			
			break;
		case 2 ://liaisons
			InitBlocData((char *)&strucLia, taillestrulia );
			enrgliatmp.CopierVersBloc( strucLia );
			strucLia.clef.taille	= taillestrulia;
			strucLia.clef.nom	= nomstrucencours;			
			break;
	}
}
void FBlocObjetContexte::DeFormaterDonnee()
{
	switch(typeformat)
	{
		case 1 ://objet
			enrgobjtmp.CopierDepuisBloc( strucObj );
			break;
		case 2 ://liaison
			enrgliatmp.CopierDepuisBloc( strucLia );
			break;
	}
}

bool FBlocObjetContexte::EcrireObjetContexte( const std::string &valeur )
{
	std::string nomfictmp, extensionexiste;
	Adresse valeurblocexiste, valeurblocnouveau;
	if(valeur.empty()) return false;
    if(!FichierExiste()) CreerLeFichier();
	CvtChaineEnBalise( valeur, &nomblocencours );
	if(!CreerUnBloc())
	{
		if(typerr!=1311) return false;
		{
			AdresseBlocTrouve( &valeurblocexiste );
			extensionexiste = ExtensionFichier();
			ExtensionFichier("tmp");
			nomfictmp = NomCompletFichier();
			CreerLeFichier();
			CreerUnBloc();
		}
	}	
	uint32_t i=0;
	nompartencours = nompartOBJ;
	if( !CreerUnPart() ) return false;
		nomstrucencours = nomstruOBJ;
		typeformat=1;
		for( i=0; i<lstobjetsCtx.TailleListe() ;i++)
		{
			enrgobjtmp = *lstobjetsCtx.Position(i);
			if(!CreerLaStruc()) return false;
		}
	i=0;
	nompartencours = nompartLIA;
	if( !CreerUnPart() ) return false;
		nomstrucencours = nomstruLIA;
		typeformat=2;
		for( i=0; i<lstliaisonCtx.TailleListe() ;i++)
		{
			enrgliatmp = *lstliaisonCtx.Position(i);
			if( !CreerLaStruc() ) return false;
		}
	if(!nomfictmp.empty())
	{
		AdresseBlocTrouve( &valeurblocnouveau );
		uint64_t taillebloccree = TailleDuBloc();
		uint64_t tailleblocexiste = valeurblocexiste.finpaquet - valeurblocexiste.debut;
		ExtensionFichier(extensionexiste);
		if( OuvrirEnLectureEcriture()==0 )
		{
			if( taillebloccree>tailleblocexiste )
			{//étendre la place du bloc
					uint64_t etalement = taillebloccree - tailleblocexiste;
					seekg( valeurblocexiste.finpaquet );
					Etendre( etalement );
			}
			else
			{
				if( taillebloccree < tailleblocexiste )
				{//rétrécir la place du bloc
					uint64_t raccourci = tailleblocexiste - taillebloccree; 
					seekg( valeurblocexiste.debut );
					if( Retrecir( raccourci ) )
						ModifierTaille( raccourci, false );
				}
			}
			close();
			OuvrirEnLectureEcriture();
			IntegrerFichier( nomfictmp, valeurblocnouveau.debut, taillebloccree, valeurblocexiste.debut );
			std::filesystem::remove( nomfictmp.data() );
		}
		FermerFichier();
	}
	return true;
}
EnrgObjetCtx *FBlocObjetContexte::PtrEnrgObj(){    return &enrgobjtmp;}
EnrgLiaisonCtx *FBlocObjetContexte::PtrEnrgLia(){    return &enrgliatmp;}
uint32_t FBlocObjetContexte::MaxObjet() const { return lstobjetsCtx.TailleListe(); }
uint32_t FBlocObjetContexte::MaxLiaison() const { return lstliaisonCtx.TailleListe(); }
bool FBlocObjetContexte::ContexteExiste( const std::string &valeur )
{
	if(CvtChaineEnBalise( valeur, &nomblocencours ))
		return BlocExiste();
	return false;
}
bool FBlocObjetContexte::LireObjetContexte( const std::string &valeur )
{
    lstobjetsCtx.Nettoyer();
    lstliaisonCtx.Nettoyer();
//    bool oktrouver = false;
	phrtest = valeur;
	if(CvtChaineEnBalise( valeur, &nomblocencours ))
	{
		if( BlocExiste() )
		{
			nompartencours = nompartOBJ;
			nomstrucencours = nomstruOBJ;
			InitBlocData((char *)&strucObj, taillestruobj );
			typeformat = 1;
			uint32_t i=0;
			while( LireStructure(i) == 0 )
			{
				lstobjetsCtx.Ajouter( strucObj );
				i++;
			}
			nompartencours = nompartLIA;
			nomstrucencours = nomstruLIA;
			InitBlocData((char *)&strucLia, taillestrulia );
			typeformat = 2;
			i=0;
			while( LireStructure(i) == 0 )
			{
				lstliaisonCtx.Ajouter( strucLia );
				i++;
			}
			typerr=0;
		}
	}
	else
		typerr=1305;
		
	return typerr==0;
}
void FBlocObjetContexte::PointerObjet( uint32_t rang ){	enrgobjtmp = *lstobjetsCtx.Position(rang); }
void FBlocObjetContexte::PointerLiaison( uint32_t rang ){	enrgliatmp = *lstliaisonCtx.Position(rang); }
void  FBlocObjetContexte::AjouterObjet(){ lstobjetsCtx.Ajouter( enrgobjtmp.Donnees() ); }
void  FBlocObjetContexte::AjouterLiaison(){ lstliaisonCtx.Ajouter( enrgliatmp.Donnees()); }
