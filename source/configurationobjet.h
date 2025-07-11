#ifndef CONFIGURATIONOBJET_H
#define CONFIGURATIONOBJET_H

#include "../bloc/fblocobjetcontexte.h"
#include "../enrg/enrgconnexion.h"
#include "../enrg/enrgvariablemsa.h"
#include "../defdia/dialconfgen/dialogconfiggenerale.h"
#include "../defdia/dialconfnouv/dialconfnouv.h"

class ConfigurationObjet : public FBlocConfig
{

public:
    ConfigurationObjet();
    ~ConfigurationObjet();

    bool InitialiserConfiguration( const std::string &chemracine, const std::string &nomcfg );
    void GestionConfiguration( uint8_t valrt );
    void ReactionEnRetour( const sigc::slot<void( uint8_t )> &slot );
    void CreerUneNouvelleConfiguration( uint8_t valrt );

    bool PointerLogiciel( const ChaineNom &nomclairlog );
    bool PointerLogiciel( uint8_t noclasse, uint8_t indexlog );
    bool ListeDesClassesLogiciels( std::vector<uint8_t> &listclasse, bool trier=false );
    bool CollecterLogicielDeLaClasse( const uint8_t noclasse, std::vector<ptrenrglogiciel> &lstretptr );

	uint16_t LireValeurPriorite( const uint8_t &valeur );
    bool ListeLabelPriorites( DGChaineListe &listelabel );

    std::string ConfigurationEnCours() const;
    uint8_t HtrIcoLog();
    uint8_t HtrIcoGes();
    uint8_t HtrIcoDessus();
    ptrenrglogiciel PointeurLogstock();
    ptrenrgraphique PointerFicli( uint8_t valeur );
    ptrenrconnexion PointeurCo( uint8_t valeur );

    LstVarMSA       lvarmsa;
    
//    bool ConfigListeLogicielModifiee();

protected:

private:
    std::string		phtmp;// zone texte fourretout
    ptrenrglogiciel	ptrlogencours;
//    bool			lstlogicielchangee;
    DialogConfigGenerale *dlgconfig;
    DialogNouvelleConfig *dlgnouvconfig;
    
    sigc::slot<void( uint8_t )> signalderappel;

    void ConfigParDefaut();
	bool Trouver( const std::vector<uint8_t> &lst, const uint8_t valeur );

};

#endif // CONFIGURATIONOBJET_H
