/*
 * Structure boite de dialogue : CreerProjet
*/
#ifndef CREERPROJET_H
#define CREERPROJET_H
#include <gtkmm.h>
#include "../../../bibliodg/entete/dgdiadate.h"
#include "../../../bibliodg/entete/dgbdial.h"
#include "../../source/structureappli.h"

class CreerProjet : public Gtk::Window
{
public:
//	CreerProjet( DGChaineListe *pstprojet, EnrgSessionProjet *pvalenrg );
	CreerProjet( DGChaineListe *pstprojet );
	virtual ~CreerProjet();
	void ConnexionRetour(const sigc::slot<void(unsigned char)> &slot);
	void Collationner( EnrgProjet &rtvaleur );
	
protected:
	void BoudateAppuye( unsigned char valrt );

private:
	struct tm		*nrgdate;
	std::string		libstr;
	DgDiaDate		*saisiedate;
	
    //EnrgSessionProjet	Enrtmp;
    //EnrgSessionProjet	*penrgretour;
    DGChaineListe		*plstprojetexistant;
	
	Gtk::Entry	*ediprojet, *edicommet, *edidatepro;
	Gtk::Button	*bouaccepte;

};
#endif /* CREERPROJET_H */ 
