#include "messagemsa.h"

MessageMSA::MessageMSA(){ fenetreparent = nullptr; }
//int MessageMSA::QuestionGestionFichier( const std::string &phrtmp )
//{
////    QMessageBox *msg = new QMessageBox;
////        msg->setWindowTitle("Gestion de fichiers");
////        msg->setText("Le fichier existe, souhaitez-vous :");
////        msg->setIcon(QMessageBox::Question);
////    msg->addButton( phrtmp, ActionRole );
////    msg->addButton( std::string("Utiliser l'existant"), ActionRole );
////    QPushButton *defbouton = msg->addButton( std::string("Ne rien faire"), ActionRole );
////    msg->setDefaultButton(defbouton);
////        return msg->exec();

    ///* 0:phrtmp, 1:utilisr existan, 2: ne rien faire */
    //return QuestionTroisReponse(std::string("Gestion de fichiers"),
                         //std::string ("Le fichier existe, souhaitez-vous :"),
                         //phrtmp,
                         //std::string ("Utiliser l'existant"),
                         //std::string("Ne rien faire"));

//}
//int MessageMSA::QuestionTroisReponse(const std::string &phrtitre,
                                     //const std::string &phrtexte,
                                     //const std::string &libbtn1,
                                     //const std::string &libbtn2,
                                     //const std::string &libbtn3)
//{
    //QMessageBox *msg = new QMessageBox();
        //msg->setWindowTitle(phrtitre);
        //msg->setText(phrtexte);
        //msg->setIcon(QMessageBox::Question);
        //QPushButton *defbouton = msg->addButton( libbtn1, ActionRole );
        //msg->addButton( libbtn2, ActionRole );
        //msg->addButton( libbtn3, ActionRole );
        //msg->setDefaultButton(defbouton);
///* 0:libbtn1, 1:libbtn2, 2:libbtn3 */
    //return msg->exec();
//}
//bool MessageMSA::QuestionSuppression(const std::string &phrtmp)
//{
    //return question(fenetreparent,"Suppression d'élèment(s)",phrtmp)==Yes;
//}
//bool MessageMSA::QuestionMSA(const std::string &phrtitre, const std::string &phrtmp)
//{
    //return question( fenetreparent, phrtitre, phrtmp )==Yes;
//}
//void MessageMSA::FichierInexistant()
//{
    //warning(fenetreparent,"ALERTE","Le fichier n'existe pas");
//}
//void MessageMSA::SauvegardeDonnees()
//{
    //information(fenetreparent,"Sauvegarde","Les données sont sauvegardées");
//}
//void MessageMSA::ObjetInconnu()
//{
    //information(fenetreparent,"suppression d'un élèment","Objet inconnu...");
//}
//void MessageMSA::PasDeLogicielsDemarres()
//{
    //information( fenetreparent,"Arrêt des logiciels","Il n'y a pas de logiciels démarrés par MultiStartApp");
//}
//bool MessageMSA::QuitterLogiciel()
//{
    //return question( fenetreparent,"Arrêt du logiciel","Souhaitez-vous fermer l'application ?")==Yes;
//}
//bool MessageMSA::ArretDesLogiciels()
//{
    //return question( fenetreparent,"Arrêt des logiciels",
             //"Si des fichiers ont été modifié et n'ont pas été sauvegardé<br/>"
             //"les modifications <strong>seront perdues</strong> !!<br/>"
             //"Continuer l'arrêt des logiciels ?")==Yes;
//}

//void MessageMSA::FichierNestPasCreer()
//{
    //warning(fenetreparent,"ALERTE","Le fichier n'est pas créer");
//}

//void MessageMSA::AlerteMessage(const std::string &phrttmp)
//{
    //warning(nullptr,"ALERTE",phrttmp);
//}
void MessageMSA::AlerteMessage(const std::string &phrtitre, const std::string &phrttmp)
{
//	warning(fenetreparent, phrtitre, phrttmp);
}
//void MessageMSA::AlerteErreur(const std::string &phrtmp)
//{
    //warning(fenetreparent, "Sortie du logiciel", phrtmp );
//}


