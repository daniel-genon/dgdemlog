#ifndef DIALOGCONFIGGENERALE_H
#define DIALOGCONFIGGENERALE_H

#include <gtkmm.h>
#include "../../bloc/fblocconfig.h"
#include "../messagemsa.h"
#include "../../enrg/enrgvariablemsa.h"
#include "../infovariablemsa.h"

class DialogConfigGenerale;
typedef void (DialogConfigGenerale::*PtrFnctRet)( uint8_t );
typedef void (DialogConfigGenerale::*PtrFnctDCG)( void );

class DialogConfigGenerale : public Gtk::Window
{
public:
    DialogConfigGenerale();
    ~DialogConfigGenerale();

	void ConnexionRetour(const sigc::slot<void(uint8_t)> &slot);

	uint8_t RetourCodeModification();
	void IniBoite( FBlocConfig *pvaleur, LstVarMSA *lvarmsa = nullptr );

private:

    FBlocConfig     *pfichier;
    BoiteDialogue	*msgmsa;
    LstVarMSA		*plvarmsa;
    PtrFnctDCG		pFncVoid, pFncAppeloui, pFncAppelnon;
    PtrFnctRet		pFncRetourValeur;
    
    uint8_t	coderetmodif;

/**
 * Page onglet configuration
 * membres et méthodes
**/
//	uint32_t indconfig;
//	DGChaineListe	lstnomconfig;

    Gtk::Box	*CGeneral;
//    Glib::RefPtr<Gtk::StringList> Clstconfig;
//    Glib::RefPtr<Gtk::SingleSelection> selconfig;
//	Gtk::ListView	*lstconfig;
	Gtk::SpinButton *hticodrt, *hticoctr, *hticogah;
	Gtk::FontButton	*btnchxpol;
	Gtk::ColorButton	*coulpol, *coulmenu, *coulgraf; 
    
	void MasqueOngletConfig();
//	void ChangerConfig( guint position, guint n_items);
//	void AttacheNomConfig(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void MiseAJourOngletApplication();
//	void NouvelleConfiguration();
//	void ChargerConfiguration();
//	void CreerNouvConfig();
//	void SaisirNomConfiguration();

/**
 * Page onglet connexion
 * membres et méthodes
**/
	uint32_t indconnex;
	
	Gtk::Box	*CConnexion;
	Gtk::Entry	*edinomficico;
	Glib::RefPtr<Gtk::StringList> Clstconnex;
    Glib::RefPtr<Gtk::SingleSelection> selcnx;
	Gtk::ColorButton 	*coulcnx, *coulfndico, *coulpolico;
	Gtk::DropDown	*chxtplcnx;
	Gtk::SpinButton	*eprlgncnx, *lgico, *htico;
	Gtk::FontButton		*btnchxpolico;
		
	void MasqueOngletConnexion();
	void ChangerConnexion( guint position, guint n_items);
	void MiseAJourOngletConnexion();
	void AttacheNomConnexion(const Glib::RefPtr<Gtk::ListItem>& list_item);
	
/**
 * Page onglet logiciel
 * membres et méthodes
**/
	bool okcollationnerlogiciel;
	InfoVariableMSA	*dialvarmsa;
    Glib::RefPtr<Gtk::StringList>	Clstlogiciel;
	Glib::RefPtr<Gtk::StringList>	lstvariable;
 	Glib::RefPtr<Gtk::SingleSelection> sellogiciel;
	Gtk::DropDown	*chxlstvar;
	Gtk::SpinButton	*delatt, *poscol;
	Gtk::CheckButton	*occunique;
	Gtk::Box	*CLogiciel;
	Gtk::Entry	*edinomproc, *edinomfico, *edilstopt, *ediopttrv,
				*edioptcfg,	*edidospro, *ediprodep, *edificstdtrv,
				*edificstdcfg, *ediphraide;
	uint32_t	indlogiciel;
	ptrenrglogiciel	ptrlog;
				
	void MasqueOngletLogiciel();
	void ChangerLogiciel( guint position, guint n_items);
	void AttacheNomLogiciel(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void MiseAJourOngletLogiciel(); 
	void TransfererVariable();
	void VoirAideVariable( uint8_t cas );
	void AjouterUnLogiciel();
	void SupprimerLogiciel();
	void SupprimerLogicielOK();
	void CreerNouvEnrgLogiciel();

/**
 * Page onglet priorité
 * membres et méthodes
**/
	Gtk::Box	*CPriorite;
	bool okcollationnerpriorite;
	uint32_t indexprio;
    Glib::RefPtr<Gtk::StringList> Clstpriorite;
    Glib::RefPtr<Gtk::SingleSelection> selprio;
	Gtk::SpinButton	*nivprio, *larsym, *htrsym;    
	Gtk::FontButton	*btnchxpolsym;
	Gtk::ColorButton 	*clsymband, *clsymfond, *coulpolsym;
	void MasqueOngletPriorite();
	void ChangerPriorite( guint position, guint n_items);
	void AttacheNomPriorite(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void MiseAJourOngletPriorite();
	void AjouterUnePriorite(); 
	void SupprimerPriorite();
	void SupprimerPrioriteOK();
	void CreerNouvEnrgPriorite();

/**
 * Page onglet graphiques fichiers liés
 * membres et méthodes
**/
	Gtk::Box	*CGraphlie;
	uint32_t indexflie;
	Glib::RefPtr<Gtk::StringList> Clstficlie;
    Glib::RefPtr<Gtk::SingleSelection> selfli;
	Gtk::SpinButton	*larfli, *htrfli;    
	Gtk::FontButton	*btnchxpolfli;
	Gtk::ColorButton 	*clfliband, *clflifond, *coulpolfli;
	
	
	void MasqueOngletFichierLie();
	void ChangerFicLie( guint position, guint n_items);
	void AttacheNomFicLie(const Glib::RefPtr<Gtk::ListItem>& list_item);
	void MiseAJourOngletFichierLie();
	
/**
 * membres et méthodes communes
**/
//	bool okboite;
	std::string	chainetmp;
    Gtk::Button	*bouaccepte;
	Gtk::FileChooserDialog *boitefichier;
	
	void ConfigLibelle( const Glib::RefPtr<Gtk::ListItem>& list_item );
	
	void ChoisirFichier( int cas );
	void ReponseFichier( int reponse, int cas );
	void SaisirValeur( const Glib::ustring& liblibel, const uint8_t &typezone );
	void Reponse_Entree( uint8_t vrt );
	void Sauvegarde();
    bool ValeursModifiees();
    void SauvegardeOK();
    
	void MessageInfo( const Glib::ustring &libmess);
	void QuestionOuiNon(const Glib::ustring& libmess,const Glib::ustring& libques);

    EnrgConfig      	econfig;		//codetransfert = 0
    LstEnrgConnexion	elstconnex;		//codetransfert = 2
    LstEnrgLogiciel		elstlogiciel;	//codetransfert = 4
    LstEnrgGrLog    	elstgraph;		//codetransfert = 8
    LstEnrgGrFic    	elstficlie;		//codetransfert = 16
    EnrgAncre			eancre;			//codetransfert = 32

    void TransfererValeurs( uint8_t codetransfert );// 31 tous les enrgs
    void InitialiserValeurs();
    //void AfficherValeur();
    //bool Initialiser_Variable_MSA();
    //void GererZoneVariable_MSA();

    void CollationnerValeurs();
    void CollationnerConfig();
    void CollationnerConnexion();
    void CollationnerPriorite();
    void CollationnerLogiciel();
    void CollationnerGraphFicLie();
	void CollationnerAncre();

    bool ConfigGeneralModifiee();
    bool LogicielModifie();
    bool ConnexionModifiee();
    bool PrioriteModifiee();
    bool FiclieModifie();
	bool AncrageModifie();
};

#endif // DIALOGCONFIGGENERALE_H
