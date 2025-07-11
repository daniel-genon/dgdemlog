#ifndef ENRGLOGICIEL_H
#define ENRGLOGICIEL_H

#include "../source/structureappli.h"
#include <string>

class EnrgLogiciel
{
public:
    EnrgLogiciel();
    EnrgLogiciel( const EnrgLogiciel &autre );
    EnrgLogiciel( const std::string &vnom,
                  const std::string &vcla,
                  const std::string &vopt,
                  const std::string &vaid,
                  const std::string &vdos,
                  const std::string &vico,
                  const std::string &vdep, uint16_t vdelai, uint8_t vuni, uint8_t vclas ,
                  const std::string &vstcfg, const std::string &vsttrv,
                  const std::string &opcfg, const std::string &optrv  );

    void Valeur(  const EnrgLogiciel *pautre );
    void Valeur(  const EnrgLogiciel &autre );
    void Valeur(  const std::string &vnom,
                  const std::string &vcla,
                  const std::string &vopt,
                  const std::string &vaid,
                  const std::string &vdos,
                  const std::string &vico,
                  const std::string &vdep, uint16_t vdelai, uint8_t vuni, uint8_t vclas,
                  const std::string &vstcfg, const std::string &vsttrv,
                  const std::string &opcfg, const std::string &optrv );

    void NomProcessus( const std::string &valeur);
    void NomClair( const std::string&valeur);
    void Options( const std::string &valeur);
    void Aide( const std::string &valeur);
    void Dossier( const std::string &valeur);
    void Icone( const std::string &valeur);
    void Delai( uint16_t valeur);
    void Unique( uint8_t valeur);
    void Classe( uint8_t valeur);
    void Unique( bool valeur);
    void Dependance( const std::string &valeur);
    void StdCFG( const std::string &valeur);
    void StdTRV( const std::string &valeur);
    void OptCFG( const std::string &valeur);
    void OptTRV( const std::string &valeur);


        std::string NomProcessus() const;
        std::string NomClair() const;
        ChaineNom BNomClair() const;
        std::string Options() const;
        std::string Aide() const;
        std::string Dossier() const;
        std::string Icone() const;
        uint16_t  Delai() const;
        uint8_t  Unique() const;
        uint8_t  Classe() const;
        bool    UniqueB();
        std::string Dependance() const;
        std::string StdTRV() const;
        std::string StdCFG() const;
        std::string OptTRV() const;
        std::string OptCFG() const;
        
        DonneesLogiciel Donnees() const;

        bool EgaleA( const EnrgLogiciel &autre );
        bool EgaleA(const EnrgLogiciel *autre , bool testnom=true);

    void CopierVersBloc( BlocLogiciel &cible );
    void CopierDepuisBloc( const BlocLogiciel &source );

protected:

	void CvtChaineNom( const std::string &valeur , void *memdestinataire );
	void CvtChaineGrandNom( const std::string &valeur , void *memdestinataire );

private:

	DonneesLogiciel contenu;
    //ChaineGrandNom   imicone;
    //ChaineGrandNom   phraide;
    //ChaineGrandNom   dosproc;
    //ChaineGrandNom   dependance;
    //ChaineGrandNom   stdcfg;
    //ChaineGrandNom   stdtrv;
    //ChaineNom   options;
    //ChaineNom	nomprocessus;
    //ChaineNom	nomclair;
    //ChaineNom	optcfg;
    //ChaineNom	opttrv;
    //uint8_t		delai;
    //uint8_t		unique;
    //uint8_t		classe;


};

typedef EnrgLogiciel *ptrenrglogiciel;

class LstEnrgLogiciel
{
public:
    LstEnrgLogiciel();
    LstEnrgLogiciel( ptrenrglogiciel nouveau );
    ~LstEnrgLogiciel();

    void Ajouter(const std::string &vnom,
                  const std::string &vcla,
                  const std::string &vopt,
                  const std::string &vaid,
                  const std::string &vdos,
                  const std::string &vico,
                  const std::string &vdep,
                  uint16_t vdelai, uint8_t vuni , uint8_t vclas,
                 const std::string &vstcfg, const std::string &vsttrv,
                 const std::string &opcfg, const std::string &optrv );

    void Ajouter( const BlocLogiciel &source);
    void CopierSimple(const LstEnrgLogiciel &source);// les pointeurs sont inchangés, toute modif
                                                    // affecte les valeurs de l'enrg
    void Copier(const LstEnrgLogiciel &source);// De nouveaux objets sont copiés sur les pointeurs
                                                // les modifs n'influent pas sur l'objet original
    void Copier(const LstEnrgLogiciel *source);// De nouveaux objets sont copiés sur les pointeurs
                                                // les modifs n'influent pas sur l'objet original
    bool EgaleA( const LstEnrgLogiciel &autre, bool testnom=true);
    void Nettoyer();
	void Supprimer( uint32_t nindex );    
    uint32_t TailleListe() const;
    ptrenrglogiciel Position( uint32_t nindex ) const;
    bool TrouverNom( const std::string &valeur, uint32_t &retindex );
    ptrenrglogiciel FinDeListe() const;
    ptrenrglogiciel DebutDeListe() const;

    void Standard();
    
#ifdef OKGTKMMSTRINGLIST 
	void ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr );
#endif /*OKGTKMMSTRINGLIST*/
    
private :
	std::vector<ptrenrglogiciel> listepointeur;
	std::vector<ptrenrglogiciel>::iterator ctmp;

};
typedef LstEnrgLogiciel *ptrlstenrglogiciel;

#endif // ENRGLOGICIEL_H
