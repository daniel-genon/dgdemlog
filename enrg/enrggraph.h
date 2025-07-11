#ifndef ENRGGRAPH_H
#define ENRGGRAPH_H

#include "enrgpolice.h"

class EnrgGraph
{
public:

    EnrgGraph();
    EnrgGraph( const std::string &vnom,
               const std::string &vcf,
               const std::string &vcb,
               const BlocPolice &vpol,
               uint16_t vlar, uint16_t vhau, uint8_t vprio );

    void Valeur(const std::string &vnom,
                       const std::string &vcf,
                       const std::string &vcb,
                       const BlocPolice &vpol,
                       uint16_t vlar, uint16_t vhau, uint8_t vprio);

    void Valeur( const EnrgGraph &autre );
    void Valeur( const EnrgGraph *autre );

    void Nom( const std::string &valeur);
    void ValeurPriorite(const uint8_t valeur );
    void Hauteur(  const uint16_t valeur );
    void Largeur(  const uint16_t valeur );
    void DimSymbole( const uint16_t htr, const uint16_t lgr );
    void CouleurFond( const std::string &valeur);
    void CouleurBandeau( const std::string &valeur);
    void Police( const BlocPolice &valeur );
    
	DonneesGraphe Donnees() const;


    std::string	Nom() const;
	ChaineNom	BNom() const;
    std::string CouleurFond() const;
    std::string CouleurBandeau() const;
    uint16_t  Hauteur() const;
    uint16_t  Largeur() const;
    uint8_t  ValeurPriorite() const;
    BlocPolice Police() const;

//    std::string *PtrCouleurFond();
//    std::string *PtrCouleurBandeau();
//    EnrgPolice *PPolice();

    bool EgaleA( const EnrgGraph &autre );
    bool EgaleA( EnrgGraph *autre );
    void CopierVersBloc( BlocGraphLog &cible );
    void CopierDepuisBloc( const BlocGraphLog &source );

private :

	DonneesGraphe contenu;

};

typedef EnrgGraph *ptrenrgraphique;

class LstEnrgGraph
{
public:

    LstEnrgGraph();
    LstEnrgGraph( ptrenrgraphique nouveau);
    ~LstEnrgGraph();

    void Ajouter( const std::string &vlibelle,
                const std::string &vcoulfond,
                const std::string &vcoulband,
                const BlocPolice &vpolice,
                uint16_t vlg, uint16_t vht, uint8_t vprio );

    void Ajouter( const BlocGraphLog &source );
    void CopierSimple( const LstEnrgGraph &source ); // les pointeurs sont inchangés, toute modif
                                                    // affecte les valeurs de l'enrg
    void Copier( const LstEnrgGraph &source );   // De nouveaux objets sont copiés sur les pointeurs
                                                // les modifs n'influent pas sur l'objet original
    bool EgaleA( const LstEnrgGraph &autre );

    void Nettoyer();
	void Supprimer( uint32_t nindex );    
	bool TrouverNom( const std::string &valeur, uint32_t &retindex );
    
    uint32_t TailleListe() const;
    ptrenrgraphique Position( uint32_t nindex ) const;

    virtual void Standard();
    
#ifdef OKGTKMMSTRINGLIST 
	void ListerNom( Glib::RefPtr<Gtk::StringList> &gtkliststr );
#endif /*OKGTKMMSTRINGLIST*/

private :
	std::vector<ptrenrgraphique> listepointeur;
	std::vector<ptrenrgraphique>::iterator ctmp;
};




class LstEnrgGrLog : public LstEnrgGraph
{
public:
    LstEnrgGrLog();
    virtual void Standard();
};


class LstEnrgGrFic : public LstEnrgGraph
{
public:
    LstEnrgGrFic();
    virtual void Standard();
};

#endif // ENRGGRAPH_H
