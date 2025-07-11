#include "dialogconfiggenerale.h"

DialogConfigGenerale::DialogConfigGenerale()
{
	indexprio, indexflie, indlogiciel, coderetmodif	= 0;
    pFncVoid		= nullptr;
    pFncAppeloui	= nullptr;
    pFncAppelnon	= nullptr;
    pFncRetourValeur	= nullptr;
	plvarmsa	= nullptr;
	pfichier	= nullptr;
	ptrlog		= nullptr;
	msgmsa		= nullptr;
	dialvarmsa	= nullptr;
	boitefichier	= nullptr;
	okcollationnerlogiciel = true;
	okcollationnerpriorite = true;
	
	set_title("Configuration");
	set_default_size(600, 600);
/**
		Configuration boite
**/	
	CGeneral = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 8 );
		CGeneral->set_margin(10);
		CGeneral->set_hexpand();
	CConnexion = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 8 );
		CConnexion->set_margin(10);
		CConnexion->set_hexpand();
	CLogiciel = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 8 );
		CLogiciel->set_margin(10);
		CLogiciel->set_hexpand();
	CPriorite = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 8 );
		CPriorite->set_margin(10);
		CPriorite->set_hexpand();
	CGraphlie = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 8 );
		CGraphlie->set_margin(10);
		CGraphlie->set_hexpand();

	auto onglet = Gtk::make_managed<Gtk::Notebook>();
		onglet->set_margin(10);
		onglet->set_expand();
	onglet->append_page(*CGeneral,"Généralité");
	onglet->append_page(*CConnexion,"Connexion");
	onglet->append_page(*CLogiciel,"Logiciel");
	onglet->append_page(*CPriorite,"Priorité");
	onglet->append_page(*CGraphlie,"Graphique lié");

	MasqueOngletConfig();
	MasqueOngletConnexion();
	MasqueOngletLogiciel();
	MasqueOngletPriorite();
	MasqueOngletFichierLie();
	
	auto zboutonfin = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		zboutonfin->set_hexpand(true);
		zboutonfin->set_margin(10);
		auto bouannule	= Gtk::make_managed<Gtk::Button>("Sortir");
			bouannule->set_hexpand(true);
			bouannule->set_halign(Gtk::Align::END);
			bouannule->signal_clicked().connect( sigc::mem_fun(*this, &DialogConfigGenerale::hide) );
			
		bouaccepte	= Gtk::make_managed<Gtk::Button>("Sauver");
			bouaccepte->set_hexpand(true);
			bouaccepte->set_halign(Gtk::Align::START);
			bouaccepte->signal_clicked().connect( sigc::mem_fun(*this, &DialogConfigGenerale::Sauvegarde) );
			
	zboutonfin->append(*bouannule);
	zboutonfin->append(*bouaccepte);
	
	auto ztotal = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
	
	ztotal->append(*onglet);
	ztotal->append(*zboutonfin);
	set_child(*ztotal);
	show();
}
DialogConfigGenerale::~DialogConfigGenerale()
{
	if( msgmsa != nullptr )delete msgmsa;
	if( dialvarmsa != nullptr )delete dialvarmsa;
	if( boitefichier != nullptr )delete boitefichier; 
}
void DialogConfigGenerale::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot){ signal_hide().connect(sigc::bind(slot,9)); }
uint8_t DialogConfigGenerale::RetourCodeModification(){ return coderetmodif; }
/*
void DialogConfigGenerale::ChangerConfig( guint position, guint n_items)
{
	std::string resuphr = Clstconfig->get_string( selconfig->get_selected() );
	uint32_t tmpindex;
	if( lstnomconfig.Position( resuphr, tmpindex ))
	{
//		if( okcollationnerlogiciel ) CollationnerLogiciel();
		indconfig = tmpindex;
		InitialiserValeurs();
	}
}
void DialogConfigGenerale::NouvelleConfiguration()
{
	if( econfig.Nom().compare( pfichier->ptrConfig()->Nom() )!=0 ) SaisirNomConfiguration();
	CollationnerValeurs();
	if(ValeursModifiees())
	{
		pFncAppeloui = &DialogConfigGenerale::SauvegardeOK; 
		pFncAppelnon = &DialogConfigGenerale::SaisirNomConfiguration;
		QuestionOuiNon( "Sauvegarde configuration.","Des valeurs de la configuration ont été modifiées.\nSauver les modifications ?" );
	}
	else
		SaisirNomConfiguration();
}
void DialogConfigGenerale::SaisirNomConfiguration()
{
	pFncVoid = &DialogConfigGenerale::CreerNouvConfig; 
	pFncRetourValeur = &DialogConfigGenerale::Reponse_Entree; 
	SaisirValeur( "Nom de la nouvelle configuration", 2 );
}
void DialogConfigGenerale::CreerNouvConfig()
{
    econfig.Standard();
    econfig.Nom(chainetmp);
    eancre.Standard();
    elstconnex.Standard();
    elstlogiciel.Nettoyer();
    elstgraph.Standard();
    elstficlie.Standard();
    InitialiserValeurs( true );
}
void DialogConfigGenerale::ChargerConfiguration()
{
}
*/
void DialogConfigGenerale::ChangerLogiciel( guint position, guint n_items)
{
	std::string resuphr = Clstlogiciel->get_string( sellogiciel->get_selected() );
	uint32_t tmpindex;
	if( elstlogiciel.TrouverNom( resuphr, tmpindex ))
	{
		if( okcollationnerlogiciel ) CollationnerLogiciel();
		indlogiciel = tmpindex;
		MiseAJourOngletLogiciel();
	}
}
void DialogConfigGenerale::ChangerPriorite( guint position, guint n_items)
{
	std::string resuphr = Clstpriorite->get_string(selprio->get_selected());
	uint32_t tmpindex;
	if( elstgraph.TrouverNom( resuphr, tmpindex ))
	{
		if( okcollationnerpriorite ) CollationnerPriorite();
		indexprio = tmpindex;
		MiseAJourOngletPriorite();
	}
}
void DialogConfigGenerale::ChangerFicLie( guint position, guint n_items)
{
	std::string resuphr = Clstficlie->get_string(selfli->get_selected());
	uint32_t tmpindex;
	if( elstficlie.TrouverNom( resuphr, tmpindex ))
	{
		CollationnerGraphFicLie();
		indexflie = tmpindex;
		MiseAJourOngletFichierLie();
	}
}
void DialogConfigGenerale::ChangerConnexion( guint position, guint n_items)
{
	std::string resuphr = Clstconnex->get_string(selcnx->get_selected());
	uint32_t tmpindex;
	if( elstconnex.TrouverNom( resuphr, tmpindex ))
	{
		CollationnerConnexion();
		indconnex = tmpindex;
		MiseAJourOngletConnexion();
	}
}
void DialogConfigGenerale::ChoisirFichier( int cas )
{
	if (boitefichier!=nullptr) delete boitefichier;
	boitefichier = new Gtk::FileChooserDialog(*this, "Choisir le nom du fichier", Gtk::FileChooser::Action::OPEN );
		boitefichier->set_modal(true);
	switch (cas)
	{
		case 1 : 
		case 3 :{ 
				auto filter_text = Gtk::FileFilter::create();
				filter_text->add_suffix("png");
				filter_text->add_suffix("svg");
				filter_text->add_suffix("jpg");
				filter_text->add_suffix("jpeg");
				boitefichier->set_filter(filter_text);
				}break;
		case 4 :
				boitefichier->set_action(Gtk::FileChooser::Action::SELECT_FOLDER);
				boitefichier->set_title("Choisir le dossier du processus");
				break;
		case 2 : boitefichier->set_title("Choisir le nom du processus");break;
		case 5 :
		case 6 : break;
	}
	boitefichier->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ReponseFichier), cas));
		boitefichier->add_button("Annuler", Gtk::ResponseType::CANCEL);
		boitefichier->add_button("Accepter", Gtk::ResponseType::ACCEPT);
	boitefichier->show();
}
void DialogConfigGenerale::ReponseFichier(int reponse, int cas)
{
	if(boitefichier!=nullptr)
	{
		if(reponse==Gtk::ResponseType::ACCEPT)
		{
			switch(cas)
			{
				case 1 : // fichier icone ancre
					edinomficico->set_text(boitefichier->get_file()->get_basename());
					break;
				case 3 : // fichier icone processus
					edinomfico->set_text(boitefichier->get_file()->get_path());
					break;
				case 2 : // fichier processus
					{
					Glib::ustring *nomfic = new Glib::ustring(boitefichier->get_file()->get_basename());
					Glib::ustring *nomchm = new Glib::ustring(boitefichier->get_file()->get_path());
					nomchm->resize(nomchm->size()-(nomfic->size()+1));
						edinomproc->set_text(*nomfic);
						edidospro->set_text(*nomchm);
						delete nomfic;
						delete nomchm;
					if(pFncVoid!=nullptr)
					   (this->*pFncVoid)();	
					}
					break;
				case 4 : // dossier du processus
						edidospro->set_text(boitefichier->get_file()->get_path());
					break;
				case 5 : // fichier standard travail
						edificstdtrv->set_text(boitefichier->get_file()->get_path());
					break;
				case 6 : // fichier standard configuration
						edificstdcfg->set_text(boitefichier->get_file()->get_path());
					break;
			}
		}
		delete boitefichier;
		boitefichier = nullptr;
	}
}
void DialogConfigGenerale::IniBoite( FBlocConfig *pvaleur, LstVarMSA *lvarmsa )
{
    pfichier    = pvaleur;
    plvarmsa    = lvarmsa;
		econfig.Valeur( pfichier->ptrConfig() );
		eancre.Valeur ( *pfichier->ptrAncrage() );
		elstconnex.Copier( *pfichier->ptrlstconnexion());
		elstlogiciel.Copier( *pfichier->ptrlstLogiciel() );
		elstgraph.Copier( *pfichier->ptrlstgrlogiciel() );
		elstficlie.Copier( *pfichier->ptrlstgrfic() );
	chainetmp = "Gestion de la configuration : "+econfig.Nom();
   	set_title(chainetmp);
    InitialiserValeurs();
}
void DialogConfigGenerale::TransfererValeurs( uint8_t codetransfert )
{
	uint8_t i=1;
	if( codetransfert & i ) pfichier->ptrConfig()->Valeur( econfig );
	i = i<<1;
	if( codetransfert & i ) pfichier->ptrAncrage()->Valeur( eancre );
	i = i<<1;
	if( codetransfert & i ) pfichier->ptrlstLogiciel()->Copier( elstlogiciel );
	i = i<<1;
	if( codetransfert & i ) pfichier->ptrlstgrlogiciel()->Copier( elstgraph );
	i = i<<1;
	if( codetransfert & i ) pfichier->ptrlstgrfic()->Copier( elstficlie );
	i = i<<1;
	if( codetransfert & i ) pfichier->ptrlstconnexion()->Copier( elstconnex );
}
void DialogConfigGenerale::InitialiserValeurs()
{
	//if(nouvconf)
	//{
		//Clstconfig->append(chainetmp);
		//lstnomconfig.PtrChaine()->push_back( chainetmp );
		//indconfig = Clstconfig->get_n_items()-1;
	//}
	//else
	//{
		//if(selconfig->property_n_items()==0)
		//{
			//lstnomconfig.Vider();
			//pfichier->ListerLesBlocs(lstnomconfig.PtrChaine());
			//lstnomconfig.ListerVers( Clstconfig );
			//selconfig->set_model(Clstconfig);
		//}
	//}
	//selconfig->set_selected(indconfig);
//onglet application;
	MiseAJourOngletApplication();
//onglet connexion;
	indconnex = 0;
 	elstconnex.ListerNom(Clstconnex);
 	selcnx->set_model(Clstconnex);
	MiseAJourOngletConnexion();
//onglet logiciel;
	indlogiciel	= 0;
	plvarmsa->ListerValeur( lstvariable );
 	elstlogiciel.ListerNom(Clstlogiciel);
 	sellogiciel->set_model(Clstlogiciel);
	chxlstvar->set_model(lstvariable);
	chxlstvar->set_selected(indlogiciel);
	MiseAJourOngletLogiciel();
//onglet priorite;
	indexprio = 0;
 	elstgraph.ListerNom(Clstpriorite);
 	selprio->set_model(Clstpriorite);
	MiseAJourOngletPriorite();
//onglet fichier lié;
	indexflie = 0;
 	elstficlie.ListerNom(Clstficlie);
 	selfli->set_model(Clstficlie);
	MiseAJourOngletFichierLie();
}
void DialogConfigGenerale::CollationnerValeurs()
{
    CollationnerConfig();
    CollationnerConnexion();
    CollationnerPriorite();
    CollationnerLogiciel();
    CollationnerGraphFicLie();
    CollationnerAncre();
}
void DialogConfigGenerale::CollationnerConfig()
{
	ConvStrVersBin( btnchxpol->get_font() , &econfig.PPolice()->nom, 0 );
	ConvStrVersBin( Gdk::RGBA(coulpol->property_rgba()).to_string() , &econfig.PPolice()->couleur, 0 );
	
	econfig.CouleurMenu(Gdk::RGBA(coulmenu->property_rgba()).to_string());
	econfig.CouleurGraphique(Gdk::RGBA(coulgraf->property_rgba()).to_string());
	econfig.IconeGestion( (uint8_t)hticodrt->get_value_as_int());	
	econfig.IconeDessus( (uint8_t)hticoctr->get_value_as_int());	
	econfig.IconeSymbole( (uint8_t)hticogah->get_value_as_int());	
}
void DialogConfigGenerale::CollationnerConnexion()
{// indconnex doit être initialisé
	ptrenrconnexion ptrconnex = elstconnex.Position(indconnex);
	ptrconnex->Valeur( "", Gdk::RGBA(coulcnx->property_rgba()).to_string(),
								(uint8_t)chxtplcnx->get_selected(),
								(uint8_t)eprlgncnx->get_value_as_int() );
}
void DialogConfigGenerale::CollationnerAncre()
{
	EnrgPolice poltmp( btnchxpolico->get_font(),
						Gdk::RGBA(coulpolico->property_rgba()).to_string());
    eancre.Valeur( edinomficico->get_text(),
					Gdk::RGBA(coulfndico->property_rgba()).to_string(),
					poltmp.Police(),
					(uint8_t)lgico->get_value_as_int(),
					(uint8_t)htico->get_value_as_int());
}
void DialogConfigGenerale::CollationnerPriorite()
{// indexprio doit être initialisé
	ptrenrgraphique ptrgraph = elstgraph.Position(indexprio);
    EnrgPolice policetmp( btnchxpolsym->get_font(), Gdk::RGBA(coulpolsym->property_rgba()).to_string() );
	ptrgraph->Valeur( "",
					Gdk::RGBA(clsymfond->property_rgba()).to_string(),
					Gdk::RGBA(clsymband->property_rgba()).to_string(),
                    policetmp.Police(), larsym->get_value_as_int(),
                    htrsym->get_value_as_int(), nivprio->get_value_as_int());
}
void DialogConfigGenerale::CollationnerLogiciel()
{// indlogiciel doit être initialisé
	if(elstlogiciel.TailleListe()>0)
	{
		uint8_t valuni;
		ptrlog = elstlogiciel.Position(indlogiciel);
		if(occunique->get_active()) valuni=1; else valuni=0;
		ptrlog->Valeur(edinomproc->get_text(),
			"",
			edilstopt->get_text(),
			ediphraide->get_text(),
			edidospro->get_text(),
			edinomfico->get_text(),
			ediprodep->get_text(),
			delatt->get_value_as_int(),
			valuni,
			(poscol->get_value_as_int()-1),
			edificstdcfg->get_text(), edificstdtrv->get_text(),
			edioptcfg->get_text(), ediopttrv->get_text() );
	}
}
void DialogConfigGenerale::CollationnerGraphFicLie()
{// indexflie doit être initialisé
	ptrenrgraphique ptrgraph = elstficlie.Position(indexflie);
    EnrgPolice policetmp( btnchxpolfli->get_font(), Gdk::RGBA(coulpolfli->property_rgba()).to_string() );
	ptrgraph->Valeur( "",
					Gdk::RGBA(clflifond->property_rgba()).to_string(),
					Gdk::RGBA(clfliband->property_rgba()).to_string(),
					policetmp.Police(),
					larfli->get_value_as_int(),
					htrfli->get_value_as_int(), 0);
}
void DialogConfigGenerale::Sauvegarde()
{
	CollationnerValeurs();
    if(ValeursModifiees())
    {
		pFncAppeloui = &DialogConfigGenerale::SauvegardeOK; 
		pFncAppelnon = nullptr;
		QuestionOuiNon( "Sauvegarde configuration.","Des valeurs de la configuration ont été modifiées.\nSauver les modifications ?" );
    }
    else
		MessageInfo( "Les valeurs n'ont pas été modifiées." );
}
void DialogConfigGenerale::SauvegardeOK()
{
	TransfererValeurs( coderetmodif );
	pfichier->AutoriserCreationEnModification();
	if(pfichier->ModifierConfig( coderetmodif ))
		hide();
	else
	{
		coderetmodif = 0;
		MessageInfo( "la sauvegarde a échoué." );
	}
	pfichier->InterdireCreationEnModification();
}
bool DialogConfigGenerale::ValeursModifiees()
{
	coderetmodif = 0;
    if(ConfigGeneralModifiee())	coderetmodif  = 1;
    if(AncrageModifie())		coderetmodif += 2;
    if(LogicielModifie())		coderetmodif += 4;
    if(PrioriteModifiee())		coderetmodif += 8;
    if(FiclieModifie())			coderetmodif += 16;
    if(ConnexionModifiee())		coderetmodif += 32;
    return coderetmodif != 0;
}
bool DialogConfigGenerale::ConfigGeneralModifiee()
{
    return !pfichier->ptrConfig()->EgaleA( econfig, false );
}
bool DialogConfigGenerale::LogicielModifie()
{
	return !pfichier->ptrlstLogiciel()->EgaleA( elstlogiciel, false );
}
bool DialogConfigGenerale::PrioriteModifiee()
{
    return !pfichier->ptrlstgrlogiciel()->EgaleA( elstgraph );
}
bool DialogConfigGenerale::ConnexionModifiee()
{
    return !pfichier->ptrlstconnexion()->EgaleA(elstconnex);
}
bool DialogConfigGenerale::FiclieModifie()
{
    return !pfichier->ptrlstgrfic()->EgaleA(elstficlie);
}
bool DialogConfigGenerale::AncrageModifie()
{
    return !pfichier->ptrAncrage()->EgaleA(eancre);
}
void DialogConfigGenerale::VoirAideVariable( uint8_t cas )
{
	if(cas==1)
	{
		if(dialvarmsa!=nullptr)
		{
		  delete dialvarmsa;
		  dialvarmsa = nullptr;
		}
	}
	else
	{
		if(dialvarmsa!=nullptr) delete dialvarmsa;
		plvarmsa->PointerValeur(lstvariable->get_string(chxlstvar->get_selected()));
		dialvarmsa = new InfoVariableMSA( plvarmsa->RtPtrEnrg() );
		dialvarmsa->set_modal(true);
		dialvarmsa->connexionInfo(sigc::mem_fun(*this, &DialogConfigGenerale::VoirAideVariable));
	}
}
void DialogConfigGenerale::TransfererVariable()
{
    if(plvarmsa->PointerValeur(lstvariable->get_string(chxlstvar->get_selected())))
    {
        std::string phrtmpcode;
        if(plvarmsa->ConstruireInsertionCode(phrtmpcode))
        {
            std::string phrtmp = edilstopt->get_text();
            if(!phrtmp.empty())
                phrtmpcode += ",";
            phrtmp.append(phrtmpcode);
            edilstopt->set_text(phrtmp);
        }
    }
}
void DialogConfigGenerale::AjouterUnLogiciel()
{
	CollationnerLogiciel();
	pFncVoid = &DialogConfigGenerale::CreerNouvEnrgLogiciel; 
	pFncRetourValeur = &DialogConfigGenerale::Reponse_Entree; 
	SaisirValeur( "Nom en clair du logiciel", 1 );
}
void DialogConfigGenerale::AjouterUnePriorite()
{
	CollationnerPriorite();
	pFncVoid = &DialogConfigGenerale::CreerNouvEnrgPriorite; 
	pFncRetourValeur = &DialogConfigGenerale::Reponse_Entree; 
	SaisirValeur( "Nom de la priorite", 2 );
}
void DialogConfigGenerale::Reponse_Entree( uint8_t vrt )
{
	switch(vrt)
	{
		case 1 :
			chainetmp = msgmsa->RetourChaine();
			if(pFncVoid!=nullptr)
					   (this->*pFncVoid)();	
			ChoisirFichier( 2 );
			break;
		case 2 :
			chainetmp = msgmsa->RetourChaine();
			if(pFncVoid!=nullptr)
					   (this->*pFncVoid)();
			break;
	}
}
void DialogConfigGenerale::SupprimerLogiciel()
{
	if(elstlogiciel.TailleListe()>0)
	{
		pFncAppeloui = &DialogConfigGenerale::SupprimerLogicielOK; 
		pFncAppelnon = nullptr;
		chainetmp = elstlogiciel.Position( indlogiciel )->NomClair();
		QuestionOuiNon( Glib::ustring::compose("Supprimer le logiciel -- %1 -- de la liste.", chainetmp ),"Si un contexte utilise ce logiciel, il n'apparaîtra plus sur la scène. Souhaitez-vous vraiment délister ?" );
	}
	else
		MessageInfo( "La liste de logiciels est vide." );
}
void DialogConfigGenerale::SupprimerLogicielOK()
{
	pFncAppeloui = nullptr;
	elstlogiciel.Supprimer( indlogiciel );
	Clstlogiciel->remove(indlogiciel);
	indlogiciel = 0;
 		okcollationnerlogiciel = false;
	sellogiciel->set_selected(indlogiciel);
		okcollationnerlogiciel = true;
}
void DialogConfigGenerale::SupprimerPriorite()
{
	if(elstgraph.TailleListe()>4)
	{
		pFncAppeloui = &DialogConfigGenerale::SupprimerPrioriteOK; 
		pFncAppelnon = nullptr;
		chainetmp = elstgraph.Position( indexprio )->Nom();
		QuestionOuiNon( Glib::ustring::compose("Supprimer la priorite -- %1 -- de la liste.", chainetmp ),"Si un graphique utilise cette priorité, elle sera remplacée par la première de la liste. Souhaitez-vous vraiment la supprimer ?" );
	}
	else
		MessageInfo( "Les priorités de base ne peuvent être supprimées." );
}
void DialogConfigGenerale::SupprimerPrioriteOK()
{
	pFncAppeloui = nullptr;
	elstgraph.Supprimer( indexprio );
	Clstpriorite->remove(indexprio);
	indexprio = 0;
 		okcollationnerpriorite = false;
	selprio->set_selected(indexprio);
		okcollationnerpriorite = true;
}
void DialogConfigGenerale::MasqueOngletConfig()
{
/*
	Gtk::ScrolledWindow *ascconf;
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto zmodcfg = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
		auto signallstconfig = Gtk::SignalListItemFactory::create();
			signallstconfig->signal_setup().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ConfigLibelle));
			signallstconfig->signal_bind().connect(sigc::mem_fun(*this, &DialogConfigGenerale::AttacheNomConfig));
		selconfig = Gtk::SingleSelection::create(Clstconfig);
			selconfig->set_autoselect(false);
			selconfig->set_can_unselect(true);
			selconfig->signal_selection_changed().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChangerConfig));
		ascconf = Gtk::make_managed<Gtk::ScrolledWindow>();
			ascconf->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
			ascconf->set_hexpand();
		lstconfig = Gtk::make_managed<Gtk::ListView>();
			lstconfig->set_model(selconfig);
			lstconfig->add_css_class("data-table");
			lstconfig->set_factory(signallstconfig);
		ascconf->set_child(*lstconfig);

		auto zbtnmod = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 4 );
			auto btn_cfg_nouv = Gtk::make_managed<Gtk::Button>("Nouvelle configuration");
			btn_cfg_nouv->signal_clicked().connect(sigc::mem_fun(*this, &DialogConfigGenerale::NouvelleConfiguration));
			auto btn_cfg_char = Gtk::make_managed<Gtk::Button>("Charger configuration");
			btn_cfg_char->signal_clicked().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChargerConfiguration));
		zbtnmod->append(*btn_cfg_nouv);
		zbtnmod->append(*btn_cfg_char);
	zmodcfg->append(*ascconf);
	zmodcfg->append(*zbtnmod);
*/
		auto titre01 = Gtk::make_managed<Gtk::Label>("Affichage de la fenêtre");
			titre01->set_margin(20);
			titre01->set_halign(Gtk::Align::CENTER);
			titre01->set_justify(Gtk::Justification::CENTER);
		auto zpolice = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 4 );
			zpolice->set_hexpand(true);
				auto lablipol	= Gtk::make_managed<Gtk::Label>("Police de caractères");
				lablipol->set_halign(Gtk::Align::START);
					btnchxpol	= Gtk::make_managed<Gtk::FontButton>();
					btnchxpol->set_halign(Gtk::Align::CENTER);
					btnchxpol->set_hexpand(true);
				coulpol = Gtk::make_managed<Gtk::ColorButton>();
					coulpol->set_hexpand(false);
					coulpol->set_halign(Gtk::Align::END);
		zpolice->append(*lablipol);
		zpolice->append(*btnchxpol);
		zpolice->append(*coulpol);
		
		auto zbarrebas = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 4 );
			zbarrebas->set_margin(10);
			zbarrebas->set_hexpand();
			auto zicone = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 4 );
				zicone->set_hexpand(true);
				auto labicone = Gtk::make_managed<Gtk::Label>();
					labicone->set_text("hauteur\nicone");
					labicone->set_wrap();
					labicone->set_hexpand(true);
					labicone->set_halign(Gtk::Align::START);
					labicone->set_justify(Gtk::Justification::CENTER);
				auto zhicone = Gtk::make_managed<Gtk::Grid>();
					zhicone->set_hexpand(true);
					zhicone->set_halign(Gtk::Align::END);
					auto labicodrt = Gtk::make_managed<Gtk::Label>("droite");
					hticodrt = Gtk::make_managed<Gtk::SpinButton>();
						hticodrt->set_range(10,50);
						hticodrt->set_increments(1,5);
					auto labicoctr = Gtk::make_managed<Gtk::Label>("dessus");
					hticoctr = Gtk::make_managed<Gtk::SpinButton>();
						hticoctr->set_range(10,50);
						hticoctr->set_increments(1,5);
					auto labicogah = Gtk::make_managed<Gtk::Label>("gauche");
					hticogah = Gtk::make_managed<Gtk::SpinButton>();
						hticogah->set_range(10,50);
						hticogah->set_increments(1,5);
					zhicone->attach(*labicodrt, 0, 0);
					zhicone->attach(*labicoctr, 1, 0);
					zhicone->attach(*labicogah, 2, 0);
					zhicone->attach(*hticodrt, 0, 1);
					zhicone->attach(*hticoctr, 1, 1);
					zhicone->attach(*hticogah, 2, 1);
			zicone->append(*labicone);
			zicone->append(*zhicone);
			auto zcoulfon = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 4 );
				zcoulfon->set_hexpand(true);
				zcoulfon->set_halign(Gtk::Align::END);
				auto labcoufon = Gtk::make_managed<Gtk::Label>("couleur fond");
					labcoufon->set_hexpand(true);
					labcoufon->set_halign(Gtk::Align::CENTER);
					labcoufon->set_justify(Gtk::Justification::CENTER);
				auto zgrifon = Gtk::make_managed<Gtk::Grid>();
					zgrifon->set_hexpand(true);
					zgrifon->set_halign(Gtk::Align::END);
				auto labcoulmenu = Gtk::make_managed<Gtk::Label>("menu");
				coulmenu = Gtk::make_managed<Gtk::ColorButton>();
					coulmenu->set_hexpand(true);
				auto labcoulgraf = Gtk::make_managed<Gtk::Label>("graphique");
				coulgraf = Gtk::make_managed<Gtk::ColorButton>();
				coulgraf->set_hexpand(true);
					zgrifon->attach(*labcoulmenu, 0, 0);
					zgrifon->attach(*labcoulgraf, 0, 1);
					zgrifon->attach(*coulmenu, 1, 0);
					zgrifon->attach(*coulgraf, 1, 1);
			zcoulfon->append(*labcoufon);
			zcoulfon->append(*zgrifon);
		zbarrebas->append(*zicone);
		zbarrebas->append(*zcoulfon);
		
//	CGeneral->append(*zmodcfg);
//	CGeneral->append(*sep01);
	CGeneral->append(*titre01);
	CGeneral->append(*zpolice);
	CGeneral->append(*zbarrebas);
}
void DialogConfigGenerale::MasqueOngletConnexion()
{
	const std::vector<Glib::ustring> typlgn{ "continu", "tirets", "pointillé", "axe" };
	Glib::RefPtr<Gtk::StringList> lsttyplgn;
	lsttyplgn = Gtk::StringList::create(typlgn);

// ci-dessous : en attente de titrage de bloc ligne
	const std::vector<Glib::ustring> libellecadre{ "entre logiciel", "fichier travail", "fichier configuration" };
	Clstconnex = Gtk::StringList::create(libellecadre);

	auto titre01 = Gtk::make_managed<Gtk::Label>("Graphisme de connecteurs");
		titre01->set_margin(20);
		titre01->set_halign(Gtk::Align::CENTER);
		titre01->set_justify(Gtk::Justification::CENTER);
		
	auto zblcnxhaut = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	auto zcnxgah = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto ascconnex = Gtk::make_managed<Gtk::ScrolledWindow>();
			ascconnex->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
			auto signallstcnx = Gtk::SignalListItemFactory::create();
				signallstcnx->signal_setup().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ConfigLibelle));
				signallstcnx->signal_bind().connect(sigc::mem_fun(*this, &DialogConfigGenerale::AttacheNomConnexion));
			selcnx = Gtk::SingleSelection::create();
				selcnx->set_autoselect(false);
				selcnx->set_can_unselect(true);
				selcnx->signal_selection_changed().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChangerConnexion));
			auto lstconnex = Gtk::make_managed<Gtk::ListView>();
				lstconnex->set_model(selcnx);
				lstconnex->add_css_class("data-table");
				lstconnex->set_factory(signallstcnx);
		ascconnex->set_child(*lstconnex);
	zcnxgah->append(*ascconnex);	
		
	
	auto ztypcox = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 4 );
		ztypcox->set_hexpand(true);
		ztypcox->set_halign(Gtk::Align::CENTER);
		auto labtyplgn = Gtk::make_managed<Gtk::Label>("type de ligne");
		chxtplcnx = Gtk::make_managed<Gtk::DropDown>();
			chxtplcnx->set_model(lsttyplgn);
			chxtplcnx->set_selected(0);
		auto labeprlgn = Gtk::make_managed<Gtk::Label>("épaisseur");
		eprlgncnx = Gtk::make_managed<Gtk::SpinButton>();
			eprlgncnx->set_range(1,10);
			eprlgncnx->set_increments(1,2);
			coulcnx = Gtk::make_managed<Gtk::ColorButton>();
				coulcnx->set_hexpand(true);
		ztypcox->append(*labtyplgn);
		ztypcox->append(*chxtplcnx);
		ztypcox->append(*labeprlgn);
		ztypcox->append(*eprlgncnx);
		ztypcox->append(*coulcnx);
	zcnxgah->append(*ztypcox);	

	zblcnxhaut->append(*zcnxgah);
	
	auto titre02 = Gtk::make_managed<Gtk::Label>("Ancre pour connexion entre graphisme");
		titre02->set_margin(20);
		titre02->set_halign(Gtk::Align::CENTER);
		titre02->set_justify(Gtk::Justification::CENTER);

	auto znmficico = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
		auto labficico	= Gtk::make_managed<Gtk::Label>();
			labficico->set_text("nom du fichier icone\nplacé à la racine de l'application");
			labficico->set_wrap();
			labficico->set_hexpand(true);
			labficico->set_halign(Gtk::Align::START);
			labficico->set_justify(Gtk::Justification::CENTER);
		edinomficico = Gtk::make_managed<Gtk::Entry>();
			edinomficico->set_hexpand(true);
		auto btnchxico = Gtk::make_managed<Gtk::Button>("...");
			btnchxico->set_expand(false);
			btnchxico->signal_clicked().connect(
								sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),1 ));
	znmficico->append(*labficico);
	znmficico->append(*edinomficico);
	znmficico->append(*btnchxico);
	
	auto zcaricone = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 8 );	
		zcaricone->set_hexpand(true);
		zcaricone->set_halign(Gtk::Align::CENTER);
		auto labsymbico = Gtk::make_managed<Gtk::Label>("symbole");
		auto labdimicolarg = Gtk::make_managed<Gtk::Label>("largeur");
		lgico = Gtk::make_managed<Gtk::SpinButton>();
			lgico->set_range(10,50);
			lgico->set_increments(1,5);
		auto labdimicohaut = Gtk::make_managed<Gtk::Label>("hauteur");
		htico = Gtk::make_managed<Gtk::SpinButton>();
			htico->set_range(10,50);
			htico->set_increments(1,5);
		auto labcouico = Gtk::make_managed<Gtk::Label>("couleur fond");
		coulfndico = Gtk::make_managed<Gtk::ColorButton>();
			coulfndico->set_hexpand(false);
			
		zcaricone->append(*labsymbico);
		zcaricone->append(*labdimicolarg);
		zcaricone->append(*lgico);
		zcaricone->append(*labdimicohaut);
		zcaricone->append(*htico);
		zcaricone->append(*labcouico);
		zcaricone->append(*coulfndico);
	auto zpoliceico = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 4 );
		zpoliceico->set_hexpand(true);
			auto labpolico	= Gtk::make_managed<Gtk::Label>("Police de caractères");
			labpolico->set_halign(Gtk::Align::START);
			btnchxpolico	= Gtk::make_managed<Gtk::FontButton>();
				btnchxpolico->set_halign(Gtk::Align::CENTER);
				btnchxpolico->set_hexpand(true);
			coulpolico = Gtk::make_managed<Gtk::ColorButton>();
				coulpolico->set_hexpand(false);
				coulpolico->set_halign(Gtk::Align::END);
		zpoliceico->append(*labpolico);
		zpoliceico->append(*btnchxpolico);
		zpoliceico->append(*coulpolico);
		
	CConnexion->append(*titre01);
	CConnexion->append(*zblcnxhaut);
	CConnexion->append(*titre02);
	CConnexion->append(*znmficico);
	CConnexion->append(*zcaricone);
	CConnexion->append(*zpoliceico);
}
void DialogConfigGenerale::MasqueOngletLogiciel()
{
	auto zblochaut = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	auto zbloccentre = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
	auto zblocbas = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	
	auto zblochautgah = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titre11 = Gtk::make_managed<Gtk::Label>("logiciels");
			titre11->set_margin(10);
			titre11->set_halign(Gtk::Align::CENTER);
		auto zblocbouton = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 8 );
			auto btnajoutlog = Gtk::make_managed<Gtk::Button>("ajouter");
				btnajoutlog->set_halign(Gtk::Align::START);
				btnajoutlog->set_hexpand(true);
				btnajoutlog->signal_clicked().connect(
							sigc::mem_fun(*this, &DialogConfigGenerale::AjouterUnLogiciel));
			auto btnsupprlog = Gtk::make_managed<Gtk::Button>("supprimer");
				btnsupprlog->set_halign(Gtk::Align::END);
				btnsupprlog->set_hexpand(true);
				btnsupprlog->signal_clicked().connect(
							sigc::mem_fun(*this, &DialogConfigGenerale::SupprimerLogiciel));
			zblocbouton->append(*btnajoutlog);
			zblocbouton->append(*btnsupprlog);

		auto asclogi = Gtk::make_managed<Gtk::ScrolledWindow>();
			asclogi->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
			asclogi->set_expand(true);
			auto signallstlogiciel = Gtk::SignalListItemFactory::create();
				signallstlogiciel->signal_setup().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ConfigLibelle));
				signallstlogiciel->signal_bind().connect(sigc::mem_fun(*this, &DialogConfigGenerale::AttacheNomLogiciel));
			sellogiciel = Gtk::SingleSelection::create();
				sellogiciel->set_autoselect(false);
				sellogiciel->set_can_unselect(true);
				sellogiciel->signal_selection_changed().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChangerLogiciel));
			auto lstlogiciel = Gtk::make_managed<Gtk::ListView>();
				lstlogiciel->set_model(sellogiciel);
				lstlogiciel->add_css_class("data-table");
				lstlogiciel->set_factory(signallstlogiciel);
		asclogi->set_child(*lstlogiciel);
		
	zblochautgah->append(*titre11);	
	zblochautgah->append(*zblocbouton);	
	zblochautgah->append(*asclogi);
		
	auto zblochautdrt = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto zlign01 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre12 = Gtk::make_managed<Gtk::Label>();
				titre12->set_text("Délai d'attente après\nlancement en secondes");
				titre12->set_wrap();
				titre12->set_hexpand(true);
				titre12->set_halign(Gtk::Align::END);
				titre12->set_justify(Gtk::Justification::CENTER);
			delatt = Gtk::make_managed<Gtk::SpinButton>();
				delatt->set_range(1,10);
				delatt->set_value(5);	
				delatt->set_increments(1,2);
		zlign01->append(*titre12);
		zlign01->append(*delatt);
		auto titre14 = Gtk::make_managed<Gtk::Label>("Nom du processus");
			titre14->set_margin(8);
			titre14->set_halign(Gtk::Align::START);
		auto zlign02 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			edinomproc = Gtk::make_managed<Gtk::Entry>();
			edinomproc->set_hexpand(true);
		auto btnchxpro = Gtk::make_managed<Gtk::Button>("...");
			btnchxpro->set_expand(false);
			btnchxpro->signal_clicked().connect(
								sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),2 ));
		zlign02->append(*edinomproc);
		zlign02->append(*btnchxpro);
		auto zlign03 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre15 = Gtk::make_managed<Gtk::Label>("colone dans le menu");
				titre15->set_margin(8);
				titre15->set_halign(Gtk::Align::START);
			poscol = Gtk::make_managed<Gtk::SpinButton>();
				poscol->set_range(1,5);
				poscol->set_value(1);	
				poscol->set_increments(1,1);
		zlign03->append(*titre15);
		zlign03->append(*poscol);
		occunique = Gtk::make_managed<Gtk::CheckButton>("un seul représentant de ce logiciel");

	zblochautdrt->append(*zlign01);
	zblochautdrt->append(*titre14);
	zblochautdrt->append(*zlign02);
	zblochautdrt->append(*zlign03);
	zblochautdrt->append(*occunique);
	
	zblochaut->append(*zblochautgah);
	zblochaut->append(*zblochautdrt);


		auto zlign04 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre18 = Gtk::make_managed<Gtk::Label>("liste des options ex : -u,-l,--G");
				titre18->set_halign(Gtk::Align::START);
			auto titre16 = Gtk::make_managed<Gtk::Label>("Liste variables de l'application");
				titre16->set_hexpand(true);
				titre16->set_halign(Gtk::Align::END);
			zlign04->append(*titre18);
			zlign04->append(*titre16);
		auto zlign05 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			edilstopt = Gtk::make_managed<Gtk::Entry>();
				edilstopt->set_hexpand(true);
			auto btntrsvar = Gtk::make_managed<Gtk::Button>("<<<");
				btntrsvar->set_expand(false);
				btntrsvar->signal_clicked().connect(
									sigc::mem_fun(*this, &DialogConfigGenerale::TransfererVariable));
			chxlstvar = Gtk::make_managed<Gtk::DropDown>();		
				chxlstvar->set_model(lstvariable);
				chxlstvar->set_selected(0);
		//		chxlstvar.property_selected().signal_changed().connect(
		//							sigc::mem_fun(*this, &DialogConfigGenerale::changervariable));
			auto btnaidevar = Gtk::make_managed<Gtk::Button>("?");
				btnaidevar->set_expand(false);
				btnaidevar->signal_clicked().connect(
										sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::VoirAideVariable),0));
		zlign05->append(*edilstopt);
		zlign05->append(*btntrsvar);
		zlign05->append(*chxlstvar);
		zlign05->append(*btnaidevar);
		
		auto zlign06 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre19 = Gtk::make_managed<Gtk::Label>("Options pour les fichiers attachés");
				titre19->set_halign(Gtk::Align::START);
			auto titre17 = Gtk::make_managed<Gtk::Label>("Nom du fichier icone");
				titre17->set_hexpand(true);
				titre17->set_halign(Gtk::Align::END);
		zlign06->append(*titre19);
		zlign06->append(*titre17);
		auto zlign07 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre20 = Gtk::make_managed<Gtk::Label>("TRV");
			auto titre21 = Gtk::make_managed<Gtk::Label>("CFG");
			ediopttrv = Gtk::make_managed<Gtk::Entry>();
				ediopttrv->set_text("");
				ediopttrv->set_hexpand(true);
			edioptcfg = Gtk::make_managed<Gtk::Entry>();
				edioptcfg->set_text("");
				edioptcfg->set_hexpand(true);
				
			edinomfico = Gtk::make_managed<Gtk::Entry>();
				edinomfico->set_text("/icone/dgdemlogstart.png");
				edinomfico->set_hexpand(true);
			auto btnchxfico = Gtk::make_managed<Gtk::Button>("...");
				btnchxfico->set_expand(false);
				btnchxfico->signal_clicked().connect(
									sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),3 ));
		zlign07->append(*titre20);
		zlign07->append(*ediopttrv);
		zlign07->append(*titre21);
		zlign07->append(*edioptcfg);
		zlign07->append(*edinomfico);
		zlign07->append(*btnchxfico);
	zbloccentre->append(*zlign04);
	zbloccentre->append(*zlign05);
	zbloccentre->append(*zlign06);
	zbloccentre->append(*zlign07);

		auto zblocbasgah = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
			auto titre22 = Gtk::make_managed<Gtk::Label>("dossier du processus");
				titre22->set_halign(Gtk::Align::START);
			auto titre23 = Gtk::make_managed<Gtk::Label>("processus dépendants du\nprocessus principal à stopper");
				titre23->set_halign(Gtk::Align::START);
			auto titre25 = Gtk::make_managed<Gtk::Label>("nom du fichier standard\nde travail");
				titre25->set_halign(Gtk::Align::START);
			auto titre24 = Gtk::make_managed<Gtk::Label>("nom du fichier standard\nde configuration");
				titre24->set_halign(Gtk::Align::START);
			auto titre26 = Gtk::make_managed<Gtk::Label>("phrase d'aide");
				titre26->set_halign(Gtk::Align::START);
		zblocbasgah->append(*titre22);
		zblocbasgah->append(*titre23);
		zblocbasgah->append(*titre25);
		zblocbasgah->append(*titre24);
		zblocbasgah->append(*titre26);
		auto zblocbasdrt = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
			auto zlign08 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
				edidospro = Gtk::make_managed<Gtk::Entry>();
					edidospro->set_text("/user/bin/");
					edidospro->set_hexpand(true);
				auto btnchxdospro = Gtk::make_managed<Gtk::Button>("...");
					btnchxdospro->set_expand(false);
					btnchxdospro->signal_clicked().connect(
										sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),4 ));
			zlign08->append(*edidospro);	
			zlign08->append(*btnchxdospro);	
				
			ediprodep = Gtk::make_managed<Gtk::Entry>();
				ediprodep->set_text("");
				ediprodep->set_hexpand(true);
				
			auto zlign09 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
				edificstdtrv = Gtk::make_managed<Gtk::Entry>();
					edificstdtrv->set_hexpand(true);
				auto btnchxfictrv = Gtk::make_managed<Gtk::Button>("...");
					btnchxfictrv->set_expand(false);
					btnchxfictrv->signal_clicked().connect(
										sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),5 ));
			zlign09->append(*edificstdtrv);	
			zlign09->append(*btnchxfictrv);	
					
			auto zlign10 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
				edificstdcfg = Gtk::make_managed<Gtk::Entry>();
					edificstdcfg->set_hexpand(true);
				auto btnchxficcfg = Gtk::make_managed<Gtk::Button>("...");
					btnchxficcfg->set_expand(false);
					btnchxficcfg->signal_clicked().connect(
										sigc::bind(sigc::mem_fun(*this, &DialogConfigGenerale::ChoisirFichier),6 ));
			zlign10->append(*edificstdcfg);	
			zlign10->append(*btnchxficcfg);	
									
			ediphraide = Gtk::make_managed<Gtk::Entry>();
				ediphraide->set_text("ex : ouvrir un texte simple");
				ediphraide->set_hexpand(true);
				
	zblocbasdrt->append(*zlign08);
	zblocbasdrt->append(*ediprodep);
	zblocbasdrt->append(*zlign09);
	zblocbasdrt->append(*zlign10);
	zblocbasdrt->append(*ediphraide);

	zblocbas->append(*zblocbasgah);
	zblocbas->append(*zblocbasdrt);

	CLogiciel->append(*zblochaut);
	CLogiciel->append(*zbloccentre);
	CLogiciel->append(*zblocbas);
}
void DialogConfigGenerale::MasqueOngletPriorite()
{
	auto zblprphaut = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
		zblprphaut->set_vexpand(true);
	auto zblprpbas = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	auto zblprphautgah = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titre30 = Gtk::make_managed<Gtk::Label>("Priorité démarrage");
			titre30->set_margin(10);
			titre30->set_halign(Gtk::Align::CENTER);
		auto zblocbtnprio = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 8 );
			auto btnajoutprp = Gtk::make_managed<Gtk::Button>("ajouter");
				btnajoutprp->set_halign(Gtk::Align::START);
				btnajoutprp->set_hexpand(true);
				btnajoutprp->signal_clicked().connect(
					sigc::mem_fun(*this, &DialogConfigGenerale::AjouterUnePriorite ));
			auto btnsupprprp = Gtk::make_managed<Gtk::Button>("supprimer");
				btnsupprprp->set_halign(Gtk::Align::END);
				btnsupprprp->set_hexpand(true);
				btnsupprprp->signal_clicked().connect(
					sigc::mem_fun(*this, &DialogConfigGenerale::SupprimerPriorite ));
			zblocbtnprio->append(*btnajoutprp);
			zblocbtnprio->append(*btnsupprprp);
		auto ascprio = Gtk::make_managed<Gtk::ScrolledWindow>();
			ascprio->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
			ascprio->set_size_request(200,100);
			auto signallstprio = Gtk::SignalListItemFactory::create();
				signallstprio->signal_setup().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ConfigLibelle));
				signallstprio->signal_bind().connect(sigc::mem_fun(*this, &DialogConfigGenerale::AttacheNomPriorite));
			selprio = Gtk::SingleSelection::create();
				selprio->set_autoselect(false);
				selprio->set_can_unselect(true);
				selprio->signal_selection_changed().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChangerPriorite));
			auto lstpriorite = Gtk::make_managed<Gtk::ListView>();
				lstpriorite->set_model(selprio);
				lstpriorite->add_css_class("data-table");
				lstpriorite->set_factory(signallstprio);
		ascprio->set_child(*lstpriorite);
		auto zlign30 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre301 = Gtk::make_managed<Gtk::Label>("niveau de priorité");
				titre301->set_hexpand(true);
				titre301->set_halign(Gtk::Align::START);
			nivprio = Gtk::make_managed<Gtk::SpinButton>();
				nivprio->set_range(1,254);
				nivprio->set_increments(1,10);
		zlign30->append(*titre301);	
		zlign30->append(*nivprio);	
		
	zblprphautgah->append(*titre30);	
	zblprphautgah->append(*zblocbtnprio);	
	zblprphautgah->append(*ascprio);
	zblprphautgah->append(*zlign30);
	
	auto zblprphautdrt = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto zlign31 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre31 = Gtk::make_managed<Gtk::Label>("largeur symbole");
				titre31->set_hexpand(true);
				titre31->set_halign(Gtk::Align::START);
			larsym = Gtk::make_managed<Gtk::SpinButton>();
				larsym->set_range(80,200);
				larsym->set_increments(5,20);
		zlign31->append(*titre31);
		zlign31->append(*larsym);
		auto zlign32 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre32 = Gtk::make_managed<Gtk::Label>("hauteur symbole");
				titre32->set_hexpand(true);
				titre32->set_halign(Gtk::Align::START);
			htrsym = Gtk::make_managed<Gtk::SpinButton>();
				htrsym->set_range(20,70);
				htrsym->set_increments(5,20);
		zlign32->append(*titre32);
		zlign32->append(*htrsym);
		auto zlign33 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre33 = Gtk::make_managed<Gtk::Label>("couleur fond");
				titre33->set_hexpand(true);
				titre33->set_halign(Gtk::Align::START);
			clsymfond = Gtk::make_managed<Gtk::ColorButton>();
				clsymfond->set_expand(false);
		zlign33->append(*titre33);
		zlign33->append(*clsymfond);
		auto zlign34 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre34 = Gtk::make_managed<Gtk::Label>("couleur bandeau");
				titre34->set_hexpand(true);
				titre34->set_halign(Gtk::Align::START);
			clsymband = Gtk::make_managed<Gtk::ColorButton>();
				clsymband->set_expand(false);
		zlign34->append(*titre34);
		zlign34->append(*clsymband);
	zblprphautdrt->append(*zlign31);
	zblprphautdrt->append(*zlign32);
	zblprphautdrt->append(*zlign33);
	zblprphautdrt->append(*zlign34);
	
	zblprphaut->append(*zblprphautgah);
	zblprphaut->append(*zblprphautdrt);
	
	zblprpbas->set_hexpand(true);
		auto labpolsym	= Gtk::make_managed<Gtk::Label>("Police de caractères");
		labpolsym->set_halign(Gtk::Align::START);
		btnchxpolsym	= Gtk::make_managed<Gtk::FontButton>();
			btnchxpolsym->set_halign(Gtk::Align::CENTER);
			btnchxpolsym->set_hexpand(true);
		coulpolsym = Gtk::make_managed<Gtk::ColorButton>();
			coulpolsym->set_hexpand(false);
			coulpolsym->set_halign(Gtk::Align::END);
	zblprpbas->append(*labpolsym);
	zblprpbas->append(*btnchxpolsym);
	zblprpbas->append(*coulpolsym);

	auto sep31 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	CPriorite->append(*zblprphaut);
	CPriorite->append(*sep31);
	CPriorite->append(*zblprpbas);
}
void DialogConfigGenerale::MasqueOngletFichierLie()
{
	auto zblflihaut = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	auto zblflibas = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
	
	auto zblflihautgah = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titre40 = Gtk::make_managed<Gtk::Label>("fichier lié au logiciel");
			titre40->set_margin(10);
			titre40->set_halign(Gtk::Align::CENTER);
	
		auto ascficlie = Gtk::make_managed<Gtk::ScrolledWindow>();
			ascficlie->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
			auto signallstfli = Gtk::SignalListItemFactory::create();
				signallstfli->signal_setup().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ConfigLibelle));
				signallstfli->signal_bind().connect(sigc::mem_fun(*this, &DialogConfigGenerale::AttacheNomFicLie));
			selfli = Gtk::SingleSelection::create();
				selfli->set_autoselect(false);
				selfli->set_can_unselect(true);
				selfli->signal_selection_changed().connect(sigc::mem_fun(*this, &DialogConfigGenerale::ChangerFicLie));
			auto lstficlie = Gtk::make_managed<Gtk::ListView>();
				lstficlie->set_model(selfli);
				lstficlie->add_css_class("data-table");
				lstficlie->set_factory(signallstfli);
		ascficlie->set_child(*lstficlie);
	zblflihautgah->append(*titre40);	
	zblflihautgah->append(*ascficlie);	
		
	auto zblflihautdrt = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto zlign41 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre41 = Gtk::make_managed<Gtk::Label>("largeur symbole");
				titre41->set_hexpand(true);
				titre41->set_halign(Gtk::Align::START);
			larfli = Gtk::make_managed<Gtk::SpinButton>();
				larfli->set_range(80,200);
				larfli->set_increments(5,20);
		zlign41->append(*titre41);
		zlign41->append(*larfli);
		auto zlign42 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre42 = Gtk::make_managed<Gtk::Label>("hauteur symbole");
				titre42->set_hexpand(true);
				titre42->set_halign(Gtk::Align::START);
			htrfli = Gtk::make_managed<Gtk::SpinButton>();
				htrfli->set_range(20,70);
				htrfli->set_increments(5,20);
		zlign42->append(*titre42);
		zlign42->append(*htrfli);

		auto zlign43 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre43 = Gtk::make_managed<Gtk::Label>("couleur fond");
				titre43->set_hexpand(true);
				titre43->set_halign(Gtk::Align::START);
			clflifond = Gtk::make_managed<Gtk::ColorButton>();
				clflifond->set_expand(false);
		zlign43->append(*titre43);
		zlign43->append(*clflifond);
		auto zlign44 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			auto titre44 = Gtk::make_managed<Gtk::Label>("couleur bandeau");
				titre44->set_hexpand(true);
				titre44->set_halign(Gtk::Align::START);
			clfliband = Gtk::make_managed<Gtk::ColorButton>();
				clfliband->set_expand(false);
		zlign44->append(*titre44);
		zlign44->append(*clfliband);

	zblflihautdrt->append(*zlign41);
	zblflihautdrt->append(*zlign42);
	zblflihautdrt->append(*zlign43);
	zblflihautdrt->append(*zlign44);

	zblflihaut->append(*zblflihautgah);
	zblflihaut->append(*zblflihautdrt);
	
	zblflibas->set_hexpand(true);
		auto labpolfli	= Gtk::make_managed<Gtk::Label>("Police de caractères");
		labpolfli->set_halign(Gtk::Align::START);
		btnchxpolfli	= Gtk::make_managed<Gtk::FontButton>();
			btnchxpolfli->set_halign(Gtk::Align::CENTER);
			btnchxpolfli->set_hexpand(true);
		coulpolfli = Gtk::make_managed<Gtk::ColorButton>();
			coulpolfli->set_hexpand(false);
			coulpolfli->set_halign(Gtk::Align::END);
	zblflibas->append(*labpolfli);
	zblflibas->append(*btnchxpolfli);
	zblflibas->append(*coulpolfli);

	auto sep41 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	CGraphlie->append(*zblflihaut);
	CGraphlie->append(*sep41);
	CGraphlie->append(*zblflibas);

}
void DialogConfigGenerale::MiseAJourOngletApplication()
{
	btnchxpol->property_font() = std::string( (char *)econfig.Police().nom.v );
	coulpol->property_rgba()	= Gdk::RGBA( std::string( (char *)econfig.Police().couleur.v ) );
	coulmenu->property_rgba()	= Gdk::RGBA(econfig.CouleurMenu());
	coulgraf->property_rgba()	= Gdk::RGBA(econfig.CouleurGraphique());
	hticodrt->set_value(econfig.IconeGestion());	
	hticoctr->set_value(econfig.IconeDessus());	
	hticogah->set_value(econfig.IconeSymbole());
}
void DialogConfigGenerale::MiseAJourOngletConnexion()
{// indconnex doit être initialisé
	ptrenrconnexion ptrconnex = elstconnex.Position( indconnex );
	chxtplcnx->set_selected( ptrconnex->TypeLigne() );
	eprlgncnx->set_value( ptrconnex->Epaisseur() );
	coulcnx->property_rgba()	= Gdk::RGBA( ptrconnex->Couleur() );

	edinomficico->set_text( eancre.Nom() );
	lgico->set_value(eancre.Largeur());
	htico->set_value(eancre.Hauteur());
	coulfndico->property_rgba()	= Gdk::RGBA(eancre.CouleurFond());
	btnchxpolico->property_font() =  std::string( (char *)eancre.Police().nom.v);
	coulpolico->property_rgba()	=  Gdk::RGBA( std::string( (char *)eancre.Police().couleur.v));
}
void DialogConfigGenerale::MiseAJourOngletLogiciel()
{// indlogiciel doit être initialisé
	if(elstlogiciel.TailleListe()>0)
	{
		ptrlog = elstlogiciel.Position(indlogiciel);
		delatt->set_value(ptrlog->Delai());	
		edinomproc->set_text(ptrlog->NomProcessus());
		poscol->set_value(ptrlog->Classe()+1);	
		occunique->set_active(ptrlog->UniqueB());
		edilstopt->set_text(ptrlog->Options());
		ediopttrv->set_text(ptrlog->OptTRV());
		edioptcfg->set_text(ptrlog->OptCFG());
		edinomfico->set_text(ptrlog->Icone());
		edidospro->set_text(ptrlog->Dossier());
		ediprodep->set_text(ptrlog->Dependance());
		edificstdtrv->set_text(ptrlog->StdTRV());
		edificstdcfg->set_text(ptrlog->StdCFG());
		ediphraide->set_text(ptrlog->Aide());
	}
}
void DialogConfigGenerale::MiseAJourOngletPriorite()
{// indexprio doit être initialisé
	ptrenrgraphique ptrgraph = elstgraph.Position(indexprio);
	nivprio->set_value(ptrgraph->ValeurPriorite());	
	larsym->set_value(ptrgraph->Largeur());	
	htrsym->set_value(ptrgraph->Hauteur());
	clsymfond->property_rgba()	= Gdk::RGBA(ptrgraph->CouleurFond());
	clsymband->property_rgba()	= Gdk::RGBA(ptrgraph->CouleurBandeau());
	coulpolsym->property_rgba()	= Gdk::RGBA(std::string( (char *)ptrgraph->Police().couleur.v));
	btnchxpolsym->property_font() = std::string( (char *)ptrgraph->Police().nom.v);
	nivprio->set_visible(indexprio!=0);
}  
void DialogConfigGenerale::MiseAJourOngletFichierLie()
{// indexflie doit être initialisé
	ptrenrgraphique ptrgraph = elstficlie.Position(indexflie);
	larfli->set_value(ptrgraph->Largeur());	
	htrfli->set_value(ptrgraph->Hauteur());
	clfliband->property_rgba()	= Gdk::RGBA(ptrgraph->CouleurBandeau());
	clflifond->property_rgba()	= Gdk::RGBA(ptrgraph->CouleurFond());
	coulpolfli->property_rgba()	= Gdk::RGBA(std::string( (char *)ptrgraph->Police().couleur.v));	
	btnchxpolfli->property_font() = std::string( (char *)ptrgraph->Police().nom.v);
}
void DialogConfigGenerale::CreerNouvEnrgLogiciel()
{
	elstlogiciel.Ajouter(edinomproc->get_text(),chainetmp,"","",edidospro->get_text(),"","",5,0,1,"","","","");
	indlogiciel = elstlogiciel.TailleListe()-1;
	Clstlogiciel->append(chainetmp);
	sellogiciel->set_selected(indlogiciel);
	pFncVoid = nullptr;
	MiseAJourOngletLogiciel();
}
void DialogConfigGenerale::CreerNouvEnrgPriorite()
{
	EnrgPolice policetmp("DejaVu Sans Mono 8","rgb(0,0,0)");
    elstgraph.Ajouter( chainetmp,
						"rgb(165,128,128)","rgb(88,44,44)",
						policetmp.Police(),160,50,127);
	indexprio = elstgraph.TailleListe()-1;
	Clstpriorite->append(chainetmp);
	selprio->set_selected(indexprio);
	pFncVoid = nullptr;
	MiseAJourOngletPriorite();
}
void DialogConfigGenerale::ConfigLibelle(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}
void DialogConfigGenerale::AttacheNomLogiciel(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstlogiciel->get_string(pos));
}
void DialogConfigGenerale::AttacheNomPriorite(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstpriorite->get_string(pos));
}
void DialogConfigGenerale::AttacheNomFicLie(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstficlie->get_string(pos));
}
void DialogConfigGenerale::AttacheNomConnexion(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstconnex->get_string(pos));
}
void DialogConfigGenerale::SaisirValeur(const Glib::ustring& liblibel, const uint8_t &typezone )
{
	if(liblibel.empty())
	{
		if(msgmsa!=nullptr)
		{
			if(typezone!=0)
			{
				(this->*pFncRetourValeur)(typezone);
			}
			delete msgmsa;
			msgmsa=nullptr;
		}
	}
	else
	{
		if(msgmsa!=nullptr) delete msgmsa;
		msgmsa = new BoiteDialogue(this,liblibel,typezone);
		msgmsa->connexionChoix(sigc::mem_fun(*this, &DialogConfigGenerale::SaisirValeur));
	}
}
void DialogConfigGenerale::QuestionOuiNon(const Glib::ustring& libmess,const Glib::ustring& libques)
{
	if(libques.empty())
	{
		if(msgmsa!=nullptr)
		{
			delete msgmsa;
			msgmsa=nullptr;
			if(libmess=="OK")
				(this->*pFncAppeloui)();
			else
				if(pFncAppelnon!=nullptr)
					(this->*pFncAppelnon)();
		}
	}
	else
	{
		if(msgmsa!=nullptr) delete msgmsa;
		msgmsa = new BoiteDialogue;
		msgmsa->AppelQuestion(this,libques,libmess);
		msgmsa->connexionQuest(sigc::mem_fun(*this, &DialogConfigGenerale::QuestionOuiNon));
	}
}
void DialogConfigGenerale::MessageInfo( const Glib::ustring &libmess)
{
	if(libmess.empty())
	{
		if(msgmsa!=nullptr)
		{
		  delete msgmsa;
		  msgmsa=nullptr;
		}
	}
	else
	{
		if(msgmsa!=nullptr) delete msgmsa;
		msgmsa = new BoiteDialogue(this,libmess);
		msgmsa->connexionInfo(sigc::mem_fun(*this, &DialogConfigGenerale::MessageInfo));
	}
}
