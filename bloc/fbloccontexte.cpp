#include "fbloccontexte.h"

FBlocContexte::FBlocContexte()
{
	taillebloc	= TAILLECHAINENOM*3 + TAILLEDATEDG*2;
   	ExtensionFichier("gla");
	InitEnrg((char *)&enrgBCX, taillebloc );
}
void FBlocContexte::InitialiserCheminProjet( std::string *vcheminprojet, const std::string &vnomprojet )
{
    pcheminprojet	= vcheminprojet;
    CheminFichier( *vcheminprojet );
    NomFichier(vnomprojet);
    CreerNomComplet();
}
bool FBlocContexte::Lister( DGChaineListe &lstvaleur )
{
	return ListerChaine(lstvaleur.PtrChaine(), (char *)&enrgBCX.nom, TAILLECHAINENOM);
}
void FBlocContexte::FormaterDonnee()
{
    ViderEnrg();
    ConvStrVersBin( enrgcontexte.nom, &enrgBCX.nom );
    ConvStrVersBin( enrgcontexte.commentaire, &enrgBCX.commentaire );
    ConvStrVersBin( enrgcontexte.configuration, &enrgBCX.configuration );
    enrgBCX.dcrea = enrgcontexte.dcreation;
    enrgBCX.dmodi = enrgcontexte.dmodi;
}
void FBlocContexte::DeFormaterDonnee()
{
	ViderEnrgContexte();
    enrgcontexte.nom = std::string((char *)&enrgBCX.nom);
    enrgcontexte.commentaire = std::string((char *)&enrgBCX.commentaire);
    enrgcontexte.configuration = std::string((char *)&enrgBCX.configuration);
    enrgcontexte.dcreation = enrgBCX.dcrea;
    enrgcontexte.dmodi = enrgBCX.dmodi;
     CreerCheminDeCeContexte();
}
bool FBlocContexte::EcrireContexte( const EnrgContexte &valeurctx )
{
	enrgcontexte = valeurctx;
	CreerEnvironnementContexte();
	if(!FichierExiste())
		CreerVide();
	FormaterDonnee();
    return Ecrire()==0;
}
bool FBlocContexte::LireContexte( const std::string &valeur )
{
	phrtest = valeur;//phrtest est déclarée dans ficbin
	if(!ChercherChaine((char*)&enrgBCX.nom , TAILLECHAINENOM)) return false;
	DeFormaterDonnee();
	return true;
}
std::string *FBlocContexte::CheminDuContexte()
{
//    CreerCheminDeCeContexte();
    return &cheminducontexte;
}
bool FBlocContexte::LirePremierContexte()
{
	ViderEnrg();
	if(!LirePremierEnrg()) return false;
	DeFormaterDonnee();
	return true;
}
void FBlocContexte::Collationner( EnrgContexte &rtvaleur )
{
	rtvaleur = enrgcontexte;
}
std::string FBlocContexte::LireCommentaire() const
{
	return enrgcontexte.commentaire;
}
EnrgDate FBlocContexte::LireDate()
{
	return enrgcontexte.dcreation;
}
void FBlocContexte::ViderEnrgContexte()
{
	enrgcontexte.nom.clear();
	enrgcontexte.commentaire.clear();
	memset(&enrgcontexte.dcreation,0,TAILLEDATEDG);
	memset(&enrgcontexte.dmodi,0,TAILLEDATEDG);
}
void FBlocContexte::CreerCheminDeCeContexte()
{
    cheminducontexte.clear();
    cheminducontexte.append(*pcheminprojet);
    cheminducontexte.append(enrgcontexte.nom);
    cheminducontexte.append("/");
}
void FBlocContexte::CreerEnvironnementContexte()
{
	CreerCheminDeCeContexte();
    if(std::filesystem::exists(cheminducontexte))
        DetruireContexte();
	std::filesystem::create_directories(cheminducontexte);
	InitDescription(*pcheminprojet);
}
void FBlocContexte::DetruireContexte()
{
}
