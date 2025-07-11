#include "connexion.h"
//Connexion::Connexion( Element *valeur , EnrgConnexion *ptr )
//{
    //pntsource.setX(0);
    //pntsource.setY(0);
    //if(ptr==NULL)
    //{
        //CouleurConnexion("#FF0000");
        //typedeligne = 1;
        //epaisseur   = 2;
    //}
    //else
    //{
        //CouleurConnexion(ptr->CCouleur());
        //typedeligne = ptr->CTypeLigne();
        //epaisseur   = ptr->CEpaisseur();
    //}

//}
Connexion::Connexion( ptrenrconnexion ptr,  GraphiqueSurface *valeur )
{
    pcible	= valeur;
    psource	= nullptr;
    pntcible.Set(1,1);
    GenreElement(5000);
    NomElement("connecteur");
    if(ptr==nullptr)
    {
		EnrgConnexion tmp;
		tmp.Standard();
		InitLigneDeBase(tmp.Donnees());
    }
    else
   		InitLigneDeBase(ptr->Donnees());
}
void Connexion::Actualiser()
{
   if((pcible!=nullptr)&&(psource!=nullptr))
   {
       BlocRectangle	dimcible, dimsource;
       DGPoint pntc;
       pcible->PositionDansScene(pntc);
       DGPoint pnts;
       psource->PositionDansScene(pnts);
       double xstmp, ystmp, xctmp, yctmp;
       pnts.Get(xstmp,ystmp);
       pntc.Get(xctmp,yctmp);
       dimcible		= pcible->Dimensions();
       dimsource	= psource->Dimensions();
           double dx,dy;
           uint8_t idxS = 100;
           uint8_t idxC = 100;
           uint8_t cas=0;
       if(EgalAvecTolerance( xstmp, xctmp,(dimcible.largeur/1.8+dimsource.largeur/1.8) )) cas=1;//aligne en X
       if(EgalAvecTolerance( ystmp, yctmp,(dimcible.hauteur/1.4+dimsource.hauteur/1.4) )) cas+=2;//aligne en Y
       if(xstmp>xctmp) cas+=4;//cible à gauche
       if(ystmp>yctmp) cas+=8;//cible haut
       dx=abs(xstmp-xctmp);
       dy=abs(ystmp-yctmp);
       switch(cas)
       {
        case  1:{//aligne X cible en bas
          idxS = 0;
          idxC = 2;
               }break;
       case  5:{//aligne X cible en bas
         idxS = 0;
         idxC = 2;
              }break;
       case  9:{//aligne X cible haut
          idxS = 2;
          idxC = 0;
               }break;
       case 13:{//aligne X cible haut
          idxS = 2;
          idxC = 0;
               }break;
       case  2:{//aligne en Y cible drt
         idxS = 1;
         idxC = 3;
              }break;
       case  10:{//aligne en Y cible drt
         idxS = 1;
         idxC = 3;
              }break;
       case  6:{//aligne Y cible à gah
          idxS = 3;
          idxC = 1;
               }break;
       case 14:{//aligne Y cible à gah
          idxS = 3;
          idxC = 1;
               }break;
       case   0:{//cible bas drt
           if(dx>dy)
            {idxS = 1;idxC = 3;}
           else
            {idxS = 0;idxC = 2;}
                }break;
       case   4:{//cible bas gauche
           if(dx>dy)
            {idxS = 3;idxC = 1;}
           else
            {idxS = 0;idxC = 2;}
                }break;
       case   8:{//cible haut drt
           if(dx>dy)
           {idxS = 1;idxC = 3;}
           else
           {idxS = 2;idxC = 0;}
                }break;
       case  12:{//cible haut gah
           if(dx>dy)
            {idxS = 3;idxC = 1;}
           else
            {idxS = 2;idxC = 0;}
                }break;
       default:{//aligne en XetY (superposé) 3 7 11 15
           idxS = 100;
           idxC = 100;
               }
       }
       pntsource = psource->PointDeContact(idxS);
       pntcible  = pcible->PointDeContact(idxC);
   }
}
bool Connexion::EntrerContacts ( GraphiqueSurface *ptrsource, GraphiqueSurface *ptrcible )
{
	if(psource!=nullptr) return false;
	if(pcible!=nullptr) return false;
	if(ptrsource==nullptr) return false;
	if(ptrcible==nullptr) return false;
	psource	= ptrsource;
	pcible	= ptrcible;
	Actualiser();
	return true;
}
void Connexion::EntrerSource ( GraphiqueSurface *valeur ){ psource	= valeur; }
void Connexion::EntrerCible ( GraphiqueSurface *valeur ){ pcible	= valeur; }
void Connexion::Deconnecter()
{
	if(pcible!=nullptr)
		pcible->RetirerLaConnexion( this );
	if(psource!=nullptr)
		psource->RetirerLaConnexion( this );
}
GraphiqueSurface *Connexion::ValeurCible() const {   return pcible; }
GraphiqueSurface *Connexion::ValeurSource() const {   return psource;}
// Element *Connexion::ValeurAutreConnecter( Element *pexistant ) const
// {
    // if(psource!=pexistant) return psource;
    // return pcible;
// }
// void Connexion::RemplacerContact( Element *pexistant, Element *pnouveau )
// {
    // if(psource==pexistant)
        // psource = pnouveau;
    // else
        // pcible = pnouveau;
// }
void Connexion::Dessiner()
{
	AppliquerValeurLigne();
	tmpcr->move_to( pntsource.ValX(),  pntsource.ValY() );
	tmpcr->line_to( pntcible.ValX(),  pntcible.ValY() );
	tmpcr->stroke();
}
