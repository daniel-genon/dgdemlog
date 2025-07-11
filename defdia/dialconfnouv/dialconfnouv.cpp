/*
 * dialconfnouv.cpp
 * 2025 daniel 
 */
//#include <iostream>
#include "dialconfnouv.h"
DialogNouvelleConfig::DialogNouvelleConfig( DGChaineListe *lstconfexiste )
{
	set_title("Créer une nouvelle configuration");
	set_default_size(360, 200);
	*lstcfgexiste.PtrChaine() = *lstconfexiste->PtrChaine();
	lstcfgexiste.ListerVers( lstexiste );
	valeurretour = 1;
	labnom1 = "Nom de la nouvelle configuration";
	labnom2 = "***Cette configuration existe déjà***";
	indsxt = 0;
	indsxttmp = indsxt;
	
	auto ztotal	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
	
	zlabelnom = Gtk::make_managed<Gtk::Label>(labnom1);
	editnom = Gtk::make_managed<Gtk::Entry>();
	editnom->signal_changed().connect(sigc::mem_fun(*this, &DialogNouvelleConfig::VerifierExistant));
	
	auto zoneboite = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		auto zonechoix = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
		
			auto btnrad01 = Gtk::make_managed<Gtk::CheckButton>( "vide" );
				btnrad01->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &DialogNouvelleConfig::ValeurIndex),0 ));
				zonechoix->append(*btnrad01);
			auto btnrad02 = Gtk::make_managed<Gtk::CheckButton>( "standard" );
				btnrad02->set_group( *btnrad01 );
				btnrad02->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &DialogNouvelleConfig::ValeurIndex),1 ));
				zonechoix->append(*btnrad02);
			auto btnrad03 = Gtk::make_managed<Gtk::CheckButton>( "copie configuration actuelle" );
				btnrad03->set_group( *btnrad01 );
				btnrad03->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &DialogNouvelleConfig::ValeurIndex),2 ));
				zonechoix->append(*btnrad03);
			auto btnrad04 = Gtk::make_managed<Gtk::CheckButton>( "copie configuration existante" );
				btnrad04->set_group( *btnrad01 );
				btnrad04->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &DialogNouvelleConfig::ValeurIndex),3 ));
				zonechoix->append(*btnrad04);

		zoneliste = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
		
		auto labexiste = Gtk::make_managed<Gtk::Label>("Configurations existantes");
		chxexiste = Gtk::make_managed<Gtk::DropDown>();
			chxexiste->set_model(lstexiste);
			chxexiste->set_selected(indsxt);
			chxexiste->set_size_request( 200, -1 );
			chxexiste->property_selected().signal_changed().connect(sigc::mem_fun(*this, &DialogNouvelleConfig::ChangeConfiguration));
		zoneliste->append(*labexiste);
		zoneliste->append(*chxexiste);

	zoneboite->append(*zonechoix);
	zoneboite->append(*zoneliste);
	auto zsortie 	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zsortie->set_halign(Gtk::Align::CENTER);
		zsortie->set_hexpand(true);
		
	btoui = Gtk::make_managed<Gtk::Button>( "Accepter" );
	btnon = Gtk::make_managed<Gtk::Button>( "Annuler" );
		btnon->signal_clicked().connect( sigc::mem_fun(*this, &DialogNouvelleConfig::hide) );
	zsortie->append(*btoui);
	zsortie->append(*btnon);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto sep02 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
		ztotal->set_margin(20);
		ztotal->append(*zlabelnom);
		ztotal->append(*editnom);
		ztotal->append(*sep01);
		ztotal->append(*zoneboite);
		ztotal->append(*sep02);
		ztotal->append(*zsortie);
	set_child( *ztotal );
	btnrad02->set_active(true);
	show();	
}
DialogNouvelleConfig::~DialogNouvelleConfig(){}
void DialogNouvelleConfig::ChangeConfiguration()
{
	indsxt = chxexiste->get_selected();
}
void DialogNouvelleConfig::VerifierExistant()
{
	if(lstcfgexiste.Position( editnom->get_text(), indsxttmp ))
	{
		indsxt = chxexiste->get_selected();
		zoneliste->set_visible( true );
		chxexiste->set_selected(indsxttmp);
		zlabelnom->set_text( labnom2 );
		btoui->set_visible( false );
		indsxttmp = 9999;
	}
	else
	{
		if( indsxttmp == 9999 )
		{
			indsxttmp = indsxt;
			zoneliste->set_visible( false );
			chxexiste->set_selected(indsxt);
			zlabelnom->set_text( labnom1 );
			btoui->set_visible( true );
		}
	}
}
uint8_t DialogNouvelleConfig::Collationner( std::string &retnomcfg, std::string &retnomcopie )
{
	retnomcfg = editnom->get_text();
	if( retnomcfg.empty() ) return 255;
	if(valeurretour==3)
		retnomcopie = lstcfgexiste.PtrChaine()->at( indsxt );
	return valeurretour;
}
void DialogNouvelleConfig::ValeurIndex( uint8_t valindex )
{
	valeurretour = valindex; 
	zoneliste->set_visible( valindex==3 );
}

void DialogNouvelleConfig::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot)
{
	btoui->signal_clicked().connect( sigc::bind( slot, 1 ));
	signal_hide().connect( sigc::bind( slot, 255 ) );
}
