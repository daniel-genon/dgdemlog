#include "fichierlie.h"

FichierLie::FichierLie( ConfigurationObjet *ptrconf, ZoneGraphique *ptrscene )
{
	cfgobjet = ptrconf;
    pscene   = ptrscene;
	GenreElement( 9999 );
	NomElement("fic lie inconnu");
	nomicone = "/icone/quitter2.png";
}
bool FichierLie::InitNomFichier( const std::string &nom )
{
	nomfichier.clear();
	nomfichiercomplet = nom;
	std::size_t position = nomfichiercomplet.find_last_of("/\\");
	if( position==std::string::npos ) return false;
	nomfichier = nomfichiercomplet.substr(position+1);
	return true;
}
bool FichierLie::InitFichierLie( uint16_t genre, const DonneesContexte &valctx )
{
	bool okvalide=false;
	GenreElement( genre );
	switch(genre)
	{
		case 200 : 
			NomElement("fichier travail"); nomicone = "/icone/fictrv.png";
			GraphiqueSurface::CopierDepuisBloc( cfgobjet->PointerFicli(0)->Donnees().symbole );
			PositionDansScene( valctx.posXtrv, valctx.posYtrv );
			
			okvalide = InitNomFichier( std::string( (char *)&valctx.fictrv.v) );
			break;
		case 300 : 
			NomElement("fichier configuration"); nomicone = "/icone/ficcfg.png"; 
			GraphiqueSurface::CopierDepuisBloc( cfgobjet->PointerFicli(1)->Donnees().symbole );
			PositionDansScene( valctx.posXcfg, valctx.posYcfg );
			okvalide = InitNomFichier( std::string( (char *)&valctx.ficcfg.v) );
			break;
		default : NomElement("fic lie inconnu"); nomicone = "/icone/quitter2.png";
	}
	return okvalide;
}
void FichierLie::InitFichierLie( uint16_t genre, const std::string &nom, const std::string &icone )
{
	GenreElement( genre );
	NomElement(nom);
	nomicone = icone;
	GraphiqueSurface::CopierDepuisBloc( cfgobjet->PointerFicli(0)->Donnees().symbole );
	PositionDansScene( pscene->get_content_width()/3, pscene->get_content_height()/3 );
}
void FichierLie::CvtNomComplet( void *valret )
{
    memcpy( valret, nomfichiercomplet.data(), nomfichiercomplet.size());
}

std::string FichierLie::LibelleNom(){ return NomElement(); }
std::string FichierLie::LibelleTitre(){ return nomfichier; }
Glib::RefPtr<Gdk::Pixbuf> FichierLie::ChargerIcone()
{
	return Gdk::Pixbuf::create_from_resource( nomicone );
}
std::string FichierLie::NomCompletFichier() const { return nomfichiercomplet; }
//void FichierLie::CollationnerDescripteur( EnrgObjetCtx *retval )
//{
    //retval->Travail( NomFichier(false) , PositionXDansScene(), PositionYDansScene());
//}
