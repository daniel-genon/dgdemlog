#ifndef ENRGVARIABLEMSA_H
#define ENRGVARIABLEMSA_H

#include "../tmpbibl/dgchaineliste.h"

class EnrgVariableMSA
{
public:
    EnrgVariableMSA();
    EnrgVariableMSA( const std::string &vvaleur,
                     const std::string &vdefinition,
                     const std::string &vcode_abrege);

    std::string Valeur() const;
    std::string Definition() const;
    std::string Code_Abrege() const;

private:
    std::string valeur;
    std::string definition;
    std::string code_abrege;

};

typedef EnrgVariableMSA *ptrenrgvariableMSA;

class LstVarMSA
{
public:
    LstVarMSA();
    ~LstVarMSA();
    void Ajouter(const std::string &vvaleur,
                 const std::string &vdefinition,
                 const std::string &vcode_abrege );
    void Marques(const std::string &mavant,const std::string &mapres);
    void RemplacerCode( DGChaineListe &listevariablecode );

    void Nettoyer();

    bool VerifierVariableMSA(const std::string &vphranalyse);
    bool PointerValeur(const std::string &vcherche);
    bool ConstruireInsertionCode( std::string &insertion );
    ptrenrgvariableMSA RtPtrEnrg() const;
    
	unsigned long TailleListe() const;
	
#ifdef OKGTKMMSTRINGLIST 
	void ListerValeur( Glib::RefPtr<Gtk::StringList> &gtkliststr );
#endif /*OKGTKMMSTRINGLIST*/


private:

	std::vector<ptrenrgvariableMSA> listepointeur;
	std::vector<ptrenrgvariableMSA>::iterator ctmp;

    std::string phranalyse;
    std::string marqueav;
    std::string marqueap;
    std::string codeabregeencours;

    ptrenrgvariableMSA ptrenrgvar;

    void RazDonnees();
    bool PointerEnrg();
    bool TrouverCodeAbrege();

};


#endif // ENRGVARIABLEMSA_H
