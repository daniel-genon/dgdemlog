/*
 * ChoisirPriorite.cpp
 * 2023 daniel 
 */
#include <fstream>
#include "choisirfichierlie.h"
ChoisirFichierLie::ChoisirFichierLie( Logiciel *pvaleur, uint16_t vgenre, const std::string &chemincontexte )
{
	switch(vgenre)
	{
		case 200 : set_title("Choisir un fichier de travail");break;
		case 300 : set_title("Choisir un fichier de configuration");break;
		default : set_title("Choisir un fichier"); 
	}
	
	set_default_size(710,220);
	
	boitefichier	= nullptr;
	ptrlog			=  pvaleur;
	okcreation		= false;
//	fichierxst		= ("... choisir un fichier ...");
	extension		= "nop";
	genre			= vgenre;
	nomprovisoire	= "nouveaufichier.";
	
	std::string chmctx( chemincontexte );
	chmctx.pop_back();
	
	position = chmctx.find_last_of("/\\");
	if( position!=std::string::npos )
		nomprovisoire = chmctx.substr(position+1)+".";
		
	if( ptrlog->ALeFichierLie(genre) )
	{
		phrtmp = ptrlog->NomStdLie(genre);
		position = phrtmp.find_last_of("/\\");
		if( position!=std::string::npos )
		{
			phrtmp = phrtmp.substr(position+1);
			position = phrtmp.find_last_of(".");
			if( position!=std::string::npos )
			{
				extension = phrtmp.substr(position+1);
			}
		}
	}
	nomprovisoire += extension;
	
	ztotal	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
	page01	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
		auto zlign01 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		auto labchmfic = Gtk::make_managed<Gtk::Label>("chemin");
			labchmfic->set_margin(8);
			labchmfic->set_halign(Gtk::Align::START);
		edichmfic = Gtk::make_managed<Gtk::Entry>();
		edichmfic->set_text(chmctx);
			edichmfic->set_hexpand(true);
		auto btnchxchm = Gtk::make_managed<Gtk::Button>("...");
			btnchxchm->set_expand(false);
			btnchxchm->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ChoisirFichierLie::ChoisirFichier),2));
		zlign01->append(*labchmfic);
		zlign01->append(*edichmfic);
		zlign01->append(*btnchxchm);

		auto zlign02 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		auto labnomfic = Gtk::make_managed<Gtk::Label>("nom du fichier");
			labnomfic->set_margin(8);
			labnomfic->set_halign(Gtk::Align::START);
			edinomfic = Gtk::make_managed<Gtk::Entry>();
			edinomfic->set_text(nomprovisoire);
			edinomfic->set_hexpand(true);
		auto btnchxnom = Gtk::make_managed<Gtk::Button>("...");
			btnchxnom->set_expand(false);
			btnchxnom->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ChoisirFichierLie::ChoisirFichier),1));
		zlign02->append(*labnomfic);
		zlign02->append(*edinomfic);
		zlign02->append(*btnchxnom);
		
		zlign03 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			zlign03->set_margin_top(10);
			zlign03->set_margin_bottom(10);
		copiestd = Gtk::make_managed<Gtk::CheckButton>("copie depuis le fichier standard");
		copiestd->signal_toggled().connect( sigc::mem_fun(*this, &ChoisirFichierLie::ActiverZoneStd) );
		copiestd->set_visible( ptrlog->ALeFichierLie(genre) );
		zlign03v = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		auto labnomstd = Gtk::make_managed<Gtk::Label>();
			labnomstd->set_margin(8);
			labnomstd->set_hexpand(true);
		if(	ptrlog->ALeFichierLie(genre) )
			labnomstd->set_text(ptrlog->NomStdLie(genre));
		zlign03v->append(*labnomstd);
		zlign03->append(*copiestd);
		zlign03->append(*zlign03v);
		
		zlign04 = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
			zlign04->set_margin_top(10);
			zlign04->set_margin_bottom(10);
		copiexst = Gtk::make_managed<Gtk::CheckButton>("copie depuis un fichier existant");
		copiexst->signal_toggled().connect( sigc::mem_fun(*this, &ChoisirFichierLie::ActiverZoneXst) );
		zlign04v = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 5 );
		labnomxst = Gtk::make_managed<Gtk::Label>("choisir un fichier -->");
			labnomxst->set_wrap(GTK_WRAP_WORD);
			labnomxst->set_justify(Gtk::Justification::RIGHT);
			labnomxst->set_margin(8);
			labnomxst->set_hexpand(true);
			labnomxst->set_halign(Gtk::Align::END);
		auto btnchxxst = Gtk::make_managed<Gtk::Button>("...");
			btnchxxst->set_expand(false);
			btnchxxst->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ChoisirFichierLie::ChoisirFichier),3));
		auto btnfacxst = Gtk::make_managed<Gtk::Button>("X");
			btnfacxst->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ChoisirFichierLie::ReponseFichier),Gtk::ResponseType::ACCEPT,4));
		zlign04v->append(*labnomxst);
		zlign04v->append(*btnchxxst);
		zlign04v->append(*btnfacxst);
		zlign04->append(*copiexst);
		zlign04->append(*zlign04v);
		
	auto zsortie 	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zsortie->set_halign(Gtk::Align::CENTER);
		zsortie->set_expand(true);
		
	btoui01 = Gtk::make_managed<Gtk::Button>( "Accepter" );
		btoui01->set_valign(Gtk::Align::END);
		btoui01->signal_clicked().connect( sigc::mem_fun(*this, &ChoisirFichierLie::PageDeSortie) );
	btnon01 = Gtk::make_managed<Gtk::Button>( "Annuler" );
		btnon01->set_valign(Gtk::Align::END);
		btnon01->signal_clicked().connect( sigc::mem_fun(*this, &ChoisirFichierLie::hide) );
	zsortie->append(*btoui01);
	zsortie->append(*btnon01);
	
	auto sep01 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	auto sep02 = Gtk::make_managed<Gtk::Separator>( Gtk::Orientation::HORIZONTAL );
	
		page01->set_margin(20);
		page01->append(*zlign01);
		page01->append(*zlign02);
		page01->append(*sep01);
		page01->append(*zlign03);
		page01->append(*zlign04);
		page01->append(*sep02);
		page01->append(*zsortie);
		
	ActiverZoneXst();
	ActiverZoneStd();
		
	page02	= Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 5 );
		auto labficexiste = Gtk::make_managed<Gtk::Label>("Le fichier à lier existe déjà dans le dossier.");
		auto choix01 = Gtk::make_managed<Gtk::CheckButton>("Lier le fichier existant.");
		choix02 = Gtk::make_managed<Gtk::CheckButton>("Remplacer par la copie.");
		choix03 = Gtk::make_managed<Gtk::CheckButton>("Remplacer par le fichier standard.");
		auto choix04 = Gtk::make_managed<Gtk::CheckButton>("Remplacer par un fichier vide.");
		choix01->set_active(true);
		choix02->set_group( *choix01 );
		choix03->set_group( *choix01 );
		choix04->set_group( *choix01 );
		choix01->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &ChoisirFichierLie::ValeurIndex),1 ));
		choix02->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &ChoisirFichierLie::ValeurIndex),2 ));
		choix03->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &ChoisirFichierLie::ValeurIndex),3 ));
		choix04->signal_toggled().connect(sigc::bind( sigc::mem_fun(*this, &ChoisirFichierLie::ValeurIndex),4 ));
		btoui02 = Gtk::make_managed<Gtk::Button>( "Accepter" );
//			btoui02->set_halign(Gtk::Align::CENTER);
			btoui02->set_valign(Gtk::Align::END);
			btoui02->set_hexpand(false);
			btoui02->signal_clicked().connect( sigc::mem_fun(*this, &ChoisirFichierLie::CreerLeFichier) );
			btnon02 = Gtk::make_managed<Gtk::Button>( "Annuler" );
			btnon02->set_valign(Gtk::Align::END);
			btnon02->signal_clicked().connect( sigc::mem_fun(*this, &ChoisirFichierLie::hide) );
	page02->append(*labficexiste);
	page02->append(*choix01);
	page02->append(*choix02);
	page02->append(*choix03);
	page02->append(*choix04);
	page02->append(*btoui02);
	page02->set_visible(false);
	
	ztotal->append(*page01);
	ztotal->append(*page02);

	set_child( *ztotal );
	show();
//	set_focus(*edinomfic);
}
ChoisirFichierLie::~ChoisirFichierLie()
{
	if (boitefichier!=nullptr) delete boitefichier;
}
std::string ChoisirFichierLie::Collationner() const
{
	return nomcomplet;
}
bool ChoisirFichierLie::OkCreation() const { return okcreation; }
void ChoisirFichierLie::ChoisirFichier( uint8_t cas )
{
	if (boitefichier!=nullptr) delete boitefichier;
	boitefichier = new Gtk::FileChooserDialog(*this, "Choisir le nom du fichier", Gtk::FileChooser::Action::OPEN );
		boitefichier->set_modal(true);
	switch (cas)
	{
		case 1 :{// nom du fichier 
				auto filter_text = Gtk::FileFilter::create();
				filter_text->add_suffix("*.*");
				boitefichier->set_filter(filter_text);
				}break;
		case 2 :// chemin du fichier
				boitefichier->set_action(Gtk::FileChooser::Action::SELECT_FOLDER);
				boitefichier->set_title("Choisir le dossier du fichier");
				break;
		case 3 :// nom+chemin du fichier existant à copier
				boitefichier->set_title("Choisir le fichier existant à copier");
				break;
	}
	boitefichier->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &ChoisirFichierLie::ReponseFichier), cas));
		boitefichier->add_button("Annuler", Gtk::ResponseType::CANCEL);
		boitefichier->add_button("Accepter", Gtk::ResponseType::ACCEPT);
	boitefichier->show();
}
void ChoisirFichierLie::ReponseFichier( int reponse, uint8_t cas )
{
	if(boitefichier!=nullptr)
	{
		if(reponse==Gtk::ResponseType::ACCEPT)
		{
			switch(cas)
			{
				case 1 : // nom du fichier 
					{
						Glib::ustring *nomfic = new Glib::ustring(boitefichier->get_file()->get_basename());
						Glib::ustring *nomchm = new Glib::ustring(boitefichier->get_file()->get_path());
						nomchm->resize(nomchm->size()-(nomfic->size()+1));
							edinomfic->set_text(*nomfic);
							edichmfic->set_text(*nomchm);
							delete nomfic;
							delete nomchm;
					}break;
				case 2 : // chemin du fichier
					edichmfic->set_text(boitefichier->get_file()->get_path());
					break;
				case 3 :// nom+chemin du fichier existant à copier
					labnomxst->set_text(boitefichier->get_file()->get_path());
					break;
			}
		}
		delete boitefichier;
		boitefichier = nullptr;
	}
}
void ChoisirFichierLie::ActiverZoneStd()
{
	zlign04->set_visible(!copiestd->get_active());
	zlign03v->set_visible(copiestd->get_active());
}
void ChoisirFichierLie::ActiverZoneXst()
{
	zlign04v->set_visible(copiexst->get_active());
	zlign03->set_visible(!copiexst->get_active());
}
void ChoisirFichierLie::ConnexionRetour(const sigc::slot<void(uint16_t)> &slot )
{
//	btoui02->signal_clicked().connect( sigc::bind( slot, genre ));
	signal_hide().connect( sigc::bind( slot, genre ) );
}
void ChoisirFichierLie::ValeurIndex( uint8_t vindex ){	index = vindex; }
void ChoisirFichierLie::PageDeSortie()
{
	nomcomplet = edichmfic->get_text()+"/"+edinomfic->get_text();
	index = 0;
	if( std::filesystem::exists (nomcomplet ) )
	{
		page01->set_visible(false);
		page02->set_visible(true);
		choix02->set_visible(copiexst->get_active());
		choix03->set_visible(copiestd->get_active());
	}
	else
		CreerLeFichier();
}
void ChoisirFichierLie::CreerLeFichier()
{
	bool oknouveau = true;
	if(index!=0)
	{
		copiestd->set_active(false);
		copiexst->set_active(false);
		switch(index)
		{
			case 1 : oknouveau = false; break;//utiliser le fichier existant.
			case 2 : copiexst->set_active(true); break;//Remplacer par la copie.
			case 3 : copiestd->set_active(true); break;//Remplacer par le fichier standard.
			//remplacer par n fichier vide;
		}
		//if(oknouveau)
			//std::filesystem::remove ( nomcomplet );
	}
	if(oknouveau)
	{
		bool okcreer = true;
		const auto options = std::filesystem::copy_options::overwrite_existing;
		if(!copiestd->get_active())
		{
			if(copiexst->get_active())
			{
				if( std::filesystem::exists( labnomxst->get_text().release() ) )
					okcreer = std::filesystem::copy_file( labnomxst->get_text().release(), nomcomplet, options );
				else
					okcreer = false;
			}
			else
				okcreer = false;
		}
		else
			okcreer = std::filesystem::copy_file( ptrlog->NomStdLie(genre), nomcomplet, options );
		
		if(!okcreer)
		{
			std::fstream fichervide(nomcomplet.data(), std::fstream::out);
			fichervide.close();
		}
	}
	okcreation = true;
	hide();
}
