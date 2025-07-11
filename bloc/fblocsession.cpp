#include "fblocsession.h"

FBlocSession::FBlocSession()
{
	taillebloc	= TAILLEDATEDG +TAILLECHAINENOM * 3;
	NomFichier("sessiondgdemlog");
   	ExtensionFichier("gla");
    InitEnrg((char *)&enrgB, taillebloc);
    ViderEnrg();
    char* pUtilisateur = getenv ("USER");
    utilisateursecours = pUtilisateur;
}
std::string FBlocSession::NomDuProjet() const { return enrgsespro.projet.nom; }
std::string FBlocSession::NomDuContexte() const { return enrgsespro.contexte.nom; }
std::string FBlocSession::NomUtilisateur() const { return enrgsespro.utilisateur; }
std::string FBlocSession::NomConfiguration() const { return enrgsespro.contexte.configuration; }
void FBlocSession::ChangerConfiguration( const std::string &valeur ) { enrgsespro.contexte.configuration = valeur; }
bool FBlocSession::EcrireSession()
{
	FormaterDonnee();
    return Ecrire(true)==0;
}
void FBlocSession::ModifierDate()
{
	time_t datedujour;
	time (&datedujour);
	struct tm *nrgdate = localtime (&datedujour);
	enrgsespro.dmodifsession.a = nrgdate->tm_year+1900;
	enrgsespro.dmodifsession.m = nrgdate->tm_mon;
	enrgsespro.dmodifsession.j = nrgdate->tm_mday;
}
bool FBlocSession::LireSession()
{
	bool ok = false;
	if(OuvrirEnLecture()==0)
	{
		if(ok = (Lire()==0) ) DeFormaterDonnee();
	}
	FermerFichier();
	return ok;
}
void FBlocSession::FormaterDonnee()
{
	ModifierDate();
    ViderEnrg();
    ConvStrVersBin( enrgsespro.projet.nom, &enrgB.projet );
    ConvStrVersBin( enrgsespro.contexte.nom, &enrgB.contexte );
    ConvStrVersBin( enrgsespro.utilisateur, &enrgB.utilisateur );
    enrgB.dmodi = enrgsespro.dmodifsession;
//    ConvStrVersBin( enrgsespro.configuration, &enrgB.configuration );
}
void FBlocSession::DeFormaterDonnee()
{
	ViderEnrgSession();
	enrgsespro.projet.nom = std::string((char *)&enrgB.projet);
	enrgsespro.contexte.nom = std::string((char *)&enrgB.contexte);
	enrgsespro.dmodifsession = enrgB.dmodi;
	if( enrgsespro.utilisateur.empty() )
		enrgsespro.utilisateur = utilisateursecours;
//	enrgsespro.configuration = std::string((char *)&enrgB.configuration);
}
void  FBlocSession::AjouterContexte( const std::string &valeur ) { enrgsespro.projet.lstcontexte.PtrChaine()->push_back(valeur); }
void FBlocSession::ViderEnrgSession()
{
	enrgsespro.utilisateur.clear();
//	enrgsespro.configuration.clear();
	memset(&enrgsespro.dmodifsession,0,TAILLEDATEDG);
	
	enrgsespro.projet.nom.clear();
	enrgsespro.projet.commentaire.clear();
	memset(&enrgsespro.projet.dcreation,0,TAILLEDATEDG);
	enrgsespro.projet.lstcontexte.Vider();

	enrgsespro.contexte.nom.clear();
	enrgsespro.contexte.commentaire.clear();
	enrgsespro.contexte.configuration.clear();
	memset(&enrgsespro.contexte.dcreation,0,TAILLEDATEDG);
	memset(&enrgsespro.contexte.dmodi,0,TAILLEDATEDG);
}
