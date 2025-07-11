#ifndef INFOVARIABLEMSA_H
#define INFOVARIABLEMSA_H

#include <gtkmm.h>
#include "../enrg/enrgvariablemsa.h"

class InfoVariableMSA : public Gtk::Window
{

public:
    InfoVariableMSA( ptrenrgvariableMSA pvaleur );
    ~InfoVariableMSA();
	void connexionInfo( const sigc::slot<void(uint8_t)> &slot );
};

#endif // INFOVARIABLEMSA_H
