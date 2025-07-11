/*
 * fenetre.cpp
 * 2023 daniel 
 */
#include <iostream>
#include "creercontexte.h"

//CreerContexte::CreerContexte( DGChaineListe *pstprojet, EnrgSessionProjet *pvalenrg )
CreerContexte::CreerContexte( FBlocProjet *pprojet, DGChaineListe *plisteconfig )
{
	saisiedate	= nullptr;
	ptrprojet	= pprojet;
	set_title("Créer un contexte");
	set_default_size(550, 350);
/*
		date du jour pour nouveau contexte
*/
	libstr.resize(50);
	setlocale(LC_TIME, "fr_FR.UTF-8");
	time_t datedujour;
	time (&datedujour);
	nrgdate = localtime (&datedujour);
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", nrgdate);
	strdatejour = libstr;
/*
		lister les projets existants
*/
	listeprojet.Vider();
	listecontexte.Vider();
	ptrprojet->Lister( listeprojet );
	listeprojet.ListerVers( Clstprojet );
	if(listeprojet.TailleListe()>0)
	{
		if( ptrprojet->Nom().empty() )
			ptrprojet->LirePremierProjet();
		else
			ptrprojet->LireProjet( ptrprojet->Nom() );
	
		ptrprojet->ListerContexte(listecontexte);
		listecontexte.ListerVers(Clstcontexte);
		if(listecontexte.TailleListe()>0)
		{
			ptrprojet->LirePremierContexte();
		}
	}
/*
		liste des configurations
*/
	*listeconfig.PtrChaine() = *plisteconfig->PtrChaine();
	Glib::RefPtr<Gtk::StringList> lstconfig;
	listeconfig.ListerVers( lstconfig );
//	lstconfig = Gtk::StringList::create(lstcfg);						

/*
		creer nom par defaut du nouveau contexte
*/
    nomtest = "nouveaucontexte";
    int increment=0;
    while(listecontexte.Trouver(nomtest))
		nomtest = "nouveaucontexte" + std::to_string(increment++);
/*
 ************** 
 Zone liste Projet
 ************** 
*/
	auto zprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titprojet = Gtk::make_managed<Gtk::Label>("Projets existants");
		titprojet->set_halign(Gtk::Align::CENTER);
		titprojet->set_hexpand();
		auto zhprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto zdateprj = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
				auto labdateprj = Gtk::make_managed<Gtk::Label>("date création");
				labdateprj->set_halign(Gtk::Align::START);
				dateprojet = Gtk::make_managed<Gtk::Label>(libstr);
				dateprojet->set_justify(Gtk::Justification::RIGHT);
				zdateprj->append(*labdateprj);
				zdateprj->append(*dateprojet);
			auto manoeuvre = Gtk::SignalListItemFactory::create();
				manoeuvre->signal_setup().connect(sigc::mem_fun(*this, &CreerContexte::ConfigLibelle));
				manoeuvre->signal_bind().connect(sigc::mem_fun(*this, &CreerContexte::AttacheNomProjet));
			selprojet = Gtk::SingleSelection::create(Clstprojet);
				selprojet->set_autoselect(false);
				selprojet->set_can_unselect(true);
				selprojet->signal_selection_changed().connect(sigc::mem_fun(*this, &CreerContexte::ChangerProjet));
			ascenceur = Gtk::make_managed<Gtk::ScrolledWindow>();
				ascenceur->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
				ascenceur->set_hexpand();
				ascenceur->set_max_content_height( 5 );
				ascenceur->set_min_content_height( 5 );
			lstprojet = Gtk::make_managed<Gtk::ListView>();
				lstprojet->set_model(selprojet);
				lstprojet->add_css_class("data-table");
			ascenceur->set_child(*lstprojet);
			lstprojet->set_factory(manoeuvre);
		zhprojet->append(*zdateprj);		
		zhprojet->append(*ascenceur);
		auto zcomprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto labcomtprj = Gtk::make_managed<Gtk::Label>();
				labcomtprj->set_text("commentaire\nsur ce projet");
				labcomtprj->set_wrap();
         		labcomtprj->set_hexpand(true);
				labcomtprj->set_halign(Gtk::Align::START);
				labcomtprj->set_justify(Gtk::Justification::CENTER);
			comtprojet = Gtk::make_managed<Gtk::Label>();
				comtprojet->set_hexpand(true);
		zcomprojet->append(*labcomtprj);
		zcomprojet->append(*comtprojet);
	zprojet->append(*titprojet);
	zprojet->append(*zhprojet);		
	zprojet->append(*zcomprojet);
/*
 ************** 
 Zone liste Contexte
 ************** 
*/
	auto zctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titexictx = Gtk::make_managed<Gtk::Label>("Contextes existants de ce projet");
		titexictx->set_halign(Gtk::Align::CENTER);
		titexictx->set_hexpand();
		auto zhctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto zdatectx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
				auto labdatectx = Gtk::make_managed<Gtk::Label>("date création");
				labdatectx->set_halign(Gtk::Align::START);
				datectx = Gtk::make_managed<Gtk::Label>();
				datectx->set_justify(Gtk::Justification::RIGHT);
				zdatectx->append(*labdatectx);
				zdatectx->append(*datectx);
			auto factoryctx = Gtk::SignalListItemFactory::create();
				factoryctx->signal_setup().connect(sigc::mem_fun(*this, &CreerContexte::ConfigLibelle));
				factoryctx->signal_bind().connect(sigc::mem_fun(*this, &CreerContexte::AttacheNomContexte));
			selprojetctx = Gtk::SingleSelection::create(Clstcontexte);
				selprojetctx->set_autoselect(false);
				selprojetctx->set_can_unselect(true);
				selprojetctx->signal_selection_changed().connect(sigc::mem_fun(*this, &CreerContexte::ChangerContexte));
			ascenceurctx = Gtk::make_managed<Gtk::ScrolledWindow>();
				ascenceurctx->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
				ascenceurctx->set_hexpand();
			lstcontexte = Gtk::make_managed<Gtk::ListView>();
				lstcontexte->set_model(selprojetctx);
				lstcontexte->add_css_class("data-table");
			ascenceurctx->set_child(*lstcontexte);
			lstcontexte->set_factory(factoryctx);
		zhctx->append(*zdatectx);		
		zhctx->append(*ascenceurctx);		
		auto zcomctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto labcomtctx = Gtk::make_managed<Gtk::Label>("commentaire\nsur ce contexte");
				labcomtctx->set_wrap();
         		labcomtctx->set_hexpand(true);
				labcomtctx->set_halign(Gtk::Align::START);
				labcomtctx->set_justify(Gtk::Justification::CENTER);
			comtctx = Gtk::make_managed<Gtk::Label>();
				comtctx->set_hexpand(true);
		zcomctx->append(*labcomtctx);
		zcomctx->append(*comtctx);
	zctx->append(*titexictx);
	zctx->append(*zhctx);		
	zctx->append(*zcomctx);
	zctx->set_visible( Clstcontexte->get_n_items()!=0 );
/*
 ************** 
 Zone nouveau contexte
 ************** 
*/
	auto znctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titctxnouv = Gtk::make_managed<Gtk::Label>("Nouveau contexte");
			titctxnouv->set_halign(Gtk::Align::CENTER);
			titctxnouv->set_hexpand();
		auto znhhctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto znvhctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
				auto znhctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
					auto labctxnouv = Gtk::make_managed<Gtk::Label>("Nom du contexte");
					edinomctx = Gtk::make_managed<Gtk::Entry>();
					edinomctx->set_hexpand(true);
					edinomctx->set_text(nomtest);
				znhctx->append(*labctxnouv);
				znhctx->append(*edinomctx);
				auto zdatenct = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
					auto labdatenct = Gtk::make_managed<Gtk::Label>("date création");
					labdatenct->set_halign(Gtk::Align::START);
					datenctx = Gtk::make_managed<Gtk::Label>();
					datenctx->set_justify(Gtk::Justification::RIGHT);
					datenctx->set_text(libstr);
					boudate	= Gtk::make_managed<Gtk::Button>("modifier");
					boudate->set_hexpand(true);
					boudate->set_halign(Gtk::Align::END);
					boudate->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &CreerContexte::BoudateAppuye),0));
				zdatenct->append(*labdatenct);
				zdatenct->append(*datenctx);
				zdatenct->append(*boudate);
				auto labncomctx = Gtk::make_managed<Gtk::Label>("commentaire sur ce nouveau contexte");
					labncomctx->set_hexpand(true);
					labncomctx->set_halign(Gtk::Align::CENTER);
				edicomctx = Gtk::make_managed<Gtk::Entry>();
					edicomctx->set_text("...commentaire du nouveau contexte...");
					
				auto zconfig = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
					auto labnconfig = Gtk::make_managed<Gtk::Label>("Configuration : ");
						labnconfig->set_halign(Gtk::Align::START);

						chxconfig = Gtk::make_managed<Gtk::DropDown>();
							chxconfig->set_model(lstconfig);
							chxconfig->set_selected(0);
							chxconfig->set_hexpand(true);
//					edicomctx = Gtk::make_managed<Gtk::Entry>();
//						edicomctx->set_text("...commentaire du nouveau contexte...");
				zconfig->append(*labnconfig);
				zconfig->append(*chxconfig);
				
			znvhctx->append(*znhctx);
			znvhctx->append(*zdatenct);
			znvhctx->append(*labncomctx);
			znvhctx->append(*edicomctx);
			znvhctx->append(*zconfig);
			bouaccepte	= Gtk::make_managed<Gtk::Button>("Enregistrer");
			bouaccepte->set_valign(Gtk::Align::CENTER);
			bouaccepte->set_halign(Gtk::Align::CENTER);
		znhhctx->append(*znvhctx);
		znhhctx->append(*bouaccepte);	
			
	znctx->append(*titctxnouv);
	znctx->append(*znhhctx);
/*
 ************** 
 Zone Fin
 ************** 
*/
	auto zboutonfin = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zboutonfin->set_hexpand(true);
		auto bouannule	= Gtk::make_managed<Gtk::Button>("Sortir");
			bouannule->set_hexpand(true);
			bouannule->set_halign(Gtk::Align::CENTER);
			bouannule->signal_clicked().connect( sigc::mem_fun(*this, &CreerContexte::hide) );
	zboutonfin->append(*bouannule);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto sep02 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto sep03 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	
	auto ztotal = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
	ztotal->set_margin(20);
	ztotal->append(*zprojet);
	ztotal->append(*sep01);
	ztotal->append(*zctx);
	ztotal->append(*sep02);
	ztotal->append(*znctx);
	ztotal->append(*sep03);
	ztotal->append(*zboutonfin);
	set_child( *ztotal );
	if(listeprojet.TailleListe()>0)
	{
		uint32_t retval=0;
		if( listeprojet.Position( ptrprojet->Nom(), retval ) )
		{
			selprojet->set_selected ( retval );
		}
	}
	AfficherProjet();
	AfficherContexte();
	show();
}
CreerContexte::~CreerContexte()
{
	if(saisiedate!=nullptr)	delete saisiedate;
}
void CreerContexte::Collationner( EnrgContexte &rtvaleur, std::string &rtprojet )
{
	rtprojet = Clstprojet->get_string(selprojet->get_selected());	
	rtvaleur.nom = edinomctx->get_text();
	rtvaleur.commentaire = edicomctx->get_text();
	rtvaleur.dcreation.a = nrgdate->tm_year;
	rtvaleur.dcreation.m = nrgdate->tm_mon;
	rtvaleur.dcreation.j = nrgdate->tm_mday;
//	int titi = chxconfig->get_selected();
	rtvaleur.configuration = listeconfig.PtrChaine()->at( chxconfig->get_selected() );
}
void CreerContexte::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot)
{
	bouaccepte->signal_clicked().connect(sigc::bind(slot, 1));
	signal_hide().connect(sigc::bind(slot,9));
}
void CreerContexte::ChangerProjet( guint position, guint n_items)
{
	std::string resuphr = Clstprojet->get_string(selprojet->get_selected());
	if( listeprojet.Trouver( resuphr ))
	{
		if(ptrprojet->LireProjet(resuphr))
		{
			AfficherProjet();
			listecontexte.Vider();
			ptrprojet->ListerContexte(listecontexte);
			listecontexte.ListerVers(Clstcontexte);
			if(listecontexte.TailleListe()>0)
			{
				ptrprojet->LirePremierContexte();
				AfficherContexte();
			}
			else
				ViderAffichageContexte();

			selprojetctx->set_model(Clstcontexte);
		}
	}
}
void CreerContexte::ChangerContexte( guint position, guint n_items)
{
	std::string resuphr = Clstcontexte->get_string(selprojetctx->get_selected());
	if( listecontexte.Trouver( resuphr ))
	{
		if(ptrprojet->LireContexte(resuphr))
		{
			AfficherContexte();
		}
	}
}
void CreerContexte::AfficherProjet()
{
	libstr.resize(50);
	comtprojet->set_text(ptrprojet->LireCommentaire());
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", ptrprojet->LireDate());
	dateprojet->set_text(libstr);
}
void CreerContexte::ViderAffichageContexte()
{
	comtctx->set_text("... commentaire sur ce contexte ...");
	datectx->set_text(strdatejour);
}
void CreerContexte::AfficherContexte()
{
	libstr.resize(50);
	comtctx->set_text(ptrprojet->LireComContexte());
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", ptrprojet->LireDateContexte());
	datectx->set_text(libstr);
}
void CreerContexte::AttacheNomProjet(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstprojet->get_string(pos));
}
void CreerContexte::AttacheNomContexte(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstcontexte->get_string(pos));
}
void CreerContexte::ConfigLibelle(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}
/*
* Modifier la date
* envoi, retour et destruction de la boite
*/
void CreerContexte::BoudateAppuye( uint8_t valrt )
{
	if(valrt==0)
	{
		if(saisiedate!=nullptr) delete saisiedate;
		saisiedate = new DgDiaDate(nrgdate);
		saisiedate->ConnexionDate(sigc::mem_fun(*this, &CreerContexte::BoudateAppuye));
	}
	else
	{
		if(saisiedate!=nullptr)
		{
			if(valrt==1)
			{
				saisiedate->Resultat(nrgdate);
				strftime(libstr.data(), libstr.size(), "%d %OB %EY", nrgdate);
				datenctx->set_text(libstr);
			}
			delete saisiedate;
			saisiedate=nullptr;
		}
	}
}

