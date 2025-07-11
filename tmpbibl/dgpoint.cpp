/*
 */

#include "dgpoint.h"
DGPoint::DGPoint(){ Raz(); }
DGPoint::DGPoint( const DGPoint &dgpnt )
{
	x = dgpnt.ValX();
	y = dgpnt.ValY();
}
DGPoint::DGPoint( DGPoint *dgpnt )
{
	x = dgpnt->ValX();
	y = dgpnt->ValY();
}
DGPoint::DGPoint( double vx, double vy ){	x=vx; y=vy;}
DGPoint::~DGPoint(){}

double DGPoint::ValX() const {	return x;}
double DGPoint::ValY() const {	return y;}
void DGPoint::ValX(const double &vx) { x=vx;}
void DGPoint::ValY(const double &vy) { y=vy;}
void DGPoint::Raz(){ x=0.0; y=0.0; }
void DGPoint::Set(const double &vx, const double &vy){ x=vx; y=vy; }
void DGPoint::Set( const DGPoint &dgpnt )
{
	x = dgpnt.ValX();
	y = dgpnt.ValY();
}
void DGPoint::Get(double &vx, double &vy){ vx=x; vy=y; }

