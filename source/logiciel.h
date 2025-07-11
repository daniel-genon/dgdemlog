#ifndef LOGICIEL_H
#define LOGICIEL_H

#include "graphobjetactif.h"
#include "fichierlie.h"

class  Logiciel : public GraphObjetActif
{
public:

    bool okvalide;

    Logiciel();
    Logiciel( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene, const DonneesContexte &valctx  );
    Logiciel( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene, uint8_t noprio, uint16_t gelement=100 );

    FichierLie *PtrFicLie( uint8_t cas );
    //FichierConfiguration *PtrFicCfg();
    
    bool VerifierExistenceSurScene();
    void ReconfigurerGraphique( uint8_t nindiceprio );
    void CollationnerDescripteur( EnrgObjetCtx *enrgtmp );
    
    uint8_t  IndicePriorite() const;
	uint8_t ValeurPriorite() const;


	std::string NomPriorite() const;
	std::string NomDuProcessus() const;
	std::string NomStdLie( uint16_t genre ) const;
    std::string NomStdCFG() const;
    std::string NomStdTRV() const;
	std::string Options( uint16_t genre ) const;
    std::string Dependance() const;
    std::string CheminProcess() const;
    uint16_t	DelaiApresDemarrage() const;
    
	bool ALeFichierLie( uint16_t genre );
    bool UnSeulAutorise();
        
    virtual std::string libelle() const;

protected :

    bool EstLeProcessus( const std::string &nomtest );

    virtual std::string LibelleTitre();
    virtual std::string LibelleNom();
    virtual Glib::RefPtr<Gdk::Pixbuf> ChargerIcone();

private:

    EnrgLogiciel    donneelogiciel;
    std::string	libellepriorite; 
    uint8_t		indicepriorite;
	const std::string libellefinappli = "Quitter automatiquement";

    void InitLogFinApplication();

};


#endif // LOGICIEL_H
