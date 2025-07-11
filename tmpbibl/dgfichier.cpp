/*
* gfichier.cpp
* v 4.1
*/

#include "dgfichier.h"

FicBase::FicBase()
{
	typerr=0;
}
FicBase::FicBase( const std::string &chemintotal )
{
	typerr=0;
	InitDescTotal( chemintotal );
}
FicBase::~FicBase()
{
    if( !nomcomplet.empty() ) FermerFichier();
}
void FicBase::InitDescription( const std::string &dchemin,  const std::string &dnom,
								const std::string &dextension )
{
	nomcomplet.clear();
	chemin	= dchemin;
	std::string test = &chemin.back();
	if((test == "/") || (test == "\\"))
		chemin.pop_back();
	int32_t pospnt = dnom.find_last_of(".");
	if(pospnt != -1)
	{
		extension	= dnom.substr(pospnt+1);
		nom			= dnom.substr(0,pospnt);
		nomcomplet	= chemin+"/"+nom+"."+extension;
	}
	else
	{
		nom	= dnom;
		nomcomplet	= chemin+"/"+nom;
		if(dextension.size()!=0)
			extension	= dextension;
		if(extension.size()!=0)
			nomcomplet	= nomcomplet+"."+extension;
	}
}
void FicBase::InitDescription( const std::string &dchemin )
{
	chemin	= dchemin;
	std::string test = &chemin.back();
	if((test == "/") || (test == "\\"))
		chemin.pop_back();
	if(nom.size()!=0)
	{
		nomcomplet	= chemin+"/"+nom;
		if(extension.size()!=0)
			nomcomplet	= nomcomplet+"."+extension;
	}
	else
		nomcomplet	= chemin+"/";
}
bool FicBase::InitDescTotal( const std::string &chemintotal )
{
	nomcomplet = chemintotal;
	std::size_t position = chemintotal.find_last_of("/\\");
	if( position==std::string::npos ) return false;
	chemin = chemintotal.substr(0,position);
	nom = chemintotal.substr(position+1);
	position = nom.find_last_of(".");
	if( position!=std::string::npos )
	{
		extension = nom.substr(position+1);
		nom = nom.substr(0,position);
	}
	else
		extension.clear(); 
		
	return true;
}
uint16_t FicBase::CreerVide()
{
    typerr = 1104;
    if( !nomcomplet.empty() )
    {
		typerr = 1100;
		open( nomcomplet.data(), FlagOuvertureEcraser() );
		if(is_open())
		{
			close();
			typerr = 0;
		}
     }
    return typerr;
}
uint16_t  FicBase::Ecrire( bool ecraserfichier )
{
    if( (typerr = VerifierPTR()) == 0 )
    {
        uint16_t reterr = 0;
        if(ecraserfichier)
        {
            reterr = 1101;
            open( nomcomplet.data(), FlagOuvertureEcraser() );
        }
        else
        {
            reterr = 1102;
            open( nomcomplet.data(), FlagOuvertureAjouter() );
        }
        if(is_open())
        {
            typerr = reterr;
            EcrireValeur();
        }
        else typerr = 1100;
        close();
    }
    return typerr;
}
uint16_t  FicBase::ReEcrire()
{
	typerr = 1113;
	if(is_open())
	{
		typerr = 1114;
		if(FichierTexte())
			ReEcrireValeur();
		else
		{
			long posenrg = tellg();
			if(posenrg!=-1)
			{
				uint32_t pointdacces = posenrg-NBOCTET;
				close();
				typerr = 1115;
				open( nomcomplet.data(), FlagOuvertureLectureEcriture());
				if(is_open())
				{
					typerr = 1116;
					if(seekg(pointdacces))
						ReEcrireValeur();
				}
			}
		}
		close();
	}
    return typerr;
}
uint16_t FicBase::Inserer()
{
	typerr = 1114;
	if(is_open())
	{
		int32_t posenrg = tellg();
		if(posenrg!=-1)
			typerr = Inserer( posenrg-NBOCTET );
		else
			typerr = 1116;
	}
	return typerr;
}

uint16_t FicBase::Inserer( const uint64_t valposition )
{
	typerr = 0;
	std::uintmax_t position = valposition;
	std::uintmax_t lgfichier	= std::filesystem::file_size( nomcomplet.data() );
	if( position < lgfichier )
	{
		typerr = 1115;
		seekg(position);
		if(good())
			Etendre( NBOCTET );
	}
	else
		position = lgfichier;
	if(typerr==0)
	{
		seekp(position);
		if(!good())
		{
			if(!eof())	typerr = 1125;
			clear();
		}
		if(typerr==0) EcrireValeur();
	}
	return typerr;
}
bool FicBase::Retrecir( uint64_t adrdebut, uint64_t taille )
{
	if(OuvrirEnLectureEcriture()==0)
	{
		seekg( adrdebut );
		if(good())
		{
			bool okraccourci = Retrecir( taille );
			FermerFichier();
			if( okraccourci )
				ModifierTaille( taille, false );
		}
	}
	FermerFichier();
	return typerr==0;
}
bool FicBase::Retrecir( uint64_t decalage )
{
/**
 initialisations préalables et impératives :
	* fichier ouvert lecture/ecriture
	* curseur seekg placé au point début de la partie à supprimer
En In/Out tellp et tellg donne le même résultat, ils font référence au même curseur.
Si bien qu'utiliser seekg ou seekp donne le même résultat, mais pour des raisons pratiques
et lisibles nous utiliserons seekp pour du write et seekg pour du read
	* 
	* 
**/
	typerr = 1115;
	uint64_t curseur = tellg();
	std::uintmax_t total	= std::filesystem::file_size( nomcomplet.data() );
	std::uintmax_t paquet	= total - curseur - decalage;
	uint16_t nbpaquet		= paquet / VALEURTAMPON;
	uint64_t restepaquet	= paquet -( nbpaquet * VALEURTAMPON );
	typerr = 0;
	curseur += decalage;
	for( uint16_t i=0; i<nbpaquet; i++ )
	{
		seekg(curseur);
			if( !good() ){	typerr = 1116;	break;	}
		read((char *)&tampon[0], VALEURTAMPON );
			if( !good() ){  typerr = 1120;  break;  }
		seekp(curseur-decalage);
			if( !good() ){	typerr = 1116;	break;	}
		write((char *)&tampon[0], VALEURTAMPON );
			if( !good() ){	typerr = 1125;	break;	}
		curseur += VALEURTAMPON + decalage;
	}
	if((typerr==0) && (restepaquet>0))
	{
		seekg(curseur);
		if( good() )
		{
			read((char *)&tampon, restepaquet );
			if(good())
			{
				seekp(curseur-decalage);
				write((char *)&tampon[0], restepaquet );
				if(!good())	typerr=1125;
			}
			else
				typerr = 1120;
		}
		else
			typerr = 1116;
	}
    return typerr==0;
/**
 * En sortie si OK :
	* fichier rétreci mais taille totale à mettre à jour après fermeture car ici toujours ouvert
	* position curseurs seekg et seekp incertaines 
**/
}
bool FicBase::Etendre( uint64_t decalage )
{
/**
 * initialisations préalables et impératives :
	* fichier ouvert lecture/ecriture
	* curseur seekg placé au point début de la partie à supprimer
En In/Out tellp et tellg donne le même résultat, ils font référence au même curseur.
Si bien qu'utiliser seekg ou seekp donne le même résultat, mais pour des raisons pratiques
et lisibles nous utiliserons seekp pour du write et seekg pour du read
	* 
	* 
**/
	uint64_t curseur = tellg();
	std::uintmax_t total	= std::filesystem::file_size( nomcomplet.data() );
	std::uintmax_t paquet	= total - curseur;
	uint16_t nbpaquet		= paquet / VALEURTAMPON;
	uint64_t restepaquet	= paquet -( nbpaquet * VALEURTAMPON );
	curseur	= total;
	typerr = 0;
	for( uint16_t i=0; i<nbpaquet;i++ )
	{
		curseur -= VALEURTAMPON;
		seekg(curseur);
			if( !good() ){	typerr = 1116;	break;	}
		read((char *)&tampon[0], VALEURTAMPON );
			if( !good() ){  typerr = 1120;  break;  }
		seekp(curseur+decalage);
			if( !good() ){	typerr = 1116;	break;	}
		write((char *)&tampon[0], VALEURTAMPON );
			if( !good() ){	typerr = 1125;	break;	}
	}
	if((typerr==0) && (restepaquet>0))
	{	
		curseur -= restepaquet;	
		seekg(curseur);
		if( good() )
		{
			read((char *)&tampon[0], restepaquet );
			if(good())
			{
				seekp(curseur + decalage);
//				int toto = tellg();
				write((char *)&tampon[0], restepaquet );
				if(!good())	typerr=1125;
			}
			else
				typerr = 1120;
		}
		else
			typerr = 1116;
	}
    return typerr==0;
/**
 * En sortie si OK :
	* fichier allonger et toujours ouvert
	* considérer que les positions curseurs seekg et seekp sont incertaines 
**/
}
void FicBase::ModifierTaille( const uint64_t decalage, bool allonger )
{
	if(is_open()) close();
	std::uintmax_t nouvelletaille = std::filesystem::file_size( nomcomplet.data() );
	if( allonger )
		nouvelletaille+=decalage;
	else
	{
		if(nouvelletaille>decalage)
			nouvelletaille-=decalage;
		else
			nouvelletaille=1;
	}
	std::filesystem::resize_file( nomcomplet.data(), nouvelletaille );
}
uint16_t FicBase::IntegrerFichier( const std::string &vnomfichier, const uint64_t debutbloc, const uint64_t taillebloc, const uint64_t valposition )
{
/**
 * le fichier réception doit être ouvert en écriture, étendu ou raccourci avant l'integration
**/
//iostate toto = rdstate();
	typerr = 1105;
	if( !vnomfichier.empty() )
	{
		FicBase *pficfusion = new FicBase;
		typerr = 1105;
		if( pficfusion->InitDescTotal(vnomfichier) )
		{
			if( pficfusion->OuvrirEnLecture()==0 )
			{
				typerr = 0;
					uint64_t posecrire	= valposition;
					uint64_t poslire	= debutbloc;
					uint64_t paquet		= taillebloc;
					while( paquet>VALEURTAMPON && typerr==0 )
					{
						typerr = 1116;
						pficfusion->seekg(poslire);
						if(pficfusion->good())
						{
							typerr = 1120;
							pficfusion->read( (char*)&tampon[0], VALEURTAMPON );
							typerr = 1116;
							seekp(posecrire);
							if(good())
							{
								typerr = 1125;
								write( (char*)&tampon[0], VALEURTAMPON );
								if(good())
								{
									typerr = 0 ;
									paquet	-=VALEURTAMPON;
									posecrire +=VALEURTAMPON;
								}
							}
						}
					}
					if(typerr==0)
					{
						if(paquet>0)
						{
							typerr = 1116;
							pficfusion->seekg(poslire);
							if(pficfusion->good())
							{
								typerr = 1120;
								pficfusion->read( (char*)&tampon[0], paquet );
								if(pficfusion->good())
								{
									typerr = 1116;
									seekp(posecrire);
									if(good())
									{
										typerr = 1120;
										write( (char*)&tampon[0], paquet );
										if( good()) typerr = 0 ;
									}
								}
							}
						}
					}
			}
			pficfusion->FermerFichier();
		}
		delete pficfusion;
	}
	return typerr;
}
bool FicBase::EcrireEnContinu()
{
    typerr = 1123;
    EcrireValeur();
    return typerr==0;
}
uint16_t FicBase::OuvrirEnLecture()
{
	typerr = 1100;
	open( nomcomplet.data(), FlagOuvertureLecture() );
	if(is_open()) typerr = 0;
	return typerr;
}
uint16_t FicBase::OuvrirEnEcriture()
{
	typerr = 1100;
	open( nomcomplet.data(), FlagOuvertureAjouter() );
	if(is_open()) typerr = 0;
	return typerr;
}
bool FicBase::OuvrirEnREcriture()
{
	if(VerifierPTR()==0)
	{
		open( nomcomplet.data(), FlagOuvertureEcraser() );
		if(is_open()) return true;
	}
    return false;
}
uint16_t FicBase::OuvrirEnLectureEcriture()
{
	if(VerifierPTR()==0)
	{
		typerr=1115;
		if(is_open()) close();
		open( nomcomplet.data(), FlagOuvertureLectureEcriture() );
		if(is_open()) typerr = 0;
	}
	return typerr;
}
void FicBase::FermerFichier()
{
	if(is_open()) close();
}
void FicBase::FermerFichierContinu()
{
    FermerFichier();
}
bool FicBase::LirePremierEnrg()
{
	if(OuvrirEnLecture()==0)
	{
		Lire(1);
	}
	FermerFichier();
	return typerr == 0;
}
uint16_t  FicBase::Lire( uint32_t nenrg )
{
    if( (typerr = VerifierPTR()) == 0 )
    {
        typerr = 1107;
        if(is_open())
        {
            if(nenrg==0)
            {
                typerr = LectureFichier();
            }
            else
            {
                if(FichierTexte())
                {// nenrg commence à 1, pas à 0
                    if(PointerLigne(nenrg)==0)
                        seekg(0);
                }
                else
                {
                    nenrg--;
                    uint32_t posoctetadebutfic = (nenrg*NBOCTET);
                    typerr = 1111;
                    seekg( posoctetadebutfic );
                    if(good())
                        typerr = LectureFichier();
                }
            }

        }
    }
    return typerr;
}
bool FicBase::LireEnContinu()
{
	LireValeur();
    return typerr==0;
}
uint16_t FicBase::Supprimer()
{
    typerr = 1113;
    if(is_open())
    {
        typerr = 1114;
		if(FichierTexte())
			ReEcrireValeur( true );
		else
		{
			long posenrg = tellg();
			if(posenrg!=-1)
			{
				long pointdacces = posenrg-NBOCTET;
				close();
				
				open( nomcomplet.data(), FlagOuvertureLectureEcriture());
				if(is_open())
				{
					
					seekg(pointdacces);
					if(good())
						ReEcrireValeur( true );
					else
						typerr = 1116;
				}
				else
				    typerr = 1115;
			}
		}
		close();
    }
    return typerr;
}
bool FicBase::FichierExiste()
{
	typerr = 1105;
	if(std::filesystem::exists(nomcomplet.data()))
		typerr = 0;
	return typerr==0;
}
bool FicBase::CheminExiste()
{
	typerr = 1127;
	if(std::filesystem::exists(chemin.data()))
		typerr = 0;
	return typerr==0;
}
std::uintmax_t FicBase::TailleFichier()
{
	if(VerifierPTR()==0)
		return std::filesystem::file_size( nomcomplet.data() );
	 else
		return 0;
}
bool FicBase::FichierVide()
{
	return TailleFichier()==0;
}
uint16_t FicBase::VerifierPTR()
{
    //typerr = 0;
    //if(nomcomplet.empty()) typerr = 1105;
    //return typerr;
    if(nomcomplet.empty())
		return typerr=1105;
	else
		return typerr=0;
}
uint16_t FicBase::LectureFichier()
{
    if(eof())
    {
        typerr = 1108;
        close();
    }
    else
    {
		IncrementLigne();
        typerr = 1106;
        LireValeur();
    }
    return typerr;
}
bool FicBase::FichierTexte()
{
	return typefichier==1;
}
bool FicBase::FichierBinaire()
{
	return typefichier==0;
}
bool FicBase::FichierIFF()
{
	return typefichier==2;
}
std::string FicBase::CheminFichier() const
{
    return chemin;
}
std::string FicBase::NomFichier() const
{
    return nom;
}
std::string FicBase::ExtensionFichier() const
{
    return extension;
}
std::string FicBase::NomCompletFichier() const
{
	//if( !CreerNomComplet() ) return std::string("");
	return nomcomplet;
}

void FicBase::NomFichier(const std::string &phrnom)
{
	nom = phrnom;
	CreerNomComplet();
}
void FicBase::ExtensionFichier(const std::string &phrext)
{
	extension = phrext;
	CreerNomComplet();
}
void FicBase::CheminFichier(const std::string &phrchm)
{
	chemin = phrchm;
	CreerNomComplet();
}
bool FicBase::CreerNomComplet()
{
	if(nom.empty()) return false;
	if(!chemin.empty())
		nomcomplet	= chemin;
	nomcomplet = nomcomplet + "/" + nom;
	if(!extension.empty())
		nomcomplet = nomcomplet +"."+extension;
	return true;
}

uint16_t FicBase::RetourErreur()
{
/**
 Futur : développement retour msg texte
**/
	return typerr;
}
void FicBase::SupprimerFichier(){ EffacerFichier(); }//fonction public
void FicBase::EffacerFichier()// fonction protected
{
	if(FichierExiste())
		std::filesystem::remove( nomcomplet.data() );
}
uint16_t FicBase::RenommerFichier( const std::string &nouveaunom )
{
	if(FichierExiste())
	{
		typerr = 1122;
		if(!std::filesystem::exists(nouveaunom.data()))
		{ 
			std::filesystem::rename( nomcomplet.data(), nouveaunom.data());
			nomcomplet = nouveaunom;
			typerr = 0;
		}
	}
	return typerr;
}
void FicBase::EcrireValeur(){typerr = 1112;}
void FicBase::ReEcrireValeur( bool suppression ){typerr = 1112;}
void FicBase::LireValeur(){typerr = 1112;}
uint16_t  FicBase::PointerLigne( uint32_t noligne ){ return 1112;}
void FicBase::IncrementLigne(){typerr = 1112;}
std::ios_base::openmode FicBase::FlagOuvertureLecture(){typerr = 1112; return (std::ios_base::out | std::ios_base::in);}
std::ios_base::openmode FicBase::FlagOuvertureEcraser(){typerr = 1112; return (std::ios_base::out | std::ios_base::in);}
std::ios_base::openmode FicBase::FlagOuvertureAjouter(){typerr = 1112; return (std::ios_base::out | std::ios_base::in);}
std::ios_base::openmode FicBase::FlagOuvertureLectureEcriture(){typerr = 1112; return (std::ios_base::out | std::ios_base::in);}

FicBin::FicBin()
{
    adrenrg     = nullptr;
    NBOCTET     = 0;
    typefichier	= 0;
    taillebloc	= 0;
    phrtest.clear();
}
FicBin::~FicBin(){}
void FicBin::InitEnrg( char* aenrg, uint32_t lgenrg )
{
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}
void FicBin::InitAdrEnrg( char* aenrg ){ adrenrg = aenrg; }
void FicBin::InitLgrEnrg( uint32_t lgenrg ){ NBOCTET = lgenrg; }
void FicBin::ReinitEnrg( const std::string &nmfic,char* aenrg, uint32_t lgenrg )
{
    NomFichier(nmfic);
    ReinitEnrg( aenrg, lgenrg );
}

void FicBin::ReinitEnrg( char* aenrg, uint32_t lgenrg )
{
    adrenrg = aenrg;
    NBOCTET = lgenrg;
}
void FicBin::EcrireValeur()
{
//    iostate titi = rdstate();
	typerr = 1123;
    write( adrenrg, NBOCTET );
//    iostate tata = rdstate();
    if( good()) typerr = 0;
}
void FicBin::ReEcrireValeur( bool suppression )
{
    if(suppression)
    {
		long posenrg = tellg();
		typerr=1116;
		if(posenrg!=-1)
		{
			std::uintmax_t tailleactuelle = std::filesystem::file_size( nomcomplet.data() );
			seekg(posenrg+NBOCTET);
			if(good())
			{	
				do{	
					LireValeur();
					if(typerr == 0)
					{
						seekg(posenrg);
						EcrireValeur();
						posenrg += NBOCTET;
						seekg(posenrg+NBOCTET);
					}
					else
					{
						if(typerr == 1108) typerr = 0;
						break;
					}
				}while( typerr==0 and good() );
			}
			close();
			if(typerr==0)
				std::filesystem::resize_file( nomcomplet.data(), tailleactuelle-NBOCTET);
		}
    }
    else
        EcrireValeur();
}
void FicBin::LireValeur()
{
	typerr = 0;
    read( adrenrg, NBOCTET );
    nboretour = gcount();
    if( nboretour < NBOCTET )
		typerr = 1106;
	if( nboretour == 0 )
		typerr = 1108;
}
bool FicBin::PointerOctetCible()
{
	typerr = 1111;
	seekg( posoctetadebutfic );
	if(good()) typerr = 0;
	return typerr==0;
}
bool FicBin::RePositionnerpointage( uint32_t valeur )
{
	long posenrg = tellg();
	if(posenrg==-1) return false;
	posoctetadebutfic = posenrg+valeur;
	if(posoctetadebutfic<0)
		posoctetadebutfic=0;
    return PointerOctetCible();
}
uint16_t FicBin::VerifierPTR()
{
    uint16_t reterr =  VerifierAdr();
    if(reterr!=0) return reterr;
    return FicBase::VerifierPTR();
}
uint16_t FicBin::VerifierAdr()
{
    if( adrenrg  == nullptr ) return 1103;
    if( NBOCTET  == 0 ) return 1104;
    return 0;
}
void FicBin::ViderEnrg()
{
    if(VerifierAdr()==0)
        memset(adrenrg,0,NBOCTET);
}
bool FicBin::ListerChaine( std::vector<std::string> *ptrlstchaine, char* adrdebut, uint16_t longzone )
{
//iostate titi = rdstate();
	if(OuvrirEnLecture()==0)
	{
		typerr = 1128;
		posoctetadebutfic = 0;
		seekg(posoctetadebutfic);
		if(good())
		{
			std::string tmpphr( longzone, ' ' ) ;
			while(LireEnContinu())
			{
				memcpy( tmpphr.data(), adrdebut, longzone);
				ptrlstchaine->push_back( std::string( (char *)tmpphr.data() ));
				posoctetadebutfic += NBOCTET;
				seekg(posoctetadebutfic);
				if(!good()) break;
			}
			if(ptrlstchaine->size()>0)
				typerr = 0;
			else
				typerr = 1312;
		}
		clear();
	}
	FermerFichier();
	return typerr == 0;
}
bool FicBin::ChercherChaine( char* adrdebut, uint16_t longzone )
{
	typerr = 1129;
	if(phrtest.empty()) return false;
	if(OuvrirEnLecture()==0)
	{
		typerr = 1128;
		posoctetadebutfic = 0;
		ViderEnrg();
		bool tourne = true;
		std::string tmpphr( longzone, ' ' ) ;
		do{
			tourne = false;
			seekg( posoctetadebutfic );
			if(good())
			{
				LireValeur();
				if(typerr==0)
				{
					memcpy( tmpphr.data(), adrdebut, longzone);
					if( phrtest.compare(std::string( (char *)tmpphr.data()) )!=0 )
					{
						posoctetadebutfic += NBOCTET;
						tourne = true;
					}
				}
			}
			else
				typerr=1128;
		}while(tourne);
		clear();
	}
	FermerFichier();
    return typerr==0;
}


std::ios_base::openmode FicBin::FlagOuvertureLecture(){    return ( std::ios_base::in  | std::ios_base::binary );}
std::ios_base::openmode FicBin::FlagOuvertureEcraser(){    return ( std::ios_base::out | std::ios_base::binary );}
std::ios_base::openmode FicBin::FlagOuvertureAjouter(){    return ( std::ios_base::app | std::ios_base::binary );}
std::ios_base::openmode FicBin::FlagOuvertureLectureEcriture(){    return ( std::ios_base::in  | std::ios_base::out | std::ios_base::binary );}
void FicBin::ConvStrVersBin(  const std::string &phr , void *memdestinataire, uint32_t lgchaine )
{
    uint32_t taille = phr.size();
    if(lgchaine!=0)
    {
        if(taille>lgchaine)
            taille=lgchaine;
    }
    memcpy( memdestinataire, phr.data(), taille);// attention pour unicode, taille*2
}
void FicBin::FormaterDonnee(){typerr = 1112;}
void FicBin::DeFormaterDonnee(){typerr = 1112;}
void FicBin::AjouterDonneeVersListe(){typerr = 1112;}


FicTexte::FicTexte()
{
    lignepointee    = 0;
    typefichier		= 1;
    tamponstr.clear();
}
FicTexte::~FicTexte(){}
void FicTexte::StockerChaine(  const std::string &phr  )
{
    tamponstr.clear();
    tamponstr = phr;
}
void FicTexte::EcrireValeur()
{
    typerr = 1110;
    if(!tamponstr.empty())
    {
        write((char*)tamponstr.data(),tamponstr.size() );
        put(10);
        if( good() )
            typerr = 0;
    }
}
uint16_t FicTexte::EcrireValeur(  const std::string &phr  )
{
	StockerChaine( phr );
	EcrireValeur();
	return typerr;
}
void FicTexte::ReEcrireValeur(bool suppression)
{
    typerr = 1117;
    if(!tamponstr.empty())
    {
		std::string	nouvelleligne;
        typerr = 0;
		if(suppression)
		{
			nouvelleligne.clear(); 
			if(!is_open()) typerr = 1113;
		}
		else
		{
			nouvelleligne = tamponstr;
			if(is_open())
			{
				seekg(0);
				if(!good())
					typerr = 1118;
			}
			else
			{
				open( nomcomplet.data(), FlagOuvertureLecture());
				if(!is_open())
					typerr = 1115;
			}	
		}       
        
        if( typerr==0 )
        {
            long limite = lignepointee;
			FicTexte *fictmp = new FicTexte();
            fictmp->InitDescription( CheminFichier(), "fcopie01", "tmp");
            if( fictmp->CreerVide()==0 )
            {
				if( fictmp->OuvrirEnEcriture()==0 )
				{
					for(long i=1;i<limite;i++)
					{
						LireValeur();
						if(typerr!=0) break;
						if(fictmp->EcrireValeur(tamponstr)!=0) break;
					}
					if(typerr==0)
					{
						if(!suppression)
						{
							fictmp->EcrireValeur(nouvelleligne);
							LireValeur();
						}
						if(typerr==0)
						{
							while(!eof())
							{
								LireValeur();
								if(fictmp->EcrireValeur(tamponstr)!=0) break;
							}
							close();
							fictmp->close();
							EffacerFichier();
							if(typerr==0)
							{
								typerr = fictmp->RenommerFichier( nomcomplet );
							}
						}
					}
					else
						fictmp->close();
					delete fictmp;
				}
            }
        }
    }
}
uint16_t FicTexte::Inserer()
{
	typerr = 1114;
	if(is_open())
	{
		typerr = 1110;
		if(!tamponstr.empty())
		{
			if(lignepointee>0)
			{
				lignepointee--;
				seekg(0);
				if(lignepointee>0)
				{
					std::string	svdtamponstr( tamponstr );
					PointerLigne( lignepointee );
					svdtamponstr.swap(tamponstr);
				}
			}
			int32_t posenrg = tellg();
			if(posenrg!=-1)
			{
				NBOCTET = tamponstr.size()+1;
				typerr = FicBase::Inserer( posenrg );
			}
			else
				typerr = 1116;
		}
	}
	return typerr;
}

void FicTexte::LireValeur()
{
    typerr = 0;
	std::getline(*this,tamponstr,widen('\n'));
	if( tamponstr.empty() && eof() )
		typerr=1108;
}
std::string FicTexte::LireChaine()
{
    return std::string(tamponstr);
}
void FicTexte::IncrementLigne()
{
	lignepointee++;
}

uint16_t FicTexte::PointerLigne( uint32_t noligne )
{// noligne commence à 1
    long i = 0;
    lignepointee = 0;
    do{
        if(eof())
            return 1108;
        else
        {
            LireValeur();
            if(typerr > 0) return typerr;
            i++;
        }
    }while(i<noligne);
    lignepointee = i;
    return 0;
}
std::ios_base::openmode FicTexte::FlagOuvertureLecture()
{
    lignepointee = 0;
    return std::ios_base::in;
}
std::ios_base::openmode FicTexte::FlagOuvertureEcraser(){  return std::ios_base::out;}
std::ios_base::openmode FicTexte::FlagOuvertureAjouter(){  return std::ios_base::app;}
std::ios_base::openmode FicTexte::FlagOuvertureLectureEcriture(){ return ( std::ios_base::in  | std::ios_base::out );}
