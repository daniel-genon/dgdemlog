#ifndef STRUCTUREAPLI_H
#define STRUCTUREAPLI_H

//#define MTLIG  3 // nombre de ligne configurées dans enrgconnexion.h

#include "../bloc/utilficbinbloc.h"
#include "../tmpbibl/dgchaineliste.h"

#define TAILLEDATEDG  6

typedef uint8_t Chaine30[30];

#ifndef DEF_ChaineBalise
#define TAILLECHAINEBALISE 32 
struct ChaineBalise{
	uint8_t	v[TAILLECHAINEBALISE];
};
#define DEF_ChaineBalise
#endif

#ifndef DEF_ChaineCouleur
#define TAILLECHAINECOULEUR 18
struct ChaineCouleur{
	uint8_t	v[TAILLECHAINECOULEUR];
};
#define DEF_ChaineCouleur
#endif

#ifndef DEF_ChaineGrandNom
#define TAILLEGRANDECHAINE 254
typedef uint8_t Chaine254[TAILLEGRANDECHAINE];
struct ChaineGrandNom{
	Chaine254 v;
};
#define DEF_ChaineGrandNom
#endif

#ifndef DEF_ChaineNom
#define TAILLECHAINENOM 80
typedef uint8_t Chaine80[TAILLECHAINENOM];
struct ChaineNom{
	Chaine80	v;
};
#define DEF_ChaineNom
#endif

struct StrucCle
{
    uint32_t	taille;//4 octets taille du contenu
	ChaineBalise nom;
};
// struct CouleurBloc{	uint8_t coul[7];};
struct EnrgDate{
    uint16_t j;
    uint16_t m;
    uint16_t a;
};
struct EnrgProjet{
    EnrgDate    	dcreation;
    std::string		nom;
    std::string		commentaire;
	DGChaineListe	lstcontexte;
};
struct EnrgContexte{
    EnrgDate	dcreation;
    EnrgDate    dmodi;
    std::string	nom;
    std::string	commentaire;
    std::string	configuration;
};
struct EnrgSessionProjet{
    EnrgDate    	dmodifsession;
    EnrgProjet		projet;
    EnrgContexte	contexte;
    std::string		utilisateur;
};

/*
 Début des déclarations des structure des blocs pour formatage vers DGFicBloc
*/

struct BlocPolice{
    int16_t			hauteur;
    ChaineCouleur	couleur;
    ChaineGrandNom	nom;
};
struct DonneesLigne{
	ChaineNom		nom;
    ChaineCouleur	couleur;
    uint8_t			typeligne;
    uint8_t			epaisseur;
};
struct BlocRectangle
{
    uint16_t largeur;
    uint16_t hauteur;
};
struct BlocCouleurs
{
    ChaineCouleur coulbandeau;
    ChaineCouleur coulfond;
};
struct DonneesSurface
{
    BlocCouleurs couleur;
    BlocPolice police;
};
struct BlocSymbole{
    BlocRectangle	dimension;
	DonneesSurface	surface;
};
struct DonneesAncre{
    BlocSymbole		symbole;
    ChaineGrandNom	imicone;
};
struct DonneesGraphe
{
    uint8_t		idxpriorite;
    BlocSymbole	symbole;
	ChaineNom	libelle;// nom de la priorité
};
struct BlocAncre{
	StrucCle	clef;
    DonneesAncre	donnees;
};
struct BlocGraphLog
{
	StrucCle	clef;
	DonneesGraphe	donnees;
    uint8_t		connectable;//0 non 1 oui
    uint8_t		uniquerepresprio;//0 non 1 oui
};
struct BlocConnexion
{
	StrucCle		clef;
	DonneesLigne	valeurligne;
};
struct DonneesLogiciel
{
    ChaineGrandNom   imicone;
    ChaineGrandNom   phraide;
    ChaineGrandNom   dosproc;
    ChaineGrandNom   dependance;
    ChaineGrandNom   stdcfg;
    ChaineGrandNom   stdtrv;
    ChaineNom   options;
    ChaineNom	nomprocessus;
    ChaineNom	nomclair;
    ChaineNom	optcfg;
    ChaineNom	opttrv;
    uint8_t		delai;
    uint8_t		unique;
    uint8_t		classe;
};
struct DonneesConfig
{
    BlocPolice	police;
	ChaineNom	nom;
    BlocCouleurs couleurs;
    uint8_t		hticodessus;
    uint8_t		hticodroite;
    uint8_t		hticogauche;
};
struct DonneesContexteLiaison
{
    ChaineNom nom;// 80 cars max ( inutilisé actuellement )
    uint16_t  idxsource;// pour liaison : no du rang du source
    uint16_t  idxcible;// pour liaison : no du rang du cible
};
struct DonneesContexte
{
    double  posX;
    double  posY;
    double  posXcfg;
    double  posYcfg;
    double  posXtrv;
    double  posYtrv;
    uint8_t  idxpriorite;
    ChaineNom    nomclair;
    ChaineGrandNom    fictrv;
    ChaineGrandNom    ficcfg;
};
struct BlocLogiciel
{
	StrucCle	clef;
	DonneesLogiciel	donnees;
};
struct BlocConfig
{
	StrucCle	clef;
	DonneesConfig	donnees;
};
struct BlocObjetCTX
{
	StrucCle	clef;
	DonneesContexte	donnees;
};
struct BlocLiaisonCTX
{
	StrucCle	clef;
	DonneesContexteLiaison	donnees;
};
struct BlocContexte{
    EnrgDate    dcrea;
    EnrgDate    dmodi;
    Chaine80	nom;
    Chaine80	commentaire;
    Chaine80	configuration;
};
struct BlocProjet{
    Chaine80	nom;
    Chaine80	commentaire;
    EnrgDate	dcrea;
};
struct BlocSession{
    Chaine80	utilisateur;
    Chaine80	projet;
    Chaine80	contexte;
    EnrgDate    dmodi;
};

//struct SEnrgConfig
//{
    //std::string		nom;
    //DonneesConfig	donnees;
//};

/*
 Fin des déclarations des structures des blocs pour formatage vers DGFicBloc
*/


//struct EnrgDimFen{
//    int posx;
//    int posy;
//    int largeur;
//    int hauteur;
//};
#endif // STRUCTUREAPLI_H
