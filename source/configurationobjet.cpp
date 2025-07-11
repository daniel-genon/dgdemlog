#include "configurationobjet.h"
//#include "../defdia/dialconfgen/dialogconfiggenerale.h"
//#include <algorithm>

ConfigurationObjet::ConfigurationObjet()
{
	dlgconfig		= nullptr;
	ptrlogencours	= nullptr;
	dlgnouvconfig	= nullptr;
}
ConfigurationObjet::~ConfigurationObjet()
{
	if(dlgconfig!=nullptr) delete dlgconfig;
    lvarmsa.Nettoyer();
}
ptrenrglogiciel ConfigurationObjet::PointeurLogstock(){ return ptrlogencours; }
ptrenrconnexion ConfigurationObjet::PointeurCo( uint8_t valeur ){ return lstconnexion.Position( valeur ); }
ptrenrgraphique ConfigurationObjet::PointerFicli( uint8_t valeur ){ return lstgrhficlie.Position( valeur ); }
void ConfigurationObjet::ReactionEnRetour( const sigc::slot<void( uint8_t )> &slot ){ signalderappel = slot; }
bool ConfigurationObjet::InitialiserConfiguration( const std::string &chemracine, const std::string &nomcfg )
{
	InitDescription(chemracine);
	if(FichierExiste())
    {
        if(!LireConfiguration( nomcfg ))
        {
			if(!LirePremiereConfig())
                ConfigParDefaut();
            return false;
        }
    }
    else
    {
        ConfigParDefaut();
        CreerConfigurationStandard();
        return false;
    }
    return true;
}
std::string ConfigurationObjet::ConfigurationEnCours() const { return enrgconfig.Nom(); }
void ConfigurationObjet::CreerUneNouvelleConfiguration( uint8_t valrt )
{
	if(valrt==0)
	{
		DGChaineListe lstconf;
		ListerLesBlocs( lstconf.PtrChaine() );
		if(dlgnouvconfig!=nullptr) delete dlgnouvconfig;
		dlgnouvconfig = new DialogNouvelleConfig( &lstconf );
		dlgnouvconfig->ConnexionRetour(sigc::mem_fun(*this, &ConfigurationObjet::CreerUneNouvelleConfiguration));
	}
	else
	{
		if(dlgnouvconfig!=nullptr)
		{
			if( valrt!=255 )
			{
				std::string nomcfgnouv, nomcfgcopie;
				std::string nomconfigsvd(ConfigurationEnCours());
				uint8_t codmod = dlgnouvconfig->Collationner( nomcfgnouv, nomcfgcopie );
				bool okcopie = false;
				switch(codmod)
				{
					case 0 ://vide
						ConfigParDefaut();
						[[fallthrough]];
					case 2 ://copie configuration actuelle
						okcopie = true;
					break;
					case 1 ://standard
						nomcfgcopie = "STANDARD";
						[[fallthrough]];
					case 3 ://copie configuration existante
						okcopie = LireConfiguration( nomcfgcopie );
				}
				if(okcopie)
				{
					enrgconfig.Nom( nomcfgnouv );
					EcrireConfig();
				}
				LireConfiguration( nomconfigsvd );
			}
			delete dlgnouvconfig;
			dlgnouvconfig=nullptr;
		}
	}
	
}
void ConfigurationObjet::GestionConfiguration( uint8_t valrt )
{
	if(valrt==0)
	{
		if(dlgconfig!=nullptr) delete dlgconfig;
		dlgconfig = new DialogConfigGenerale();
		dlgconfig->ConnexionRetour(sigc::mem_fun(*this, &ConfigurationObjet::GestionConfiguration));
		dlgconfig->IniBoite((FBlocConfig*)this , &lvarmsa );
	}
	else
	{
		if(dlgconfig!=nullptr)
		{
			uint8_t codmod = dlgconfig->RetourCodeModification();
			if( codmod != 0 )
			{
				signalderappel( codmod );
			}
			delete dlgconfig;
			dlgconfig=nullptr;
		}
	}
}
//****************   GRAPHIQUE/PRIORITE   ************************************
uint16_t ConfigurationObjet::LireValeurPriorite( const uint8_t &valeur )
{
	if( valeur<lstenrgralog.TailleListe() )
	{
		return lstenrgralog.Position(valeur)->ValeurPriorite();
	}
	return 1;
}
bool ConfigurationObjet::ListeLabelPriorites( DGChaineListe &listelabel )
{
	listelabel.PtrChaine()->clear();
	for( uint16_t i=0; i<lstenrgralog.TailleListe(); i++ )
	{
		listelabel.PtrChaine()->push_back(lstenrgralog.Position(i)->Nom());
	}
	return listelabel.PtrChaine()->size()!=0;
}
////****************   LOGICIELS   ************************************
bool ConfigurationObjet::PointerLogiciel( const ChaineNom &nomclairlog )
{
    if(nomclairlog.v!=0)
    {
        for(uint32_t i=0;i<lstenrlog.TailleListe();i++)
		{
			ChaineNom nomtest = lstenrlog.Position(i)->BNomClair();
            if( memcmp( nomclairlog.v, &nomtest , TAILLECHAINENOM) ==0 )
            {
                ptrlogencours = lstenrlog.Position(i);
                return true;
            }
		}
    }
    return false;
}
bool ConfigurationObjet::PointerLogiciel( uint8_t noclasse, uint8_t indexlog )
{
	ptrlogencours = nullptr;
	std::vector<ptrenrglogiciel> lstptrlog;
	if( CollecterLogicielDeLaClasse( noclasse, lstptrlog ) )
	{
		if( indexlog <= lstptrlog.size() )
			ptrlogencours = lstptrlog.at(indexlog);
	}
    return ptrlogencours != nullptr;
}
bool ConfigurationObjet::CollecterLogicielDeLaClasse( const uint8_t noclasse, std::vector<ptrenrglogiciel> &lstretptr )
{
	lstretptr.clear();
    if(lstenrlog.TailleListe()>0)
    {
		uint16_t indlog	= 0;
        while( indlog<lstenrlog.TailleListe() )
        {
            if( lstenrlog.Position(indlog)->Classe() == noclasse )
				lstretptr.push_back( lstenrlog.Position( indlog ));
            indlog++;
        }
    }
    return lstretptr.size() != 0 ;
}
//****************   GRAPHIQUE/FICHIER LIE   ****************************
uint8_t ConfigurationObjet::HtrIcoLog(){	return enrgconfig.IconeSymbole(); }
uint8_t ConfigurationObjet::HtrIcoGes(){	return enrgconfig.IconeGestion(); }
uint8_t ConfigurationObjet::HtrIcoDessus(){	return enrgconfig.IconeDessus(); }
void ConfigurationObjet::ConfigParDefaut()
{
    enrgconfig.Standard();
    enrgancre.Standard();
    lstconnexion.Standard();
    lstenrlog.Standard();
    lstenrgralog.Standard();
    lstgrhficlie.Standard();
}
bool ConfigurationObjet::ListeDesClassesLogiciels( std::vector<uint8_t> &listclasse, bool trier )
{
    listclasse.clear();
    for( uint16_t i=0; i<lstenrlog.TailleListe(); i++ )
    {
        uint8_t inttmp = lstenrlog.Position(i)->Classe();
        if(!Trouver( listclasse, inttmp ))
            listclasse.push_back(inttmp);
    }
    if(listclasse.size()==0)
        return false;
    else
        if(trier)
            std::sort(listclasse.begin(),listclasse.end());
    return true;
}
bool ConfigurationObjet::Trouver( const std::vector<uint8_t> &lst, const uint8_t valeur )
{
	if( lst.size() == 0 ) return false;
	for( uint16_t i=0; i<lst.size(); i++ )
		if( lst[i] == valeur ) return true;
    return false;
}
