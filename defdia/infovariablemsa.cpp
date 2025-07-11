#include "infovariablemsa.h"

InfoVariableMSA::InfoVariableMSA( ptrenrgvariableMSA pvaleur )
{
	set_title("variables de l'application");
	set_default_size(450, 150);
	
	auto zaffiche = Gtk::make_managed<Gtk::Grid>();
	zaffiche->set_margin(10);
		auto titre01 = Gtk::make_managed<Gtk::Label>("valeur");
			titre01->set_hexpand(true);
		titre01->set_margin(8);
			titre01->set_halign(Gtk::Align::START);
		auto titre02 = Gtk::make_managed<Gtk::Label>("code");
			titre02->set_hexpand(true);
		titre02->set_margin(8);
			titre02->set_halign(Gtk::Align::START);
		auto titre03 = Gtk::make_managed<Gtk::Label>("définition");
			titre03->set_hexpand(true);
		titre03->set_margin(8);
			titre03->set_halign(Gtk::Align::START);

		auto label01 = Gtk::make_managed<Gtk::Label>(pvaleur->Valeur());
			label01->set_hexpand(true);
		label01->set_margin(8);
			label01->set_halign(Gtk::Align::START);
		auto label02 = Gtk::make_managed<Gtk::Label>(pvaleur->Code_Abrege());
			label02->set_hexpand(true);
		label02->set_margin(8);
			label02->set_halign(Gtk::Align::START);
		auto label03 = Gtk::make_managed<Gtk::Label>(pvaleur->Definition());
			label03->set_halign(Gtk::Align::START);
		label03->set_margin(8);
			label03->set_hexpand(true);
	
	zaffiche->attach(*titre01, 0, 0);
	zaffiche->attach(*titre02, 0, 1);
	zaffiche->attach(*titre03, 0, 2);
	zaffiche->attach(*label01, 1, 0);
	zaffiche->attach(*label02, 1, 1);
	zaffiche->attach(*label03, 1, 2);
	
	auto bouannule	= Gtk::make_managed<Gtk::Button>("Sortir");
		bouannule->set_hexpand(true);
		bouannule->set_margin(10);
		bouannule->set_halign(Gtk::Align::CENTER);
		bouannule->signal_clicked().connect( sigc::mem_fun(*this, &InfoVariableMSA::hide) );
	auto ztotal = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
		ztotal->append(*zaffiche);
		ztotal->append(*bouannule);
	set_child(*ztotal);
	show();
}
InfoVariableMSA::~InfoVariableMSA(){}
void InfoVariableMSA::connexionInfo(const sigc::slot<void(uint8_t)> &slot)
{
	signal_hide().connect(sigc::bind(slot, 1));
}
