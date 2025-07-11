#include "graphobjetactif.h"

GraphObjetActif::GraphObjetActif()
{
    pancretmp = nullptr;
    pelemresu = nullptr;
}
GraphObjetActif::~GraphObjetActif()
{
	SupprimerLesConnexions();
}

void GraphObjetActif::EntrerUneConnexion( Connexion *valeur )
{
//   pconexencours = valeur;
    lstconex.push_back(valeur);
}

//bool GraphObjetActif::CreerConnexion( GraphObjetActif *ptrcible )
//{
   //if( ptrcible!=NULL )
   //{
      //pconexencours =  new Connexion( ptrcible, cfgobjet->PointeurCo(0) );
      //if(pconexencours!=NULL)
      //{
          //lstconex.push_back(pconexencours);
          //return true;
      //}
   //}
   //return false;
//}

Connexion *GraphObjetActif::TrouverConnexion( uint16_t valgenre )
{
	if(lstconex.size()!=0)
	{
		for(int i=0;i<lstconex.size();i++)
		{
			Connexion *conex = lstconex.at(i);
			pelemresu = conex->ValeurCible();
			if(pelemresu!=nullptr)
				if(pelemresu->GenreElement()==valgenre)
					return conex;
		}
	}
	return nullptr;
}
//Connexion *GraphObjetActif::DerniereConnexionDeLaListe() const
//{
    //if(lstconex.size()!=0)
    //{
        //return lstconex.back();
    //}
    //return NULL;
//}

void GraphObjetActif::ActualiserConnexion()
{
    if(lstconex.size()!=0)
    {
        for(int i=0;i<lstconex.size();i++)
        {
            lstconex.at(i)->Actualiser();
		}
    }
}
void GraphObjetActif::EntrerSourceConnexion( GraphiqueSurface *valeur )
{
    pconexencours->EntrerSource( valeur );
    ActualiserConnexion();
}
//bool GraphObjetActif::AncreNonLarguee()
//{
    //if(pancretmp==NULL) return false;
    //return pancretmp->AncreMaterialisee();
//}
void GraphObjetActif::RetirerAncre(){ pancretmp = nullptr; }
void GraphObjetActif::EntrerUneAncre( Ancrage *pvaleur, GraphiqueSurface *vbateau, EnrgConnexion *pvalconex )
{
    pancretmp = pvaleur;
    pconexencours =  new Connexion( pvalconex, pancretmp);
    EntrerSourceConnexion( vbateau );
    lstconex.push_back( pconexencours );
}
void GraphObjetActif::TransfererUneConnexionAncre( GraphiqueSurface *ptrcible )
{
	pconexencours->EntrerCible(ptrcible);
    ActualiserConnexion();
}
//bool GraphObjetActif::CreerUneConnexionNouvelle(Element *psource, Element *pcible )
//{
    //if(!CreerConnexion(pcible)) return false;
    //return EntrerSourceConnexion(psource);
//}
//void GraphObjetActif::SupprimerLesItemsAncre()
//{
    ////QGraphicsItem *pobjet;
    ////QList<QGraphicsItem *> tabitem = pscene->items();
    ////for(int i=0;i<tabitem.length();i++)
    ////{
        ////pobjet = tabitem.at(i);
        ////Element *pelem = (Element *)pobjet;
        ////if((pelem->GenreElement()==1000))
            ////pscene->removeItem( pobjet );
    ////}
//}
GraphiqueSurface *GraphObjetActif::ValeurConnexion()
{
    //if(pconexencours==nullptr)
        //return nullptr;
    //else
        return (GraphiqueSurface *) pconexencours;
}

bool GraphObjetActif::ConnecterElement(  GraphObjetActif *valeur )
{
	if( valeur == nullptr ) return false;
	ptrenrconnexion valigne = cfgobjet->PointeurCo( 0 );
	switch(valeur->GenreElement())
	{
		case 200 : valigne = cfgobjet->PointeurCo( 1 );	break;
		case 300 : valigne = cfgobjet->PointeurCo( 2 );	break; 
	}
	pconexencours =  new Connexion( valigne );
	lstconex.push_back( pconexencours );
	valeur->EntrerUneConnexion( pconexencours );
    if( !pconexencours->EntrerContacts ( this, valeur )) return false;
	pscene->AjouterElement ( pconexencours );
    return true;
}
void GraphObjetActif::RetirerLaConnexion( GraphiqueSurface *ptrconex )
{
	std::vector<Connexion*>::iterator ctmp;
	ctmp = std::find( lstconex.begin(), lstconex.end(), (Connexion*)ptrconex );
	if (ctmp != lstconex.end())
		lstconex.erase( ctmp );
}

//void GraphObjetActif::Deconnecter( Connexion *pconex, bool detruireconex )
//{
	//for(size_t i=0;i<lstconex.size();i++)
	//{
		//if(lstconex.at(i)==pconex)
		//{
			//lstconex.erase(lstconex.begin()+i);
			//break;
		//}
	//}
    //if(detruireconex)
    //{
        //delete pconex;
    //}
    //pconexencours=NULL;
//}
void GraphObjetActif::SupprimerLesConnexions()
{
	if(lstconex.size()!=0)
	{
		for(int i=0; i<lstconex.size(); i++)
		{
			pconexencours = lstconex.at(i);
			pconexencours->Deconnecter();
			pscene->Supprimer( pconexencours ) ;
		}
		lstconex.clear();
		pconexencours = nullptr;
	}
}
ConfigurationObjet *GraphObjetActif::PtrConfObjet() const
{
	return cfgobjet;
}


////************************************************************
////     Gestion des événements
////************************************************************


//void GraphObjetActif::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
    //bool okup=false;
    //QGraphicsItem::mouseMoveEvent(event);
    //if(AncreNonLarguee())
    //{
        //pancretmp->RemonterLAncre();
        //okup=true;
    //}
    //if(!lstconex.isEmpty())
    //{
        //for(int i=0;i<lstconex.size();i++)
            //lstconex.at(i)->Actualiser();
        //okup=true;
    //}
    //if(okup) update();
//}
