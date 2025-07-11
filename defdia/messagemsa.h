#ifndef MESSAGEMSA_H
#define MESSAGEMSA_H

#include "../../bibliodg/entete/dgbdial.h"

class MessageMSA : public BoiteDialogue
{
public:
    MessageMSA();
//    MessageMSA( Gtk::Window *parent );
//    MessageMSA( Gtk::Window *parent , const std::string &phrtmp);
//    MessageMSA( Gtk::Window *parent , const std::string &phr1, const std::string &phr2);
//	MessageMSA( Gtk::Window *fenappel, const Glib::ustring &libellezone, const uint8_t &typezone );

    //void FichierInexistant();
    //void FichierNestPasCreer();
    //void SauvegardeDonnees();
    //bool QuitterLogiciel();
    //void ObjetInconnu();
    //void PasDeLogicielsDemarres();
    //bool ArretDesLogiciels();

    //int QuestionGestionFichier(const std::string &phrtmp);
    //int QuestionTroisReponse(const std::string &phrtitre, const std::string &phrtexte,
                             //const std::string &libbtn1,const std::string &libbtn2,const std::string &libbtn3);
    //bool QuestionSuppression(const std::string &phrtmp);
    //bool QuestionMSA(const std::string &phrtitre, const std::string &phrtmp);

    //static void AlerteMessage(const std::string &phrttmp);
    void AlerteMessage(const std::string &phrtitre, const std::string &phrttmp);
    //void AlerteErreur(const std::string &phrtmp);
private:
    Gtk::Window *fenetreparent;
};

#endif // MESSAGEMSA_H
