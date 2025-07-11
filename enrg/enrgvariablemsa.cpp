#include "enrgvariablemsa.h"

EnrgVariableMSA::EnrgVariableMSA(){}
EnrgVariableMSA::EnrgVariableMSA(const std::string &vvaleur,
                 const std::string &vdefinition,
                 const std::string &vcode_abrege)
{
    valeur.append(vvaleur);
    definition.append(vdefinition);
    code_abrege.append(vcode_abrege);
}
std::string EnrgVariableMSA::Valeur() const { return valeur;}
std::string EnrgVariableMSA::Definition() const { return definition;}
std::string EnrgVariableMSA::Code_Abrege() const { return code_abrege; }

/*****************************************************************************

*****************************************************************************/

LstVarMSA::LstVarMSA()
{
    marqueav="$£$";
    marqueap="$§$";
    RazDonnees();
}
LstVarMSA::~LstVarMSA()
{
	Nettoyer();
}
void LstVarMSA::Nettoyer()
{
	for (ctmp = listepointeur.begin(); ctmp != listepointeur.end(); ++ctmp)
		delete *ctmp;
	listepointeur.clear();
}
void LstVarMSA::Ajouter( const std::string &vvaleur,
                         const std::string &vdefinition,
                         const std::string &vcode_abrege )
{
    ptrenrgvariableMSA pnouveau = new EnrgVariableMSA( vvaleur, vdefinition, vcode_abrege );
    listepointeur.push_back(pnouveau);
}

bool LstVarMSA::VerifierVariableMSA( const std::string &vphranalyse )
{
    RazDonnees();
    if(vphranalyse.size()!=0)
    {
        phranalyse = vphranalyse;
        return TrouverCodeAbrege();
    }
    return false;
}

bool LstVarMSA::TrouverCodeAbrege()
{
	if(phranalyse.size()!=0)
	{
		size_t deb, fin, nbcar;
		if((deb = phranalyse.find(marqueav)) != std::string::npos )
		{
			if((fin = phranalyse.find(marqueap,deb+2)) != std::string::npos )
			{
				deb += marqueav.size();
				nbcar = fin-deb;
				codeabregeencours = phranalyse.substr (deb,nbcar);
				return PointerEnrg();
			}
        }
    }
    return false;
}
bool LstVarMSA::PointerEnrg()
{
    if(!codeabregeencours.size()!=0)
    {
        for( size_t i=0; i<listepointeur.size(); i++ )
        {
            if(listepointeur[i]->Code_Abrege() == codeabregeencours)
            {
                ptrenrgvar = listepointeur[i];
                return true;
            }
        }
    }
    return false;
}

void LstVarMSA::RazDonnees()
{
    phranalyse.clear();
    codeabregeencours.clear();
    ptrenrgvar  = nullptr;
}
unsigned long LstVarMSA::TailleListe() const
{
	return listepointeur.size();
}
ptrenrgvariableMSA LstVarMSA::RtPtrEnrg() const
{
    return ptrenrgvar;
}

bool LstVarMSA::PointerValeur(const std::string &vcherche)
{
    if(vcherche.size()!=0)
    {
        RazDonnees();
        for( size_t i=0; i<listepointeur.size(); i++ )
        {
            if(listepointeur[i]->Valeur() == vcherche)
            {
                ptrenrgvar = listepointeur[i];
                return true;
            }
        }
    }
    return false;
}
bool LstVarMSA::ConstruireInsertionCode( std::string &insertion )
{
    insertion.clear();
    if( ptrenrgvar != nullptr )
    {
        insertion = marqueav+ptrenrgvar->Code_Abrege();
        insertion.append(marqueap);
    }
    return insertion.size()!=0;
}
void LstVarMSA::RemplacerCode( DGChaineListe &listevariablecode )
{
    RazDonnees();
    std::string phrtmp;
    for( size_t i=0; i<listepointeur.size(); i++ )
    {
        ptrenrgvar=listepointeur[i];
        if(ConstruireInsertionCode( phrtmp ))
            listevariablecode.Remplacer(phrtmp,ptrenrgvar->Valeur());
    }
}
#ifdef OKGTKMMSTRINGLIST 
void LstVarMSA::ListerValeur( Glib::RefPtr<Gtk::StringList> &gtkliststr )
{
	std::vector<Glib::ustring> lstphr;
	Glib::ustring	phrtmp;
	for(unsigned long i=0;i<TailleListe();i++)
	{
		phrtmp = listepointeur[i]->Valeur();
		lstphr.push_back(phrtmp);
	}
	gtkliststr = Gtk::StringList::create(lstphr);
}
#endif /*OKGTKMMSTRINGLIST*/

