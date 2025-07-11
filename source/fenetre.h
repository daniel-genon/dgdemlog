/*
 * fenetre.h
*/

#ifndef FENETRE_H
#define FENETRE_H

#include <gtkmm.h>
#include "../bloc/tmp_chemin_bibliodg.h"
#include "zonegraphique.h"
#include "gerersession.h"
#include "configurationobjet.h"
#include "demarreobjet.h"
#include "fichierlie.h"
#include "../defdia/chargercontexte/chargercontexte.h"
#include "../defdia/choisirpriorite/choisirpriorite.h"
#include "../defdia/choisirfichierlie/choisirfichierlie.h"
#include "../defdia/messagemsa.h"


class Fenetre;
typedef void (Fenetre::*PtrFnct)(void);
typedef void (Fenetre::*PtrFnctFenRet)( uint8_t );

class Fenetre : public Gtk::Window
{
	public:
		Fenetre();
		virtual ~Fenetre();
	
protected:
	Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;

// SLOT APPLICATION
	
	void LancerContexteEnCours();
    void StopperTout();
    void AProposDe();
    void ChoixDuContexte();
    void NouveauProjet();
    void NouveauContexte();
    void Sauvegarder();
    void SupprimerObjet();
    void SupprimerTout();
    void Configuration();
    void CreerUneConfiguration();
    void Quitter();
	void FermerAppliContexte();
	void ModifierPriorite();
	void LierDesObjets();
	void FichiersLies( uint8_t cas );

    void AjouterLogiciel( uint16_t cas );

	void QuestionOuiNon(const Glib::ustring& libmess,const Glib::ustring& libques);
	void MessageInfo( const Glib::ustring &libmess );
	void QuestionChoix( const Glib::ustring& libmess, const uint8_t &rtbtn );
	void SaisirValeur(const Glib::ustring& liblibel, const uint8_t &typezone );
	virtual void close();
	
private:
	
    bool			passortir;
    bool			okdemarrer;
    Logiciel		*ptrlogTMP;
    Connexion		*ptrconTMP;
    FichierLie  	*ptrficlie;
	ptrenrglogiciel ptmplogiciel;
	ptrconnexion	ptmpconnexion;
	Ancrage			*psymboleancre;
    std::string		phrtmp1, phrtmp2;
    PtrFnct			pFncVoid, pFncAppeloui, pFncAppelnon;
    PtrFnctFenRet	pFncRetourValeur;
    
   	std::vector<GraphiqueSurface*> lstobjettmp;

    
   	Gtk::Grid	*zonegauche;
	Gtk::Label	*zonetitre;
    std::list<Gtk::Button*> lstbtnlogiciel;
    Glib::RefPtr<Gio::InputStream> fichierdonnees;
	Glib::RefPtr<Gio::DataInputStream> lignedonnee;
	
	std::tuple< Gtk::Image*, Glib::RefPtr<Gdk::Pixbuf>, Glib::RefPtr<Gdk::Pixbuf> > valimgbtnalt;
	std::vector<std::tuple< Gtk::Image*, Glib::RefPtr<Gdk::Pixbuf>, Glib::RefPtr<Gdk::Pixbuf> >> lstobjimage;

	Gtk::Button *ptrboutontmp;// variable générale tmp
	Gtk::Image	*ptrimagetmp;// variable générale tmp
	Glib::RefPtr<Gdk::Pixbuf> ptrimgpixbuftmp, ptrimgaltpixbuftmp;
	
	std::vector< std::string > *plstchoixdialogue;
//	void reponse_choix_contexte( uint8_t vrt );
//	void Reponse_Entree( uint8_t vrt );
	void reponse_choix_demarrer( uint8_t vchoix );
	void ViderListeChoix();
	void PasDeChoix();
    
    MessageMSA			*bdialogue;
    MessageMSA			*messagemsa;
    ChargerContexte		*dlgcharcontexte;
	ChoisirPriorite		*dlgchoixprio;
	ChoisirFichierLie	*dlgchoixFichierLie;	
    ZoneGraphique		*pscene;
	GererSession		session;
	ConfigurationObjet  CfgMTStartApp;// ancien cfgdemarreMAO
	DemarreObjet        demarreur;

//	void RechargerSession();
	void CreerLeGrapheLogiciel( uint8_t valrt );
	void CreerLeGrapheFichierLie( uint16_t valrt );    
	void AppliquerModificationPriorite( uint8_t valrt );
    bool CreerBoutonImage( int dimimage, Gtk::Box *barreattache, bool img_alternat = false );
	Gtk::Button *CreerBoutonLogiciel( int posx, int posy );
    void CreerLeMenu();
    void TitreDeLaFenetre();
    void BarreBoutonLogiciel();
	void TraitementRetourConfig( uint8_t codret );
	void TraitementRetourContexte();
    void ImageAlternative( uint8_t index, bool sens );
	void Rallumer();
	void RallumerSup();

    void ChoisirContexte( uint8_t valrt );
	bool ChargerUnContexte();
//	void ChangerContexte();
	void EnregistrerContexte();
	void NettoyerLaScene();
	void TuerProcess();
	
	bool AjouterElement( Logiciel *pvaleur );
    void AjouterObjetContexte( const DonneesContexte &valctx );
	void EcrireContexte();
	void SupprimerUnObjet();
	void SupprimerFichierLie();
	void SupprimerObjetLogiciel();
	void DemarrerContexte();
	
};
#endif /* FENETRE_H */ 
