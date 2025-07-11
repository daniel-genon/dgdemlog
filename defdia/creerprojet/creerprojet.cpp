/*
 * fenetre.cpp
 * 2023 daniel 
 */
#include <iostream>
#include "creerprojet.h"

//CreerProjet::CreerProjet( DGChaineListe *pstprojet, EnrgSessionProjet *pvalenrg )
CreerProjet::CreerProjet( DGChaineListe *pstprojet)
{
    //penrgretour = pvalenrg;
    //Enrtmp      = *pvalenrg;
    plstprojetexistant = pstprojet;
	saisiedate	= nullptr;
	
	set_title("Créer un projet");
	set_default_size(450, 200);
	
/*
		creer nom par defaut
*/
    std::string nomtest = ("nouveauprojet");
    int increment=0;
    while(plstprojetexistant->Trouver(nomtest))
		nomtest = "nouveauprojet" + std::to_string(increment++);
/*
		date du jour
*/
	libstr.resize(50);
	setlocale(LC_TIME, "fr_FR.UTF-8");
	time_t datedujour;
	time (&datedujour);
	nrgdate = localtime (&datedujour);
	strftime(libstr.data(), libstr.size(), "%d %OB %EY", nrgdate);
/*
		Configuration boite
*/
	auto zprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		auto zentreeprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 2 );
			auto labprojet = Gtk::make_managed<Gtk::Label>("nom du projet");
				labprojet->set_halign(Gtk::Align::CENTER);
			ediprojet = Gtk::make_managed<Gtk::Entry>();
				ediprojet->set_text(nomtest);
				ediprojet->set_hexpand(true);
				
		zentreeprojet->append(*labprojet);
		zentreeprojet->append(*ediprojet);
		auto zdateprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 2 );
			auto labdate = Gtk::make_managed<Gtk::Label>("date du projet");
				labdate->set_halign(Gtk::Align::CENTER);
				
			auto zlibprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
				edidatepro = Gtk::make_managed<Gtk::Entry>();
					edidatepro->set_text(libstr);
					edidatepro->set_hexpand(false);
					edidatepro->set_halign(Gtk::Align::START);
				auto boudate	= Gtk::make_managed<Gtk::Button>("Modifier");
					boudate->set_hexpand(false);
					boudate->set_halign(Gtk::Align::END);
					boudate->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &CreerProjet::BoudateAppuye),0));
			zlibprojet->append(*edidatepro);
			zlibprojet->append(*boudate);
		zdateprojet->append(*labdate);
		zdateprojet->append(*zlibprojet);
	zprojet->append(*zentreeprojet);
	zprojet->append(*zdateprojet);
	
	auto zcommentprojet = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 2 );
		auto labcommet = Gtk::make_managed<Gtk::Label>("commentaires sur ce projet");
			labcommet->set_halign(Gtk::Align::CENTER);
		edicommet = Gtk::make_managed<Gtk::Entry>();
			edicommet->set_text("conteneur de contextes de démarrage.");
			edicommet->set_hexpand(true);
	zcommentprojet->append(*labcommet);
	zcommentprojet->append(*edicommet);
	
	auto zboutonfin = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
	zboutonfin->set_hexpand(true);
		bouaccepte	= Gtk::make_managed<Gtk::Button>("Accepter");
			bouaccepte->set_hexpand(false);
			bouaccepte->set_halign(Gtk::Align::START);
		auto bouannule	= Gtk::make_managed<Gtk::Button>("Annuler");
			bouannule->set_hexpand(true);
			bouannule->set_halign(Gtk::Align::END);
			bouannule->signal_clicked().connect( sigc::mem_fun(*this, &CreerProjet::hide) );
	zboutonfin->append(*bouaccepte);
	zboutonfin->append(*bouannule);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto ztotal = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 10 );
	ztotal->set_margin(20);
	ztotal->append(*zprojet);
	ztotal->append(*zcommentprojet);
	ztotal->append(*sep01);
	ztotal->append(*zboutonfin);
	set_child( *ztotal );
	set_visible();
}
CreerProjet::~CreerProjet()
{
	if(saisiedate!=nullptr)	delete saisiedate;
}

void CreerProjet::Collationner( EnrgProjet &rtvaleur )
{
	rtvaleur.nom = ediprojet->get_text();
	rtvaleur.commentaire = edicommet->get_text();
	rtvaleur.dcreation.a = nrgdate->tm_year;
	rtvaleur.dcreation.m = nrgdate->tm_mon;
	rtvaleur.dcreation.j = nrgdate->tm_mday;
}
void CreerProjet::ConnexionRetour(const sigc::slot<void(uint8_t)> &slot)
{
	bouaccepte->signal_clicked().connect(sigc::bind(slot, 1));
	signal_hide().connect(sigc::bind(slot,9));
}
/*
* Modifier la date
* envoi, retour et destruction de la boite
*/
void CreerProjet::BoudateAppuye( uint8_t valrt )
{
	if(valrt==0)
	{
		if(saisiedate!=nullptr) delete saisiedate;
		saisiedate = new DgDiaDate(nrgdate);
		saisiedate->ConnexionDate(sigc::mem_fun(*this, &CreerProjet::BoudateAppuye));
	}
	else
	{
		if(saisiedate!=nullptr)
		{
			if(valrt==1)
			{
				saisiedate->Resultat(nrgdate);
				strftime(libstr.data(), libstr.size(), "%d %OB %EY", nrgdate);
				edidatepro->set_text(libstr);
			}
			delete saisiedate;
			saisiedate=nullptr;
		}
	}
}

