#include "fblocprojet.h"

FBlocProjet::FBlocProjet()
{
	taillebloc		= TAILLEDATEDG + TAILLECHAINENOM * 2;
	NomFichier("projet");
   	ExtensionFichier("gla");
    ViderEnrgprojet();
    InitEnrg((char *)&enrgB, taillebloc);
    ViderEnrg();
}
FBlocProjet::~FBlocProjet(){}
void FBlocProjet::Lister( DGChaineListe &lstvaleur ){ ListerChaine(lstvaleur.PtrChaine(), (char*)&enrgB.nom , TAILLECHAINENOM); }
void FBlocProjet::ListerContexte( DGChaineListe &lstvaleur ){ fichiercontexte.Lister(lstvaleur); }

bool  FBlocProjet::CreerLeProjet(const EnrgProjet &venrgprojet)
{
	enrgprojet = venrgprojet;
	if(EcrireProjet())
	{
		CreerEnvironnementProjet();
		return true;
	}
	return false;
}
bool FBlocProjet::EcrireProjet()
{
	if(!FichierExiste())
		CreerVide();
	FormaterDonnee();
    return Ecrire()==0;
}
void FBlocProjet::FormaterDonnee()
{
    ViderEnrg();
    ConvStrVersBin( enrgprojet.nom, &enrgB.nom );
    ConvStrVersBin( enrgprojet.commentaire, &enrgB.commentaire );
    enrgB.dcrea = enrgprojet.dcreation;
}
void FBlocProjet::DeFormaterDonnee()
{
	ViderEnrgprojet();
    enrgprojet.nom = std::string((char *)&enrgB.nom);
    enrgprojet.dcreation = enrgB.dcrea;
    enrgprojet.commentaire = std::string((char *)&enrgB.commentaire);
    CreerCheminDeCeProjet();
    fichiercontexte.InitialiserCheminProjet( &cheminduprojet, enrgprojet.nom );
}
std::string FBlocProjet::LireCommentaire() const { return enrgprojet.commentaire; }
std::string FBlocProjet::Nom() const { return enrgprojet.nom; }
struct tm *FBlocProjet::LireDate() const
{
	struct tm *rdate;
	if(enrgprojet.dcreation.j==0)
	{
		time_t datejour;
		time (&datejour);
		rdate = localtime (&datejour);
	}
	rdate->tm_mday	= enrgprojet.dcreation.j;
	rdate->tm_year	= enrgprojet.dcreation.a;
	rdate->tm_mon	= enrgprojet.dcreation.m;
	return rdate;
}
std::string FBlocProjet::LireComContexte() const { return fichiercontexte.LireCommentaire(); }
struct tm *FBlocProjet::LireDateContexte()
{
	EnrgDate	tmpdate = fichiercontexte.LireDate();
	struct tm	*rdate;
	if(tmpdate.j==0)
	{
		time_t datejour;
		time (&datejour);
		rdate = localtime (&datejour);
	}
	rdate->tm_mday	= tmpdate.j;
	rdate->tm_year	= tmpdate.a;
	rdate->tm_mon	= tmpdate.m;
	return rdate;
}

bool FBlocProjet::LireProjet( const std::string &valeur )
{
	ViderEnrgprojet();
	phrtest = valeur;
	if(!ChercherChaine((char*)&enrgB.nom , TAILLECHAINENOM)) return false;
	DeFormaterDonnee();
	return true;
}
//bool FBlocProjet::ListerContexte( DGChaineListe &lstvaleur )
//{
    //fichiercontexte.InitDescription( CheminFichier() );
    //return fichiercontexte.Lister( lstvaleur );
//}

bool FBlocProjet::LirePremierProjet()
{
	bool ok = false;
	if(OuvrirEnLecture()==0)
	{
		if(ok = (Lire(0)==0) )
		{
			DeFormaterDonnee();
//			CreerCheminDeCeProjet();
		}
	}
	FermerFichier();
	return ok;
}

bool FBlocProjet::LirePremierContexte()
{
//    CreerCheminDeCeProjet();
    return fichiercontexte.LirePremierContexte();
}

bool FBlocProjet::LireContexte( const std::string &valeur )
{
//    CreerCheminDeCeProjet();
//    if(!fichiercontexte.Initialiser( &cheminduprojet )) return false;
    return fichiercontexte.LireContexte(valeur);
}

bool FBlocProjet::EcrireContexte( const EnrgContexte &valeurctx )
{
    //CreerCheminDeCeProjet();
    //fichiercontexte.Initialiser( &cheminduprojet );
    return fichiercontexte.EcrireContexte(valeurctx);
}

void FBlocProjet::CreerCheminDeCeProjet()
{
    cheminduprojet = CheminFichier();
    cheminduprojet.append("/");
    cheminduprojet.append(enrgprojet.nom);
    cheminduprojet.append("/");
}

void FBlocProjet::CreerEnvironnementProjet()
{
	CreerCheminDeCeProjet();
    if(std::filesystem::exists(cheminduprojet))
        DetruireProjet();
	std::filesystem::create_directories(cheminduprojet);
}
void FBlocProjet::Collationner( EnrgSessionProjet &rtenrgsession )
{
	EnrgContexte enrgctxtmp;
	fichiercontexte.Collationner( enrgctxtmp );
	rtenrgsession.contexte	= enrgctxtmp;// nom du contexte en cours
    rtenrgsession.projet	= enrgprojet;
}
void FBlocProjet::ViderEnrgprojet()
{
	enrgprojet.nom.clear();
	enrgprojet.commentaire.clear();
	memset(&enrgprojet.dcreation,0,TAILLEDATEDG);
	enrgprojet.lstcontexte.Vider();
}
void FBlocProjet::DetruireProjet()
{
}

