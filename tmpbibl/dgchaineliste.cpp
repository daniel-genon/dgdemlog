#include "dgchaineliste.h"
#include <algorithm>

DGChaineListe::DGChaineListe(){}
DGChaineListe::~DGChaineListe(){ Vider(); }
std::vector<std::string> *DGChaineListe::PtrChaine(){ return &chaineliste; }
void DGChaineListe::Ajouter( const std::vector<std::string> *lstajoutee )
{
	for( size_t i=0; i<lstajoutee->size(); i++ )
	{
		chaineliste.push_back( lstajoutee->at(i) );
	}
	
}
bool DGChaineListe::Trouver(const std::string &valchaine)
{
	ctmp = std::find (chaineliste.begin(), chaineliste.end(), valchaine);
	return (ctmp != chaineliste.end());
}
bool DGChaineListe::Position( const std::string &valeur, uint32_t &retindex )
{
	if( Trouver(valeur) )
	{
		 retindex = ctmp - chaineliste.begin();
		 return true;
	}
	return false;
}
void DGChaineListe::Effacer(const std::string &valchaine)
{
	ctmp = std::find (chaineliste.begin(), chaineliste.end(), valchaine);
    if( ctmp != chaineliste.end() )
		chaineliste.erase(ctmp);
}
void DGChaineListe::Remplacer(const std::string &vchavant, const std::string &vchapres)
{
	size_t lgori = vchavant.size();
	size_t lgfin = vchapres.size();
	for( size_t i=0; i<chaineliste.size(); i++ )
	{
		size_t position = chaineliste[i].rfind(vchavant);
		while(position!=std::string::npos)
		{
			chaineliste[i].replace(position,lgfin,vchapres);
			position = chaineliste[i].rfind(vchavant);
		}
	}
}
bool DGChaineListe::NonVide() { return !chaineliste.empty(); }
uint32_t  DGChaineListe::TailleListe() const { return chaineliste.size(); }
void DGChaineListe::Vider()
{
	while (!chaineliste.empty())
	{
		chaineliste.back().clear();
		chaineliste.pop_back();
	}
}
bool DGChaineListe::Partager( const std::string &valchaine, char symbolecoupe )
{
	if( valchaine.size()!=0 )
	{
		std::string test = valchaine;
		std::size_t position = test.find_first_of( symbolecoupe );
		while( position/=std::string::npos )
		{
			chaineliste.push_back( test.substr( 0, position ) );
			test.erase( 0, position );
			position = test.find_first_of( symbolecoupe );
		}
		chaineliste.push_back( test );
	}
	return NonVide();
}
bool DGChaineListe::Concatener( std::string &valchaine, char separateur )
{
	if(separateur==0)
	{
		for( size_t i=0; i<chaineliste.size(); i++ )
			valchaine.append(chaineliste[i]);
	}
	else
	{
		for( size_t i=0; i<chaineliste.size(); i++ )
		{
			valchaine.append(chaineliste[i]);
			valchaine.push_back(separateur);
		}
		valchaine.pop_back();
	}
	return !valchaine.empty();	
}

#ifdef OKGTKMMSTRINGLIST 
void DGChaineListe::ListerVers( Glib::RefPtr<Gtk::StringList> &gtkliststr )
{
	std::vector<Glib::ustring> lstphr;
	Glib::ustring	phrtmp;
	for(unsigned long i=0;i<TailleListe();i++)
	{
		phrtmp = chaineliste[i];
		lstphr.push_back(phrtmp);
	}
	gtkliststr = Gtk::StringList::create(lstphr);
}
#endif /*OKGTKMMSTRINGLIST*/

