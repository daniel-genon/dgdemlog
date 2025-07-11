/*
 */
#ifndef DGPOINT_H
#define DGPOINT_H

class DGPoint
{
public:
	DGPoint();
	DGPoint( const DGPoint &dgpnt );
	DGPoint( DGPoint *dgpnt );
	DGPoint( double vx, double vy);
	
	~DGPoint();
	
	void Set( const double &vx, const double &vy);
	void Set( const DGPoint &dgpnt );
	void Get( double &vx, double &vy);
	void Raz();
	double ValX() const;
	double ValY() const;
	void ValX(const double &vx);
	void ValY(const double &vy);

private:
	double	x;
	double	y;
	
};

#endif /* DGPOINT_H */ 
