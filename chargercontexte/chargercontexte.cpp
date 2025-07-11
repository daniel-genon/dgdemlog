/*
 * fenetre.cpp
 * 2023 daniel 
 */
#include <iostream>
#include "chargercontexte.h"

//ChargerContexte::ChargerContexte( DGChaineListe *pstprojet, EnrgSessionProjet *pvalenrg )
ChargerContexte::ChargerContexte( FBlocProjet *pprojet )
{
	ptrprojet	= pprojet;
	set_title("Charger un contexte");
	set_default_size(550, 500);
/*
		date du jour
*/
	strdatejour.resize(50);
	setlocale(LC_TIME, "fr_FR.UTF-8");
	time_t datedujour;
	time (&datedujour);
	struct tm *nrgdate = localtime (&datedujour);
	strftime(strdatejour.data(), strdatejour.size(), "%d %OB %EY", nrgdate);
/*	
		lister les projets existants
*/
	listeprojet.Vider();
	listecontexte.Vider();
	ptrprojet->Lister( listeprojet );
	listeprojet.ListerVers( Clstprojet );
	if(listeprojet.TailleListe()>0)
	{
		ptrprojet->LirePremierProjet();
		ptrprojet->ListerContexte(listecontexte);
		listecontexte.ListerVers(Clstcontexte);
		if(listecontexte.TailleListe()>0)
		{
			ptrprojet->LirePremierContexte();
		}
	}
/*
		Configuration boite
*/
	listeprojet.ListerVers( Clstprojet );
	listecontexte.ListerVers( Clstcontexte );
	auto zprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		zprojet->set_expand(true);
		auto titprojet = Gtk::make_managed<Gtk::Label>("Projets");
		titprojet->set_halign(Gtk::Align::CENTER);
		titprojet->set_hexpand();
		auto zhprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto factory = Gtk::SignalListItemFactory::create();
				factory->signal_setup().connect(sigc::mem_fun(*this, &ChargerContexte::ConfigLibelle));
				factory->signal_bind().connect(sigc::mem_fun(*this, &ChargerContexte::AttacheNomProjet));
			selprojet = Gtk::SingleSelection::create(Clstprojet);
				selprojet->set_autoselect(false);
				selprojet->set_can_unselect(true);
				selprojet->signal_selection_changed().connect(sigc::mem_fun(*this, &ChargerContexte::ChangerProjet));
			ascenceur = Gtk::make_managed<Gtk::ScrolledWindow>();
				ascenceur->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
				ascenceur->set_expand( true );
//				ascenceur->set_max_content_height( 7 );
//				ascenceur->set_min_content_height( 6 );
			lstprojet = Gtk::make_managed<Gtk::ListView>();
				lstprojet->set_model(selprojet);
				lstprojet->add_css_class("data-table");
			ascenceur->set_child(*lstprojet);
			lstprojet->set_factory(factory);
		zhprojet->append(*ascenceur);
		auto zdateprj = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto labdateprj = Gtk::make_managed<Gtk::Label>("date création");
			labdateprj->set_halign(Gtk::Align::START);
			dateprojet = Gtk::make_managed<Gtk::Label>(libstr);
			dateprojet->set_justify(Gtk::Justification::RIGHT);
			zdateprj->append(*labdateprj);
			zdateprj->append(*dateprojet);
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
	zprojet->append(*zdateprj);		
	zprojet->append(*zcomprojet);
	
	auto zctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
		auto titexictx = Gtk::make_managed<Gtk::Label>("Contextes de ce projet");
		titexictx->set_halign(Gtk::Align::CENTER);
		titexictx->set_hexpand();
		auto zhctx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto factoryctx = Gtk::SignalListItemFactory::create();
				factoryctx->signal_setup().connect(sigc::mem_fun(*this, &ChargerContexte::ConfigLibelle));
				factoryctx->signal_bind().connect(sigc::mem_fun(*this, &ChargerContexte::AttacheNomContexte));
			selprojetctx = Gtk::SingleSelection::create(Clstcontexte);
				selprojetctx->set_autoselect(false);
				selprojetctx->set_can_unselect(true);
				selprojetctx->signal_selection_changed().connect(sigc::mem_fun(*this, &ChargerContexte::ChangerContexte));
			ascenceurctx = Gtk::make_managed<Gtk::ScrolledWindow>();
				ascenceurctx->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
				ascenceurctx->set_expand(true);
//				ascenceurctx->set_max_content_height( 7 );
//				ascenceurctx->set_min_content_height( 6 );
			lstcontexte = Gtk::make_managed<Gtk::ListView>();
				lstcontexte->set_model(selprojetctx);
				lstcontexte->add_css_class("data-table");
			ascenceurctx->set_child(*lstcontexte);
			lstcontexte->set_factory(factoryctx);
		zhctx->append(*ascenceurctx);		
		auto zdatectx = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 10 );
			auto labdatectx = Gtk::make_managed<Gtk::Label>("date création");
			labdatectx->set_halign(Gtk::Align::START);
			datectx = Gtk::make_managed<Gtk::Label>(libstr);
			datectx->set_justify(Gtk::Justification::RIGHT);
			zdatectx->append(*labdatectx);
			zdatectx->append(*datectx);
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
	zctx->append(*zdatectx);		
	zctx->append(*zcomctx);
	
	auto zboutonfin = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zboutonfin->set_hexpand(true);
		auto bouannule	= Gtk::make_managed<Gtk::Button>("Sortir");
			bouannule->set_hexpand(true);
			bouannule->set_halign(Gtk::Align::END);
			bouannule->signal_clicked().connect( sigc::mem_fun(*this, &ChargerContexte::hide) );
			
		bouaccepte	= Gtk::make_managed<Gtk::Button>("Charger");
			bouaccepte->set_hexpand(true);
			bouaccepte->set_halign(Gtk::Align::START);
	zboutonfin->append(*bouannule);
	zboutonfin->append(*bouaccepte);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto sep02 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	
	auto ztotal = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
	ztotal->set_margin(20);
	ztotal->append(*zprojet);
	ztotal->append(*sep01);
	ztotal->append(*zctx);
	ztotal->append(*sep02);
	ztotal->append(*zboutonfin);
	set_child( *ztotal );
	
	AfficherProjet();
	AfficherContexte();
	
	show();
}
ChargerContexte::~ChargerContexte()
{
}
void ChargerContexte::Collationner( std::string &rtprojet, std::string &rtcontexte )
{
	rtprojet	= Clstprojet->get_string(selprojet->get_selected());
	rtcontexte	= Clstcontexte->get_string(selprojetctx->get_selected());
}
void ChargerContexte::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot)
{
	bouaccepte->signal_clicked().connect(sigc::bind(slot, 1));
	signal_hide().connect(sigc::bind(slot,9));
}
void ChargerContexte::ChangerProjet( guint position, guint n_items)
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
void ChargerContexte::ChangerContexte( guint position, guint n_items)
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
void ChargerContexte::AfficherProjet()
{
	libstr.resize(50);
	comtprojet->set_text(ptrprojet->LireCommentaire());
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", ptrprojet->LireDate());
	dateprojet->set_text(libstr);
}
void ChargerContexte::ViderAffichageContexte()
{
	comtctx->set_text("... commentaire sur ce contexte ...");
	datectx->set_text(strdatejour);
}
void ChargerContexte::AfficherContexte()
{
	libstr.resize(50);
	comtctx->set_text(ptrprojet->LireComContexte());
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", ptrprojet->LireDateContexte());
	datectx->set_text(libstr);
}

void ChargerContexte::AttacheNomProjet(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstprojet->get_string(pos));
}
void ChargerContexte::AttacheNomContexte(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Clstcontexte->get_string(pos));
}
void ChargerContexte::ConfigLibelle(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}
