#ifndef DGCHAINELISTE_H
#define DGCHAINELISTE_H

#include <vector>
#include <string>

/**
  en cas d'utilisation des Glib StringList : 
  inclure la ligne : add_compile_definitions( OKGTKMMSTRINGLIST )
  * dans le CMakeLists.txt
**/

#ifdef OKGTKMMSTRINGLIST 
#include "gtkmm/stringlist.h"
#endif /*OKGTKMMSTRINGLIST*/

class DGChaineListe
{
public:
    DGChaineListe();
	virtual ~DGChaineListe();
	
	std::vector<std::string> *PtrChaine();
	void Ajouter( const std::vector<std::string> *lstajoutee );
	bool Trouver(const std::string &valchaine);
	bool Position( const std::string &valeur, uint32_t &retindex );
	void Remplacer(const std::string &vchavant, const std::string &vchapres);
	void Effacer(const std::string &valchaine);
	bool Partager( const std::string &valchaine, char symbolecoupe );
	bool Concatener( std::string &valchaine, char separateur = 32 );
	uint32_t TailleListe() const;
	bool NonVide();
	void Vider();

#ifdef OKGTKMMSTRINGLIST 
	void ListerVers( Glib::RefPtr<Gtk::StringList> &gtkliststr );
#endif /*OKGTKMMSTRINGLIST*/

private:
	std::vector<std::string> chaineliste;
	std::vector<std::string>::iterator ctmp;
};

#endif // DGCHAINELISTE_H
