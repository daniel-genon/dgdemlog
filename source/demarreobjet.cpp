#include "demarreobjet.h"

DemarreObjet::DemarreObjet()
{
    lstprocessus.Vider();
    regulateurdelai  = 10;// delai = delai/regulateur
}
void DemarreObjet::InitSession( GererSession *valeur, ZoneGraphique *pvalscene  )
{
	psession	= valeur;
	pscene		= pvalscene;
}
bool DemarreObjet::ReinitialiserLaScene()
{
	tabitem.clear();
	tabdemarrage.clear();
	pscene->CollecterGenreObjet( 100, tabitem );
    if( tabitem.size()>0 )
    {
       	std::vector<GraphiqueSurface*>::iterator itgraph;
        for (itgraph = tabitem.begin(); itgraph != tabitem.end(); ++itgraph)
        {
			plogi = (Logiciel*) *itgraph;
			AjouterATable();
		}
		pgrasurftmp = pscene->CollecterGenreObjet( 110 );
		if(pgrasurftmp!=nullptr)
		{
			valdemlogtmp = std::make_pair( 0, (Logiciel*)pgrasurftmp );
			tabdemarrage.push_back(valdemlogtmp);
		}
	}
    return tabdemarrage.size()>0;
}
bool DemarreObjet::AjouterATable()
{
    uint8_t valprio = plogi->ValeurPriorite();
	valdemlogtmp = std::make_pair( valprio, plogi );
	for (itabdem = tabdemarrage.begin(); itabdem != tabdemarrage.end(); ++itabdem)
	{
		if(std::get<0>(*itabdem)<=valprio)
		{                
			tabdemarrage.insert(itabdem,valdemlogtmp);
			return true;
		}
	}
	tabdemarrage.push_back(valdemlogtmp);
    return true;
}
uint8_t DemarreObjet::DemarrerLaSession()
{
    phrasededemarreur.clear();
    nomdulogiciel.clear();
    lstprocessus.Vider();
    nomfichiercfgobjet.Vider();
    nomfichiertrvobjet.Vider();
    phrasepouroptions.Vider();
    bool oklancer       = true;
    uint8_t retoursession = 2;
    if(ReinitialiserLaScene())
    {
        retoursession=0;
        for (itabdem = tabdemarrage.begin(); itabdem != tabdemarrage.end(); ++itabdem)
        {
           plogi = std::get<1>(*itabdem);
           nomdulogiciel = plogi->NomDuProcessus();
           if( nomdulogiciel == "fermerauto" )
           {
				retoursession = 1;
           }
           else
           {
				if(plogi->UnSeulAutorise())
					oklancer = !ProcessusExistant();
				else
					oklancer = true;
				if(oklancer)
				{
					PhraseFichierCFG();
					PhraseFichierTRV();
					if(LancerProcessus())
						IntegrerDansListeDesDemarres();
				}
				else
				{// logiciel déjà démarré ( intégration dans la liste pour le stopper en fin de session)
					IntegrerDansListeDesDemarres();
				}
           }
        }
    }
    return retoursession;
}
void DemarreObjet::IntegrerDansListeDesDemarres()
{
	lstprocessus.PtrChaine()->push_back(nomdulogiciel);
	IntegrerLesDependances();
}
void DemarreObjet::IntegrerLesDependances()
{
	lstprocessus.Partager( plogi->Dependance(), ',' );
}
void DemarreObjet::PhraseFichierTRV()
{
	FichierLie *fictest = plogi->PtrFicLie(2);
	if(fictest!=NULL)
		PhraseFichier( fictest->NomCompletFichier(), plogi->Options(200), nomfichiertrvobjet );
}
void DemarreObjet::PhraseFichierCFG()
{
	FichierLie *fictest = plogi->PtrFicLie(3);
	if(fictest!=NULL)
		PhraseFichier( fictest->NomCompletFichier(), plogi->Options(300), nomfichiercfgobjet );
}
void DemarreObjet::PhraseFichier( const std::string &nmfic, const std::string &opfic, DGChaineListe &rtlstchaine )
{
//    DGChaineListe	nomliste;
    std::string		nomfichier(nmfic);
    FicBase *objetfichier = new(FicBase);

    objetfichier->InitDescTotal( nomfichier );

    if(objetfichier->CheminFichier().empty())
    {
        nomfichier = psession->CheminContexte();
        nomfichier.append( nmfic );
        objetfichier->InitDescTotal( nomfichier );
    }
    if(objetfichier->FichierExiste())
    {
		if(objetfichier->ExtensionFichier().compare("txt")==0)
        {
            std::string ligne;
            FicTexte *tmpfic = (FicTexte*)objetfichier;
            if(tmpfic->OuvrirEnLecture())
            {
                if(tmpfic->LireEnContinu())
                {
                    if(tmpfic->LireChaine().compare("nom-interne") == 0)
                    {
						nomfichier.clear();
						if(tmpfic->LireEnContinu())
							nomfichier = tmpfic->LireChaine();
                    }
                }
				tmpfic->FermerFichierContinu();
            }
        }
        if(!nomfichier.empty())
        {
			if(!opfic.empty())
				rtlstchaine.PtrChaine()->push_back(opfic);
			rtlstchaine.PtrChaine()->push_back(nomfichier);
		}
    }
    delete objetfichier;
}
bool DemarreObjet::ProcessusExistant()
{
	bool valeurretour = false;
	std::string ficsortie("ficresexiste");
    std::string phrsystem = "pgrep -f "+ nomdulogiciel+">"+ficsortie;
	std::system( phrsystem.data() );
	std::system( "wait \"$!\" " );
	
	FicBase rtvaleurfic(ficsortie);
	if(rtvaleurfic.FichierExiste())
	{
		valeurretour = rtvaleurfic.FichierVide();
		rtvaleurfic.SupprimerFichier();
	}
	return valeurretour;
}
bool DemarreObjet::LancerProcessus()
{
    bool reussi = false;
		phrasededemarreur = "exec " + plogi->CheminProcess();
        if(phrasededemarreur.back()!='/')
			phrasededemarreur.push_back('/');
        phrasededemarreur.append(plogi->NomDuProcessus());

    if(!phrasededemarreur.empty())
    {
		uint8_t attente = plogi->DelaiApresDemarrage()/regulateurdelai;
        if(!plogi->Options( 1 ).empty())
        {
            phrasepouroptions.Partager( plogi->Options( 1 ), ',');
            plogi->PtrConfObjet()->lvarmsa.RemplacerCode( phrasepouroptions );
        }
        if(nomfichiercfgobjet.NonVide())
            phrasepouroptions.Ajouter( nomfichiercfgobjet.PtrChaine() );
        if(nomfichiertrvobjet.NonVide())
            phrasepouroptions.Ajouter( nomfichiertrvobjet.PtrChaine() );
        if(phrasepouroptions.NonVide())
        {
			std::string	phrtmp;
			if( phrasepouroptions.Concatener( phrtmp ))
			{
				phrasededemarreur.append(" ");
				phrasededemarreur.append(phrtmp);
			}
		}
		phrasededemarreur += " &";
		reussi = std::system( phrasededemarreur.data() ) == 0;
		phrasededemarreur = "sleep " + std::to_string( attente );
		std::system( phrasededemarreur.data() );
	}
    phrasededemarreur.clear();
    nomfichiercfgobjet.Vider();
    nomfichiertrvobjet.Vider();
    phrasepouroptions.Vider();
    return true;
}
bool DemarreObjet::DesProcessusSontDemarres(){ return lstprocessus.NonVide(); }
void DemarreObjet::ArreterLesProcessus(  )
{
    if(lstprocessus.NonVide())
    {
		std::string commandeoptions = "killall -I -u " + psession->NomUtilisateur() + " ";
		for( int i=0; i<lstprocessus.TailleListe(); i++ )
		{
			std::string toto(lstprocessus.PtrChaine()->at(i));
			phrasededemarreur = commandeoptions + toto;
			std::system( phrasededemarreur.data() );
		}
		lstprocessus.Vider();
    }
}
