/*
 * Structure boite de dialogue : CreerContexte
*/
#ifndef CREERCONTEXTE_H
#define CREERCONTEXTE_H

#include <gtkmm.h>
#include "../../../bibliodg/entete/dgdiadate.h"
#include "../../../bibliodg/entete/dgbdial.h"
#include "../../source/structureappli.h"

#ifndef OKGTK
#define OKGTK
#endif /* OKGTK */

#include "../../bloc/fblocprojet.h"

class CreerContexte : public Gtk::Window
{
public:
	CreerContexte( FBlocProjet *pprojet, DGChaineListe *plisteconfig );
	virtual ~CreerContexte();
	
	void ConnexionRetour(const sigc::slot<void(unsigned char)> &slot);
	void Collationner( EnrgContexte &rtvaleur, std::string &rtprojet );
	
protected:

	Glib::RefPtr<Gtk::StringList> Clstprojet;	
	Glib::RefPtr<Gtk::StringList> Clstcontexte;	
	
	void BoudateAppuye( unsigned char valrt );
	void ConfigLibelle(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void AttacheNomProjet(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void AttacheNomContexte(const Glib::RefPtr<Gtk::ListItem>& list_item);
	
	
private:

	std::string	libstr, nomtest, strdatejour;
	struct tm	*nrgdate;
	DgDiaDate	*saisiedate;
	FBlocProjet	*ptrprojet;
	
//   EnrgSessionProjet	Enrtmp;
//    EnrgSessionProjet	*penrgretour;
    DGChaineListe listeprojet, listecontexte, listeconfig;
	
	Gtk::Entry	*ediprojet, *edicommet, *edidatepro, *edinomctx, *edicomctx;
	Gtk::Button	*bouaccepte, *boudate;
	Gtk::Label	*datenctx, *comtprojet, *comtctx, *dateprojet, *datectx;
	Gtk::DropDown *chxconfig;
	Glib::RefPtr<Gtk::SingleSelection> selprojet;
	Glib::RefPtr<Gtk::SingleSelection> selprojetctx;
	Gtk::ListView	*lstcontexte, *lstprojet;
	Gtk::ScrolledWindow	*ascenceur;
	Gtk::ScrolledWindow	*ascenceurctx;
	
	void ChangerProjet( guint position, guint n_items );
	void ChangerContexte( guint position, guint n_items );
	void AfficherProjet();
	void ViderAffichageContexte();
	void AfficherContexte();


};
#endif /* CREERCONTEXTE_H */ 
