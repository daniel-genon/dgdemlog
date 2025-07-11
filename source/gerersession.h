#ifndef GERERSESSION_H
#define GERERSESSION_H

#include "../bloc/fblocsession.h"
#include "../bloc/fblocprojet.h"
#include "../defdia/creerprojet/creerprojet.h"
#include "../defdia/creercontexte/creercontexte.h"

class GererSession : public FBlocSession
{
public:
    int noerreur;

    GererSession();
	virtual ~GererSession();
	
	void LireSessionEnCours();
    void ChargerSession();
	bool ChargerSession( const std::string &nomprojet, const std::string &nomcontexte );
	
    std::string CheminRacine() const;
    std::string CheminStandard() const;
    std::string *ptrCheminRacine();
    std::string CheminProjet() const;
    std::string CheminContexte() const;

    std::string LibelleErreur() const;

    bool oksession();
    bool okboite();
    void Enregistrer();
    void MiseAJourListeConfig( const std::vector<std::string> &lstcfg );

    void CreerNouveauProjet( uint8_t valrt );
    void CreerNouveauContexte( uint8_t valrt );
    void ReactionEnRetour( const sigc::slot<void()> &slot );

    void SauverEnrgProjet();
    void RestaurerEnrgProjet();
    void ReserverEnrgProjet();
    void RetablirEnrgProjet();

    FBlocProjet *pFichierProjet();

private:

    std::string phrtmp1, phrtmp2;
    std::string cheminhome;// chemin du home de l'utilisateur
    std::string cheminracine;// chemin du repertoire de multiapp
    DGChaineListe	listedesconfigurations;
	sigc::slot<void()> signalderappel;
	
    FBlocProjet	fichierprojet;
    
    CreerProjet		*dlgnouvprojet;
    CreerContexte	*dlgnouvcontexte;
	
	void InitEnrgSession();
    void CreerRepertoire();
    void CreerCheminParDefaut();
    void VerifierRepertoire();
    void CreerEnvironnementContexte();
};

#endif // GERERSESSION_H
