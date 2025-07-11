#include "logiciel.h"

Logiciel::Logiciel(){}
Logiciel::Logiciel( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene, uint8_t noprio, uint16_t gelement )
{
    cfgobjet = ptrconf;
    pscene   = ptrscene;
    okvalide = false;
    indicepriorite = noprio;
	GenreElement( gelement );
    if(noprio==0)
    {
		switch( gelement )
		{
			case 110 :// construction graphique de fin d'application
				InitLogFinApplication();
				okvalide = true;
			break;
		}
	}
    else
    {
		donneelogiciel.Valeur( cfgobjet->PointeurLogstock() );
		okvalide = true;
	}
	if(okvalide)
	{
		libellepriorite = cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Nom();
		NomElement(donneelogiciel.NomClair());
		GraphiqueSurface::CopierDepuisBloc( cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Donnees().symbole );
		PositionDansScene( pscene->get_content_width()/2, pscene->get_content_height()/2 );
	}
}
Logiciel::Logiciel( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene, const DonneesContexte &valctx  )
{
    cfgobjet = ptrconf;
    pscene   = ptrscene;
    okvalide = true;
	if( memcmp( valctx.nomclair.v, libellefinappli.data() , libellefinappli.length() ) ==0 )   
	{
		GenreElement( 110 );
		InitLogFinApplication();
		NomElement(donneelogiciel.NomClair());
	}
	else
	{
		if(cfgobjet->PointerLogiciel(valctx.nomclair))
		{
			GenreElement( 100 );
			donneelogiciel.Valeur( cfgobjet->PointeurLogstock() );
		}
		else
		{
			GenreElement( 120 );
			okvalide = false;
		}
	}
	if(okvalide)
    {
		NomElement(donneelogiciel.NomClair());
		indicepriorite = valctx.idxpriorite;
		if( indicepriorite >= cfgobjet->ptrlstgrlogiciel()->TailleListe() )
			indicepriorite = cfgobjet->ptrlstgrlogiciel()->TailleListe()/2;
		libellepriorite = cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Nom();
		GraphiqueSurface::CopierDepuisBloc( cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Donnees().symbole );
		PositionDansScene( valctx.posX, valctx.posY );
    }
}
void Logiciel::InitLogFinApplication()
{
 	donneelogiciel.Valeur( "fermerauto",libellefinappli,"",
							"Fermer dgdemlog après le lancement du contexte","",
							"","",20,1,1,"","","","" );
}
void Logiciel::CollationnerDescripteur( EnrgObjetCtx *enrgtmp )
{
    DonneesContexte donneetmp;
    memset(&donneetmp, 0, sizeof (DonneesContexte ));
    enrgtmp->Raz();
    donneetmp.nomclair = donneelogiciel.BNomClair();
    donneetmp.posX = PositionXDansScene();
    donneetmp.posY = PositionYDansScene();
    donneetmp.idxpriorite = indicepriorite;
	Connexion *resuconex = TrouverConnexion(200);
	if(resuconex!=nullptr  )
	{
		FichierLie *tstfic = (FichierLie *)resuconex->ValeurCible();
		if( tstfic!=nullptr )
		{
			tstfic->CvtNomComplet( &donneetmp.fictrv );
			donneetmp.posXtrv = tstfic->PositionXDansScene();
			donneetmp.posYtrv = tstfic->PositionYDansScene();
		}
	}
	resuconex = TrouverConnexion(300);
	if(resuconex!=nullptr  )
	{
		FichierLie *tstfic = (FichierLie *)resuconex->ValeurCible();
		if( tstfic!=nullptr )
		{
			tstfic->CvtNomComplet( &donneetmp.ficcfg );
			donneetmp.posXcfg = resuconex->ValeurCible()->PositionXDansScene();
			donneetmp.posYcfg = resuconex->ValeurCible()->PositionYDansScene();
		}
	}
	enrgtmp->Valeur( donneetmp );
}
FichierLie *Logiciel::PtrFicLie( uint8_t cas )
{
	if( TrouverConnexion( cas*100 )!=nullptr )
	{
		return (FichierLie*)pelemresu;
	}
	return nullptr;
}
//FichierConfiguration *Logiciel::PtrFicCfg()
//{
    //if(TrouverConnexion(200))
        //return (FichierConfiguration *)pelemresu;
    //return NULL;
//}

std::string Logiciel::LibelleTitre(){ return donneelogiciel.NomProcessus(); }
std::string Logiciel::LibelleNom(){ return donneelogiciel.NomClair(); }
Glib::RefPtr<Gdk::Pixbuf> Logiciel::ChargerIcone()
{
	if(donneelogiciel.Icone().empty())
		return Gdk::Pixbuf::create_from_resource( "/icone/autoquitter.png" );
	else
		return Gdk::Pixbuf::create_from_file( donneelogiciel.Icone() );
}
/**
 * retour valeur
**/
std::string Logiciel::libelle() const {    return donneelogiciel.NomClair(); }
std::string Logiciel::Options( uint16_t genre ) const
{
	switch(genre)
	{
		case 1 : return donneelogiciel.Options();break;
		case 200 : return donneelogiciel.OptTRV();break;
		case 300 : return donneelogiciel.OptCFG();break;
	}
	return "";
}
std::string Logiciel::NomStdLie( uint16_t genre ) const
{
	switch(genre)
	{
		case 200 : return NomStdTRV();break;
		case 300 : return NomStdCFG();break;
	}
	return "";
}
std::string Logiciel::NomStdCFG() const {    return donneelogiciel.StdCFG(); }
std::string Logiciel::NomStdTRV() const {    return donneelogiciel.StdTRV(); }
std::string Logiciel::NomPriorite() const {    return libellepriorite;}
std::string Logiciel::NomDuProcessus() const { return donneelogiciel.NomProcessus(); }
std::string Logiciel::CheminProcess() const{    return donneelogiciel.Dossier();}
std::string Logiciel::Dependance() const{    return donneelogiciel.Dependance();}
uint8_t  Logiciel::IndicePriorite() const {    return indicepriorite; }
uint8_t Logiciel::ValeurPriorite() const { return cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->ValeurPriorite(); }
uint16_t Logiciel::DelaiApresDemarrage() const { return donneelogiciel.Delai(); }
bool Logiciel::UnSeulAutorise() { return donneelogiciel.UniqueB(); }
bool Logiciel::VerifierExistenceSurScene()
{
	bool trouver = false;
    if(donneelogiciel.UniqueB())
    {
		std::vector<GraphiqueSurface*> tmpidentite;
		if(pscene->CollecterGenreObjet( 100, tmpidentite ))
		{
			while (!tmpidentite.empty())
			{
				Logiciel *pobjettmp =  (Logiciel *) tmpidentite.back();
				if( pobjettmp->EstLeProcessus( donneelogiciel.NomProcessus()) )
					tmpidentite.clear();
				else
					tmpidentite.pop_back();
			}
		}
    }
    return trouver;
}
void Logiciel::ReconfigurerGraphique( uint8_t nindiceprio )
{
	indicepriorite = nindiceprio;
	libellepriorite = cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Nom();
	GraphiqueSurface::CopierDepuisBloc( cfgobjet->ptrlstgrlogiciel()->Position(indicepriorite)->Donnees().symbole );
	RecalculerPositionDansScene();
}
bool Logiciel::EstLeProcessus( const std::string &nomtest ){ return nomtest.compare( donneelogiciel.NomProcessus() ) == 0; }
bool Logiciel::ALeFichierLie( uint16_t genre )
{
	switch(genre)
	{
		case 200 : return !donneelogiciel.StdTRV().empty();break;
		case 300 : return !donneelogiciel.StdCFG().empty();break;
	}
	return false;
}
