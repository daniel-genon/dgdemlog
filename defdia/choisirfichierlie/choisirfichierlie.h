/*
 * choisirfichierlie.h
*/

#ifndef CHOISIRFICHIERLIE_H
#define CHOISIRFICHIERLIE_H

#include <filesystem>
#include <gtkmm.h>
#include "../../bloc/tmp_chemin_bibliodg.h"
#include "../../source/logiciel.h"

class ChoisirFichierLie : public Gtk::Window
{
	public:
		ChoisirFichierLie( Logiciel *pvaleur, uint16_t vgenre, const std::string &chemincontexte );
		virtual ~ChoisirFichierLie();
		
	void ConnexionRetour(const sigc::slot<void(uint16_t)> &slot );
	std::string Collationner() const;
	bool OkCreation() const;
	
protected:
	void ChoisirFichier( uint8_t cas );
	
private:
	uint16_t	genre;
	uint8_t		index;
	bool		okcreation;
	std::size_t position;
	std::string nomcomplet, extension, nomprovisoire, phrtmp;//fichierxst, 
	Gtk::Box	*zlign03v, *zlign03, *zlign04v, *zlign04, *page01, *page02, *ztotal;
	Gtk::Label	*labnomxst;
	Gtk::Entry	*edinomfic, *edichmfic;
	Gtk::Button	*btoui01,*btoui02,*btnon01,*btnon02;
	Gtk::CheckButton	*copiestd, *copiexst, *choix02, *choix03;
	Gtk::FileChooserDialog *boitefichier;
	Logiciel *ptrlog;
	
	void ReponseFichier(  int reponse, uint8_t cas );
	void PageDeSortie();
	void CreerLeFichier();
	void ValeurIndex( uint8_t vindex);
	void ActiverZoneStd();
	void ActiverZoneXst();
};
#endif /* CHOISIRFICHIERLIE_H */ 
