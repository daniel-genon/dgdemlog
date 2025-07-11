//#include "ancrage.h"
#include "logiciel.h"
//#include <QtGui>

Ancrage::Ancrage(){}
Ancrage::Ancrage( Element *vbateau, ConfigurationObjet *ptrcfg )
{
//    pconextmp = nullptr;
    bateau = vbateau;
    GenreElement(1000);
    NomElement("ancre");
    Valeur( ptrcfg->ptrAncrage()->Donnees());
    AnnulerCartouche();
    messagemsa = new MessageMSA;
    CopierDepuisBloc( donneesancre.symbole );
    PositionDansScene(  vbateau->PositionXDansScene(), vbateau->PositionYDansScene()-HauteurElement()/0.75  );
}

Ancrage::~Ancrage(){}

void Ancrage::Valeur( const DonneesAncre &valeur ){ donneesancre = valeur; }
GraphiqueSurface *Ancrage::ObjetConnecter(){ return (GraphiqueSurface *)bateau; }
//void Ancrage::Nettoyerconnexion()
//{
    ////if(pconextmp!=nullptr)
    ////{
        ////Logiciel* toto = (Logiciel *)bateau;
        ////toto->RetirerAncre();
        ////delete pconextmp;
        ////pconextmp=nullptr;
    ////}
//}

//QGraphicsItem *Ancrage::ValeurConnexion()
//{
//    if(pconextmp==NULL)
//        return NULL;
//    else
//        return (QGraphicsItem *) pconextmp;
//}

//bool Ancrage::AncreMaterialisee()
//{
    //return ((bateau!=NULL)&&(pconextmp!=NULL));
//}
//bool Ancrage::TransfererConnexion( Element *pelem )
//{
    //Logiciel *plogique = (Logiciel *)pelem;
////    Element *pconnecte = pconextmp->ValeurSource();
////    if(pconnecte->Famille()!=pelem->Famille())
////    {
        //plogique->TransfererUneConnexionAncre(pconextmp);
        //pconextmp->RemplacerContact(this,pelem);
        //pconextmp->Actualiser();
        //pconextmp = NULL;
        //bateau = NULL;
        //return true;
////    }
////    return false;
//}

/******************* Routines dessin ************************/
void Ancrage::Dessiner()
{
	Glib::RefPtr<Gdk::Pixbuf> imagetmp = Gdk::Pixbuf::create_from_resource( std::string((char *)donneesancre.imicone.v ) );
	int lgimg = LargeurElement();
	Glib::RefPtr<Gdk::Pixbuf> image = imagetmp->scale_simple( lgimg, lgimg, Gdk::InterpType::BILINEAR );
	Gdk::Cairo::set_source_pixbuf(tmpcr, image, xctr+LargeurElement()/2-lgimg*1.1, yctr-image->get_height()*0.5);
	tmpcr->paint();
}
