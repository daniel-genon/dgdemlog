#ifndef FICHIERLIE_H
#define FICHIERLIE_H

#include "graphobjetactif.h"

class FichierLie : public GraphObjetActif
{
public:

    FichierLie( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene );
    void InitFichierLie( uint16_t genre, const std::string &nom, const std::string &icone );
	bool InitFichierLie( uint16_t genre, const DonneesContexte &valctx );
    bool InitNomFichier( const std::string &nom );
    void CvtNomComplet( void *valret );
    
    std::string NomCompletFichier() const;
	
protected:	

private:
	std::string nomicone;
	std::string nomfichier;
	std::string nomfichiercomplet;
	virtual std::string LibelleTitre();
	virtual std::string LibelleNom();
	virtual Glib::RefPtr<Gdk::Pixbuf> ChargerIcone();

};

#endif // FICHIERLIE_H
