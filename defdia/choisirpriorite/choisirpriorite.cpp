/*
 * ChoisirPriorite.cpp
 * 2023 daniel 
 */
#include <iostream>
#include "choisirpriorite.h"
ChoisirPriorite::ChoisirPriorite( DGChaineListe &listelabel )
{
	set_title("Choisir une priorité");
	set_default_size(260, 160);
	
	valeurretour = 1;
	
	listelabel.ListerVers( lstprio );

	auto ztotal	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );

	chxprio = Gtk::make_managed<Gtk::DropDown>();
		chxprio->set_model(lstprio);
		chxprio->set_selected(valeurretour);
		chxprio->set_size_request( 200, -1 );
		chxprio->property_selected().signal_changed().connect(sigc::mem_fun(*this, &ChoisirPriorite::Changepriorite));

	auto zsortie 	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zsortie->set_halign(Gtk::Align::END);
		zsortie->set_hexpand(true);
	btoui = Gtk::make_managed<Gtk::Button>( "Accepter" );
		btoui->set_halign(Gtk::Align::START);
	btnon = Gtk::make_managed<Gtk::Button>( "Annuler" );
		btnon->set_halign(Gtk::Align::END);
		btnon->signal_clicked().connect( sigc::mem_fun(*this, &ChoisirPriorite::hide) );
	zsortie->append(*btoui);
	zsortie->append(*btnon);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
		ztotal->set_margin(20);
		ztotal->append(*chxprio);
		ztotal->append(*sep01);
		ztotal->append(*zsortie);
	set_child( *ztotal );
	show();	
}
ChoisirPriorite::~ChoisirPriorite(){}
void ChoisirPriorite::Changepriorite()
{
	if( chxprio->get_selected()>0 )
		valeurretour = chxprio->get_selected();
	else
		chxprio->set_selected(valeurretour);
}
uint8_t ChoisirPriorite::Collationner(){ return valeurretour;}

void ChoisirPriorite::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot)
{
	btoui->signal_clicked().connect( sigc::bind( slot, 1 ));
	signal_hide().connect( sigc::bind( slot, 255 ) );
}
