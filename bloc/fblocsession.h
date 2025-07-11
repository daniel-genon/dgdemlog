#ifndef FBLOCSESSIONMULTIAPP_H
#define FBLOCSESSIONMULTIAPP_H

#include "tmp_chemin_bibliodg.h"
#include "../source/structureappli.h"
/*
bloc LIST
taille liste
(
    bloc sess;
    taille bloc;
    (
        (
            balise = enrg;
            taille enrg;
            structure BlocSession
        )
        (
            ultérieurement autres valeurs
        )
    )
    etc... autre session // applications futures
)
*/
class FBlocSession : public FicBin
{
public:

    FBlocSession();

    bool EcrireSession();
    std::string NomDuProjet() const;
    std::string NomDuContexte() const;
    std::string NomUtilisateur() const;
    std::string NomConfiguration() const;
	void ChangerConfiguration( const std::string &valeur );
    
protected:
    EnrgSessionProjet enrgsespro, SVDenrgsespro, RESenrgsespro;
    
	bool LireSession();
	void AjouterContexte( const std::string &valeur );
   
	virtual void FormaterDonnee();
	virtual void DeFormaterDonnee();

private:

    BlocSession enrgB;
    std::string	utilisateursecours;
	 
    void ModifierDate();
    void ViderEnrgSession();
};

#endif // FBLOCSESSIONMULTIAPP_H
