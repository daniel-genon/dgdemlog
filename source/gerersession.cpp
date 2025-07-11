#include "gerersession.h"

GererSession::GererSession()
{
    dlgnouvprojet	= nullptr;
    dlgnouvcontexte	= nullptr;
    noerreur        = 0;
    listedesconfigurations.Vider();
    VerifierRepertoire();
}
GererSession::~GererSession()
{
	if(dlgnouvprojet!=nullptr) delete dlgnouvprojet;
	if(dlgnouvcontexte!=nullptr) delete dlgnouvcontexte;
}
void GererSession::LireSessionEnCours()
{
	noerreur=0;
	InitDescription( cheminracine );
    fichierprojet.InitDescription(cheminracine);
	if( !LireSession() ) noerreur=5;
}
void GererSession::ChargerSession()
{// LireSessionEnCours doit avoir été appelé avant.
	if( noerreur==0 )
    {
        if(fichierprojet.LireProjet(NomDuProjet()))
        {
			if(!fichierprojet.LireContexte(NomDuContexte()))
				noerreur = 4;
        }
        else
			noerreur = 3;
    }
    else
    {
		fichierprojet.InitDescription(cheminracine);
		noerreur = 1;
		if(fichierprojet.RetourErreur()==0)
		{
			noerreur = 3;
			if(fichierprojet.LirePremierProjet())
			{
				noerreur = 4;
				if(fichierprojet.LirePremierContexte())
					noerreur = 0;
			}
		}
    }
    if(noerreur==0)
		fichierprojet.Collationner( enrgsespro );
}
bool GererSession::ChargerSession( const std::string &nomprojet, const std::string &nomcontexte )
{
	noerreur=0;
	if(fichierprojet.LireProjet(nomprojet))
	{
		if(!fichierprojet.LireContexte(nomcontexte))
			noerreur = 4;
	}
	else
		noerreur = 3;
	if(noerreur==0)
		fichierprojet.Collationner( enrgsespro );
	return noerreur==0;
}
// erreur 999 = sortie annuler de boite de dialogue
bool GererSession::oksession(){ return (noerreur==0||noerreur==999); }
// erreur 999 = sortie annuler de boite de dialogue
bool GererSession::okboite(){ return noerreur==999; }
void GererSession::Enregistrer()
{
	fichierprojet.Collationner( enrgsespro );
    EcrireSession();
}
void GererSession::MiseAJourListeConfig( const std::vector<std::string> &lstcfg )
{
	*listedesconfigurations.PtrChaine() = lstcfg;
}
std::string GererSession::CheminRacine() const { return cheminracine;}
std::string *GererSession::ptrCheminRacine(){ return &cheminracine; }
std::string GererSession::CheminStandard() const
{
    std::string phr = CheminRacine();
    phr.append( "fichierstandard/" );
    return phr;
}
std::string GererSession::CheminProjet() const { return std::string( fichierprojet.CheminFichier()+"/"+NomDuProjet()+"/" ); }
std::string GererSession::CheminContexte() const
{
    std::string phr = CheminProjet();
    phr.append( NomDuContexte() );
    phr.append("/");
    return phr;
}
void GererSession::ReactionEnRetour( const sigc::slot<void()> &slot ){ signalderappel = slot; }
void GererSession::CreerNouveauContexte( uint8_t valrt )
{
	if(valrt==0)
	{
		if(dlgnouvcontexte!=nullptr) delete dlgnouvcontexte;
		dlgnouvcontexte = new CreerContexte( &fichierprojet, &listedesconfigurations );
		dlgnouvcontexte->ConnexionRetour(sigc::mem_fun(*this, &GererSession::CreerNouveauContexte));
	}
	else
	{
		if(dlgnouvcontexte!=nullptr)
		{
			if(valrt==1)
			{
				noerreur = 997;
				EnrgContexte	tmpcontexte;
				std::string retphr("");
				dlgnouvcontexte->Collationner( tmpcontexte, retphr );
				if(retphr.compare( NomDuProjet() )!=0)
					fichierprojet.LireProjet( retphr );
				
				fichierprojet.EcrireContexte(tmpcontexte);
				enrgsespro.contexte = tmpcontexte;
				noerreur = 0;
				signalderappel();			
			}
			delete dlgnouvcontexte;
			dlgnouvcontexte=nullptr;
		}
	}
}
void GererSession::CreerNouveauProjet( uint8_t valrt )
{
	if(valrt==0)
	{
		DGChaineListe lstprojet;
		fichierprojet.Lister( lstprojet );
		if(dlgnouvprojet!=nullptr) delete dlgnouvprojet;
		dlgnouvprojet = new CreerProjet( &lstprojet );
		dlgnouvprojet->ConnexionRetour(sigc::mem_fun(*this, &GererSession::CreerNouveauProjet));
	}
	else
	{
		if(dlgnouvprojet!=nullptr)
		{
			if(valrt==1)
			{
				noerreur = 998;
				EnrgProjet	tmpprojet;
				dlgnouvprojet->Collationner(tmpprojet);
				if(fichierprojet.CreerLeProjet(tmpprojet))
				{
					noerreur = 0;
					enrgsespro.projet = tmpprojet;
					fichierprojet.LireProjet( enrgsespro.projet.nom );
					CreerNouveauContexte(0);
				}
			}
			delete dlgnouvprojet;
			dlgnouvprojet=nullptr;
		}
	}
}
FBlocProjet *GererSession::pFichierProjet(){ return &fichierprojet; }
std::string GererSession::LibelleErreur() const
{
    std::string phrmessage;
    switch(noerreur)
    {
    case 0: phrmessage.append("aucune erreur");break;
    case 1: phrmessage.append("Le projet ou le contexte n'est pas créé");break;
    case 2: phrmessage.append("Il n'y a aucun projet ou contexte sauvegardé.");break;
    case 3: phrmessage.append("Projet inexistant.");break;
    case 4: phrmessage.append("Contexte inexistant.");break;
    case 5: phrmessage.append("Aucune session en cours.");break;


    case 997: phrmessage.append("Le contexte n'est pas créé.");break;
    case 998: phrmessage.append("Le projet n'est pas créée.");break;
    case 999: phrmessage.append("Sortie abandon de boite");break;// ne pas afficher
    default : phrmessage.append("erreur non répertoriée");
    }
    return phrmessage;
}

void GererSession::CreerRepertoire(){ std::filesystem::create_directories(cheminracine+"/fichierstandard"); }
void GererSession::CreerCheminParDefaut(){}
void GererSession::VerifierRepertoire()
{
	cheminhome = std::getenv("HOME");
    cheminhome.append("/");
    cheminracine = cheminhome;
    cheminracine.append("MultiApp/");
    CreerCheminParDefaut();
    if(!std::filesystem::exists(cheminracine))
    {
        CreerRepertoire();
    }
}
void GererSession::SauverEnrgProjet(){ SVDenrgsespro = enrgsespro; }
void GererSession::RestaurerEnrgProjet(){ enrgsespro = SVDenrgsespro; }
void GererSession::ReserverEnrgProjet(){ RESenrgsespro = enrgsespro; }
void GererSession::RetablirEnrgProjet(){ enrgsespro = RESenrgsespro; }
