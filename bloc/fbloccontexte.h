#ifndef FBLOCCONTEXTE_H
#define FBLOCCONTEXTE_H

#include "tmp_chemin_bibliodg.h"
#include "../source/structureappli.h"

class FBlocContexte : public FicBin
{
public:

    FBlocContexte();

    std::string *CheminDuContexte();
    bool EcrireContexte( const EnrgContexte &valeurctx );
    bool LireContexte( const std::string &valeur );
    bool LirePremierContexte();
    bool Lister( DGChaineListe &lstvaleur );
	void InitialiserCheminProjet( std::string *vcheminprojet, const std::string &vnomprojet  );
	void Collationner( EnrgContexte &rtvaleur );
	EnrgDate LireDate();
    std::string LireCommentaire() const;

protected:
    
	virtual void FormaterDonnee();
	virtual void DeFormaterDonnee();

private:

    EnrgContexte	enrgcontexte;
    BlocContexte	enrgBCX;

    std::string     *pcheminprojet;
    std::string     cheminducontexte;
    DGChaineListe	tmplstprojet;

	void CreerCheminDeCeContexte();
	void CreerEnvironnementContexte();
    void DetruireContexte();
    void ViderEnrgContexte();
};

#endif // FBLOCCONTEXTE_H
