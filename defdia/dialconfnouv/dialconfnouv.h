/*
 * DialConfNouv.h
*/

#ifndef DIALCONFNOUV_H
#define DIALCONFNOUV_H

#include <gtkmm.h>
#include "../../tmpbibl/dgchaineliste.h"

class DialogNouvelleConfig : public Gtk::Window
{
	public:
		DialogNouvelleConfig( DGChaineListe *lstconfexiste );
		virtual ~DialogNouvelleConfig();
		
	void ConnexionRetour(const sigc::slot<void(unsigned char)> &slot);
	uint8_t Collationner( std::string &retnomcfg, std::string &retnomcopie );
	
protected:
	
private:
	std::string		labnom1, labnom2;
	uint8_t			valeurretour;
	uint32_t		indsxt, indsxttmp;
	DGChaineListe	lstcfgexiste;
	Gtk::Label		*zlabelnom;
	Gtk::DropDown	*chxexiste;
	Gtk::Button		*btoui,*btnon;
	Gtk::Box		*zoneliste;
	Gtk::Entry		*editnom;
	Glib::RefPtr<Gtk::StringList> lstexiste;
	
	void ChangeConfiguration();
	void ValeurIndex( uint8_t valindex );
	void VerifierExistant();
};
#endif /* DIALCONFNOUV_H */ 
