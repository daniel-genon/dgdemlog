#include "utilficbinbloc.h"
#include <stdio.h>
#include <string.h>

bool EgalAvecTolerance( double v1, double v2, double tolerance )
{
    if(v1>(v2+tolerance)) return false;
    if(v1<(v2-tolerance)) return false;
    return true;
}

bool ValeurEntre( double vmin, double vmax, double vtest, double tolerance )
{
    if(vtest<(vmin-tolerance)) return false;
    if(vtest>(vmax+tolerance)) return false;
    return true;
}

void ConvStrVersBin( const std::string &phr , void *memdestinataire, std::size_t lgchaine )
{
    std::size_t taille = phr.size();
    if(lgchaine!=0)
    {
        if(taille>lgchaine)
            taille=lgchaine;
    }
	memcpy( memdestinataire, phr.data(), taille);
}
