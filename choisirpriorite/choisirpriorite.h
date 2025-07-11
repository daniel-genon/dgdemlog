/*
 * ChoisirPriorite.h
*/

#ifndef CHOISIRPRIORITE_H
#define CHOISIRPRIORITE_H

#include <gtkmm.h>
#include "../../tmpbibl/dgchaineliste.h"

class ChoisirPriorite : public Gtk::Window
{
	public:
		ChoisirPriorite( DGChaineListe &listelabel );
		virtual ~ChoisirPriorite();
		
	void ConnexionRetour(const sigc::slot<void(unsigned char)> &slot);
	uint8_t Collationner();
	
protected:

	void Changepriorite();
	
private:
	Gtk::DropDown	*chxprio;
	Gtk::Button		*btoui,*btnon;
	Glib::RefPtr<Gtk::StringList> lstprio;
	
	uint8_t	valeurretour;
	
};
#endif /* CHOISIRPRIORITE_H */ 
