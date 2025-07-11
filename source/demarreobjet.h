#ifndef DEMARREOBJET_H
#define DEMARREOBJET_H

//#include <QtGui>
//#include <QList>
#include "gerersession.h"
#include "logiciel.h"

class DemarreObjet
{
public:

    DemarreObjet();

    void InitSession( GererSession *valeur, ZoneGraphique *pvalscene );
    uint8_t DemarrerLaSession();
    void ArreterLesProcessus();
    bool DesProcessusSontDemarres();

private:

    ZoneGraphique	*pscene;
    GererSession    *psession;
    Logiciel        *plogi;
	GraphiqueSurface	*pgrasurftmp;
	
    uint8_t	regulateurdelai;

    DGChaineListe	lstprocessus;

    std::string nomdulogiciel;
    std::string phrasededemarreur;
    DGChaineListe nomfichiercfgobjet;
    DGChaineListe nomfichiertrvobjet;
    DGChaineListe phrasepouroptions;
//    DGChaineListe lstdependance;

    std::vector<GraphiqueSurface*> tabitem;

//    std::vector<Logiciel*> tabdemarrage;
   	std::pair< uint8_t,Logiciel*> valdemlogtmp;
    std::vector< std::pair< uint8_t,Logiciel*> > tabdemarrage;
    std::vector<std::pair< uint8_t,Logiciel*>>::iterator itabdem;


    bool AjouterATable();
    //void ClasserObjets();
    bool LancerProcessus();

    bool ReinitialiserLaScene();
    void PhraseFichierCFG();
    void PhraseFichierTRV();
    void PhraseFichier( const std::string &nmfic, const std::string &opfic, DGChaineListe &rtlstchaine );
    //QStringList PhraseFichier( const QString &nmfic, const QString &opfic );
    void IntegrerLesDependances();
    void IntegrerDansListeDesDemarres();

    bool ProcessusExistant();
    //void Attendre(int valeur);
};

#endif // DEMARREOBJET_H
