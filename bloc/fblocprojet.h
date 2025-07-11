#ifndef FBlocProjet_H
#define FBlocProjet_H

#include "fbloccontexte.h"

class FBlocProjet : public FicBin
{
public:

    FBlocProjet();
	virtual ~FBlocProjet();

//public acces projet
    bool CreerLeProjet(const EnrgProjet &venrgprojet);
    void Lister( DGChaineListe &lstvaleur );
    bool EcrireProjet();
    bool LireProjet( const std::string &valeur );
    bool LirePremierProjet();
    std::string LireCommentaire() const;
    std::string Nom() const;
	struct tm *LireDate() const;
   
//public acces contexte
    void ListerContexte( DGChaineListe &lstvaleur );
    bool EcrireContexte( const EnrgContexte &valeurctx );
    bool LirePremierContexte();
    bool LireContexte( const std::string &valeur );
    std::string LireComContexte() const;
	struct tm *LireDateContexte();
	
//public acces projet et contexte
	void Collationner( EnrgSessionProjet &rtenrgsession );


protected:
	virtual void FormaterDonnee();
	virtual void DeFormaterDonnee();

private:
    std::string	*pChRacineMApp;
    std::string cheminduprojet;
    
    BlocProjet	enrgB;
	EnrgProjet	enrgprojet;

    FBlocContexte   fichiercontexte;

    void CreerCheminDeCeProjet();
    void CreerEnvironnementProjet();
    void DetruireProjet();
    void ViderEnrgprojet();
};

#endif // FBlocProjet_H
