#ifndef ENRGCONNEXION_H
#define ENRGCONNEXION_H

#include "../source/structureappli.h"

class EnrgConnexion
{
public:

    EnrgConnexion();
    EnrgConnexion( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr  );

    void Valeur( const EnrgConnexion &autre );
    void Valeur( const EnrgConnexion *autre );
    void Valeur( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr );

	void Nom( const std::string &valeur);
	std::string Nom() const;
	std::string Couleur() const;
	ChaineNom	BNom() const;
    uint8_t TypeLigne() const;
    uint8_t Epaisseur() const;
    
    DonneesLigne Donnees() const;

    bool EgaleA( const EnrgConnexion &autre );
    bool EgaleA( EnrgConnexion *autre );
    void CopierVersBloc( BlocConnexion &cible );
    void CopierDepuisBloc( const BlocConnexion &source );
    
    virtual void Standard();

private:
    DonneesLigne donneesligne;

};

typedef EnrgConnexion *ptrenrconnexion;

class LstEnrgConnexion
{
public:

    LstEnrgConnexion();
    LstEnrgConnexion( ptrenrconnexion nouveau );
    ~LstEnrgConnexion();

    void Ajouter( const std::string &vnom, const std::string &vcou, uint8_t vtyp, uint8_t vepr );
	void Ajouter( const BlocConnexion &source);
    void Nettoyer();
	bool TrouverNom( const std::string &valeur, uint32_t &retindex );

	void CopierSimple( const LstEnrgConnexion &source);
	void Copier( const LstEnrgConnexion &source);
	
	bool EgaleA( const LstEnrgConnexion &autre );
    
    uint32_t TailleListe() const;
    ptrenrconnexion Position( uint32_t nindex ) const;

    virtual void Standard();
    
#ifdef OKGTKMMSTRINGLIST 
	void ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr );
#endif /*OKGTKMMSTRINGLIST*/

private :
//0 lignelogiciel;
//1 lignetravail;
//2 ligneconfigu;
	std::vector<ptrenrconnexion> listepointeur;
	std::vector<ptrenrconnexion>::iterator ctmp;
};



#endif // ENRGCONNEXION_H
