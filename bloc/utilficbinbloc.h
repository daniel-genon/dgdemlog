#ifndef UTILFICBINBLOC_H
#define UTILFICBINBLOC_H

#include <string>

bool EgalAvecTolerance( double v1, double v2, double tolerance=1 );
bool ValeurEntre( double vmin, double vmax, double vtest, double tolerance=1 );
void ConvStrVersBin( const std::string &phr , void *memdestinataire, std::size_t lgchaine=0 );

#endif // UTILFICBINBLOC_H
