/*
 * Structure boite de dialogue : ChargerContexte
*/
#ifndef CHARGERCONTEXTE_H
#define CHARGERCONTEXTE_H

#include <gtkmm.h>
#include "../../../bibliodg/entete/dgbdial.h"
#include "../../source/structureappli.h"

#ifndef OKGTK
#define OKGTK
#endif /* OKGTK */

#include "../../bloc/fblocprojet.h"

class ChargerContexte : public Gtk::Window
{
public:
	ChargerContexte( FBlocProjet *pprojet );
	virtual ~ChargerContexte();
	
	void ConnexionRetour(const sigc::slot<void(unsigned char)> &slot);
	void Collationner( std::string &rtprojet, std::string &rtcontexte );
	
protected:

	Glib::RefPtr<Gtk::StringList> Clstprojet;	
	Glib::RefPtr<Gtk::StringList> Clstcontexte;	
	
	void ConfigLibelle(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void AttacheNomProjet(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void AttacheNomContexte(const Glib::RefPtr<Gtk::ListItem>& list_item);
	
private:

	std::string	libstr, strdatejour;
//	struct tm	*nrgdate;
	FBlocProjet	*ptrprojet;
	
    DGChaineListe listeprojet, listecontexte;
	
	Gtk::Entry	*ediprojet, *edicommet, *edidatepro, *edinomctx, *edicomctx;
	Gtk::Label	*datectx, *comtprojet, *dateprojet, *comtctx;
	Glib::RefPtr<Gtk::SingleSelection> selprojet, selprojetctx;
	Gtk::Button *bouaccepte;
	Gtk::ScrolledWindow	*ascenceur;
	Gtk::ListView		*lstprojet;
	Gtk::ScrolledWindow	*ascenceurctx;
	Gtk::ListView		*lstcontexte;
	
	void ChangerProjet( guint position, guint n_items );
	void ChangerContexte( guint position, guint n_items );
	void AfficherProjet();
	void ViderAffichageContexte();
	void AfficherContexte();

};
#endif /* CHARGERCONTEXTE_H */ 
