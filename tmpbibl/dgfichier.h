/*
dgfichier
Daniel Génon - 20.10.2015 - 08500 Revin
	  dgfichier est une bibliothèque de gestion de fichier

version 4.1 25.04.2024

Dans CMakeLists.txt :
    set(DOS_PER_INCLUSION "chemin dossier biblio entete /dgfichier.h" CACHE PATH "")
    set(BIB_DGFIC "chemin dossier biblio /libdgfichier.so" CACHE PATH "")

    target_link_libraries(... ${BIB_DGFIC} ...... )

dans les fichiers utilisateurs :
    #include "chemin dossier biblio entete/dgfichier.h"

   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué SANS AUCUNE GARANTIE.
Voir la licence GNU GPL pour plus de détails.

retour des erreurs

0000 : tout est ok.
1100 : impossible d'ouvrir le fichier.
1101 : impossible d'écrire (writeonly) dans le fichier.
1102 : impossible d'ajouter (append) dans le fichier.
1103 : l'adresse de la structure enregistrement ou chaîne texte nulle.
1104 : NBOCTET = 0.
1105 : le descripteur du fichier est nullptr.
1106 : la lecture du fichier est impossible.
1107 : le fichier n'est pas ouvert.
1108 : la fin du fichier est atteinte.
1109 : impossible de lire la ligne texte.
1110 : impossible d'écrire la ligne texte.
1111 : erreur d'index en lecture direct.
1112 : programmation : erreur d'appel de fonction virtuelle.
1113 : le fichier doit être ouvert et placé sur la position de l'enregistrement à remplacer/supprimer.
1114 : le fichier n'est pas ouvert en lecture.
1115 : impossible d'ouvrir le fichier en lecture/écriture.
1116 : position du point d'accès dans le fichier est inconnue.
1117 : la ligne texte est vide.
1118 : le repositionnement au début du fichier a échoué.
1119 : la suppression du fichier a échoué.
1120 : lecture direct impossible.
1121 : redimensionnement du fichier impossible.
1122 : le fichier existe.
1123 : impossible d'écrire l'enregistrement binaire.
1124 : taille du fichier invalide.
1125 : impossible d'écrire à la position seekp.
1126 : valeur expansion invalide (=<0)
1127 : chemin inexistant
1128 : impossible de lire à la position seekg.
1129 : le paramètre phrtest est vide;
*/

#ifndef GFICHIER_H
#define GFICHIER_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#ifndef VALEURTAMPON
 #define VALEURTAMPON 65535
#endif

//#define FLT_EVAL_METHOD 2

class FicBase : public std::fstream
{
public:
    FicBase();
    FicBase( const std::string &chemintotal );
    virtual ~FicBase();

    //// Réinitialisation
    void InitDescription( const std::string &dchemin,
							const std::string &dnom,
							const std::string &dextension );
    void InitDescription( const std::string &dchemin );//chemin sans nom ni extension
    bool InitDescTotal( const std::string &chemintotal );

    //// opération d'écriture
    uint16_t	Ecrire( bool ecraserfichier = false );// écrire
    uint16_t	ReEcrire();// écrire à l'emplacement actuel
    virtual uint16_t	Inserer();/*** insérer écrire à l'emplacement actuel
										le fichier est ouvert et le curseur
										pointer sur la ligne txt à décaler en-dessous
									***/
    virtual bool	EcrireEnContinu();// ecrire en suivant dans un fichier ouvert
	
    //// opération de lecture
    virtual uint16_t	Lire(uint32_t nenrg=0);
	virtual bool	LireEnContinu();
    //// autres operations
    uint16_t	CreerVide();
    bool		FichierExiste();
    bool 		CheminExiste();
    uint16_t	OuvrirEnLecture();
    uint16_t	OuvrirEnEcriture();
	bool		OuvrirEnREcriture();// ouvrir/écraser pour écrire en continu
	uint16_t	OuvrirEnLectureEcriture();
    void		FermerFichier();
    void		FermerFichierContinu();
    uint16_t	Supprimer();
	uint16_t	RetourErreur();
	bool		FichierVide();
	void		SupprimerFichier();

	bool	FichierTexte();
	bool	FichierBinaire();
	bool	FichierIFF();

    std::string CheminFichier() const;
    std::string NomFichier() const;
    std::string ExtensionFichier() const;
    std::string NomCompletFichier() const;
    
protected:
    uint64_t	nboretour;
    uint16_t	typerr;
    uint64_t	NBOCTET;
    uint8_t		typefichier;
    uint8_t		tampon[VALEURTAMPON];
    std::string	nomcomplet;

    
    void	NomFichier(const std::string &phrnom);
    void	ExtensionFichier(const std::string &phrext);
    void	CheminFichier(const std::string &phrchm);
    bool	CreerNomComplet();
	void	EffacerFichier();
	
	std::uintmax_t	TailleFichier();
	uint16_t		RenommerFichier( const std::string &nouveaunom );
	uint16_t		Inserer( const uint64_t valposition );/*** insérer écrire à l'emplacement indiqué
															le fichier est ouvert
														***/
	bool Retrecir( uint64_t adrdebut, uint64_t taille );
	bool Retrecir( uint64_t decalage );
	bool Etendre( const uint64_t decalage );
	void ModifierTaille( const uint64_t decalage, bool allonger = true );
	uint16_t IntegrerFichier( const std::string &vnomfichier, const uint64_t debutbloc, const uint64_t taillebloc, const uint64_t valposition );

	
	bool	LirePremierEnrg();
    virtual uint16_t  VerifierPTR();
    virtual uint16_t  PointerLigne( uint32_t noligne );
    virtual void EcrireValeur();
    virtual void ReEcrireValeur(bool suppression = false);
    virtual void LireValeur();
    virtual void IncrementLigne();

    virtual std::ios_base::openmode FlagOuvertureLecture();
    virtual std::ios_base::openmode FlagOuvertureEcraser();
    virtual std::ios_base::openmode FlagOuvertureAjouter();
    virtual std::ios_base::openmode FlagOuvertureLectureEcriture();
    
private:
    std::string	chemin;
    std::string	nom;
    std::string	extension;
    
    uint16_t LectureFichier();
};


class FicBin : public FicBase
{
public:
    uint64_t  posoctetadebutfic;//pointeur pour seek
 //   uint64_t  volumeexpansion;//taille pour expansion/retractation
    
    FicBin();
    virtual ~FicBin();

    void InitEnrg( char* aenrg, uint32_t lgenrg );
    void ViderEnrg();
    void ReinitEnrg( char* aenrg, uint32_t lgenrg );
    void ReinitEnrg( const std::string &nmfic,char* aenrg, uint32_t lgenrg );
    void InitAdrEnrg( char* aenrg );
    void InitLgrEnrg( uint32_t lgenrg );

protected:

	uint32_t	taillebloc;// taille du bloc data créer dans la classe supérieure
    std::string phrtest;// contient la phrase à trouver dans une recherche de texte de structure.

    bool    PointerOctetCible();
    bool    RePositionnerpointage( uint32_t valeur );//replacer le curseur par rapport à sa position +-valeur
	bool	ListerChaine( std::vector<std::string> *ptrlstchaine, char* adrdebut, uint16_t longzone );
	bool	ChercherChaine( char* adrdebut, uint16_t longzone );
	/**
	 * Initialiser phrtest dans l'appelant
	 * si OK, lenrg bloc est initialisé : faire un DeFormaterDonnee dans l'appelant.
	**/
    
    virtual uint16_t	VerifierPTR();
    virtual void	EcrireValeur();
    virtual void	ReEcrireValeur( bool suppression = false );
    virtual void	LireValeur();
    virtual void	FormaterDonnee();
    virtual void	DeFormaterDonnee();
	virtual void	AjouterDonneeVersListe();

    virtual std::ios_base::openmode FlagOuvertureLecture();
    virtual std::ios_base::openmode FlagOuvertureEcraser();
    virtual std::ios_base::openmode FlagOuvertureAjouter();
    virtual std::ios_base::openmode FlagOuvertureLectureEcriture();

    void ConvStrVersBin( const std::string &phr , void *memdestinataire, uint32_t lgchaine = 0 );

private:

    char    *adrenrg;

    uint16_t VerifierAdr();

};

class FicTexte : public FicBase
{
public:

    FicTexte();
    virtual ~FicTexte();

    std::string LireChaine();
    virtual uint16_t Inserer();/*** insérer écrire à l'emplacement actuel
										le fichier est ouvert et le curseur
										pointer sur la ligne txt à décaler en-dessous
								***/
								
    virtual void StockerChaine( const std::string &phr );

protected:

	uint16_t EcrireValeur( const std::string &phr );

    virtual uint16_t  PointerLigne( uint32_t noligne );
    virtual void EcrireValeur();
    virtual void LireValeur();
    virtual void ReEcrireValeur(bool suppression = false);
    virtual void IncrementLigne();

    virtual std::ios_base::openmode FlagOuvertureLecture();
    virtual std::ios_base::openmode FlagOuvertureEcraser();
    virtual std::ios_base::openmode FlagOuvertureAjouter();
    virtual std::ios_base::openmode FlagOuvertureLectureEcriture();


private:
	std::string	tamponstr;
    uint32_t lignepointee;

};


#endif /* GFICHIER_H */ 
