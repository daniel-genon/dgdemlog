#ifndef DGFICBlOC_H
#define DGFICBlOC_H
/*************************************
dgfichier
Daniel Génon - 20.10.2015 - 08500 Revin
	  dgficbloc est une bibliothèque de gestion de fichier bloc de type IFF

version 4.1 du 25.04.2024

Dans CMakeLists.txt :
    set(DOS_PER_INCLUSION "chemin dossier biblio entete /dgficbloc.h" CACHE PATH "")
    set(BIB_DGFICBLOC "chemin dossier biblio /libdgficbloc.so" CACHE PATH "")

    target_link_libraries(... ${BIB_DGFICBLOC} ...... )

dans les fichiers utilisateurs :
    #include "chemin dossier biblio entete/dgficbloc.h"

   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué SANS AUCUNE GARANTIE.
Voir la licence GNU GPL pour plus de détails.

* Exemple de structure fichier type BLOC
entete
	*PACK <nom unique>
		*ENR1 <nom unique dans le pack>
			enrg01 
			enrg03
			enrg02
			enrg01 
			enrg03
			enrg02
			enrg02
			enrg02
		*ENR2 <nom unique dans le pack>
			enrg
			enrg
		*ENR3 <nom unique dans le pack>
			enrg
			enrg
	*PICK <nom unique>
		*PECK
			enrg
			enrg
			enrg
	*POCK <nom unique>
		*ENR2
			enrg
			enrg
			* 
			* 
-----Entete du fichier : (EnrgEntete)
BLOC						-  8 octets -> désignation
type du fichier				-  8 octets -> ( TRUC ... )
-----Entete d'un PACK : 
	taille contenu de l'amas	-  8 octets
	nom							-  4 octets -> nom standard de début d'une liste de PAQUET
-----Entete d'un ENRG : 
		taille contenu du pack	-  2 octets
		nom						-  4 octets
-----Enregistrement d'un d'une structure
			nom						-  8 octets
			taille totale contenu	-  4 octets
				<contenu>	-  n octets

codes messages erreurs à destination du programmeur pour le traitement vers l'utilisateur
1301 fichier inconnu
1302 problème de lecture
1303 n'est pas fichier bloc souhaité
1304 pas de balise trouvée 
1305 la taille du nom de Bloc est nulle.
1306 la taille du nom de Part est nulle.
1307 la taille du nom de Structure est nulle.
1308 
1309 l'adresse de Part est hors limite adresse fin Bloc
1310 adresse adrblocdata nulle
1311 le bloc existe
1312 le bloc n'existe pas
1313 éléments de la liste position ENRG > nombre de ENRG.
1314 le part existe
1315 le part n'existe pas
1316 la struc n'existe pas

**************************************/
#include <stack>
#include "dgfichier.h"

#ifndef DEF_ChaineBalise
#define TAILLECHAINEBALISE 32 
struct ChaineBalise{
	uint8_t	v[TAILLECHAINEBALISE];
};
#define DEF_ChaineBalise
#endif

struct Enrgstruc
{
    uint32_t	taille;;//4 octets taille du contenu
	ChaineBalise nom;
};

class DGFicBloc  : public FicBin
{
public:
    DGFicBloc();
    virtual ~DGFicBloc();
    
    void CreerLeFichier();
	bool CreerUnFichierAvecPart();
/**
 * Modifications du 21 04 2024
 * suppression des pack/enrg
 * mise en oeuvre des bloc/part avec des noms limité à 32 cars pour les blocs et part et structure
**/	
	bool CreerUnBloc( const std::string &nombloc );
	bool CreerUnPart( const std::string &nombloc, const std::string &nompart );
    bool CreerLaStruc( const std::string &nombloc, const std::string &nompart, const std::string &nomsturc );

	uint16_t ModifierStructure( int32_t norang );

	virtual uint16_t Lire( const std::string &nombloc, const std::string &nompart, const std::string &nomstruc, uint32_t norang = 0 );
	virtual uint16_t LirePremierBloc();
	virtual uint16_t LirePremiereStructure();
	virtual uint16_t LirePositionStructure( const std::string &nombloc, const std::string &nompart, const std::string &nomstruc );
	uint16_t LireStructure( int32_t norang );
	


	bool ListerLesBlocs( std::vector<std::string> *ptrlstchaine );
	bool ListerLesParts( const std::string &nombloc, std::vector<std::string> *ptrlstchaine );
	
    uint64_t TailleDuBloc();

/**
 * initialiser phrtest avec la chaine à trouver
 * la position de la structure sera indiquée dans rtnumstruc
**/
	bool ChercherTexte( const std::string &ptrchainestock, const uint16_t pospack = 0, const uint16_t posenrg = 0 );
/**
 * Si utilisation de ModifierLaStruc alors que la structure n'existe pas (nouvelle structure) :
**/
	void AutoriserCreationEnModification();
	void InterdireCreationEnModification();// valeur par défaut à réinitialiser impérativement après une autorisation
	
protected:

	struct Enrg64
	{
		uint64_t	taille;//8 octets taille du contenu
		ChaineBalise	nom;//le nom de la balise ou type de fichier stocké sur 4 octets
	};
	struct EnrgEntete
	{
		uint64_t	type;//le nom de la balise stockés sur 8 octets
		uint64_t	genre;//8 octets taille du contenu 
	};

	struct Adresse{
		uint64_t	debut;
		uint64_t	fin;
		uint64_t	finpaquet;
		uint64_t	limite;
	};

	EnrgEntete	entetefichier;
    uint8_t		tailletetestruc;

	ChaineBalise	nomblocencours, nompartencours, nomstrucencours;	
	
	bool CreerUnBloc();
	bool CreerUnPart();
    bool CreerLaStruc();
	bool BlocExiste();
	bool AjusterTailleBloc( const Adresse adrblocrectifie, uint64_t dimdifference, bool sens );
	void InitBlocData( char *vadrpart, uint32_t vtaille );
	bool CvtChaineEnBalise( const std::string &vchaine, ChaineBalise *rtbalise );
	bool ModifierStruc();
    uint64_t TailleDuBlocTrouve();
    void AdresseBlocTrouve( Adresse *valret );
    uint16_t TaillePartEnCours( uint64_t &rettaille );
    void AdressePartTrouve( Adresse *valret );
	uint16_t LireStructureDePartEnContinu();

	virtual void InitHierarchie();
    virtual void FormaterDonnee();
    virtual void DeFormaterDonnee();
	virtual void AjouterDonneeVersListe();
    
    uint32_t rtnumstruc;// contient la position de la structure trouvée dans une recherche.
	
private:
/**
 * variables fixes générales initialisées à la construction
**/    
	bool	modeokcreer;
    char	*adrstruc;
    uint8_t	tailleenrgbloc;
    uint8_t	tailleenrgpart;
    uint8_t	tailleentete;
    uint8_t	tailleadresse;
    uint32_t	taillestruc;
    EnrgEntete	entete;
    ChaineBalise	balisevide;
/**
 * variables paramètres discrets entre membres
**/    
    Enrg64	blocbloc;
    Enrg64	blocenrg;
    Adresse	adrbloc;
    Adresse	adrpart;
	Enrgstruc	rtvaleurtmp;

    int64_t	tailledata;
    
    std::stack<uint16_t> listeposmarque;
    std::stack<uint64_t> stocadrmaj;
    
    uint8_t indicemaxi;
    uint32_t norangstruc;
    
/**
 * variables d'utilisation internes aux membres à ne jamais utiliser en paramètres entre membres
**/    
    unsigned char tamponchaine[2048];
	uint16_t	pospackencours;
/***/

	Adresse adrbloctrv;	/** contient les valeurs position du bloc dernièrement
							trouvé dans une recherche ou nouvellement crée vide.**/
	Adresse adrparttrv;	/** contient les valeurs position du part dernièrement
							trouvé dans une recherche ou nouvellement crée vide.**/

    void InitEnrgBloc( bool raz = false );
    void InitEnrgPart( bool raz = false );
    void RazBloc();
	void RazPart();
	void NettoyerStocAdrMaj();
    void Razadrbloc();
    void Razadrpart();

    void EcrireEntete();
	bool CreerBloc();
	bool CreerPart();
	bool CreerStruc();
   
//	bool SupprimerStruc();
    uint16_t LireEntete();
	uint16_t LireStructure();
	bool TrouverBloc();
	uint16_t TrouverPart();
	uint16_t TrouverStruc();
//	uint16_t TrouverBlocRang();
   	bool PointerStruc();
   	
	void MajTailleMarque();
	
};
#endif // DGFICBlOC_H
