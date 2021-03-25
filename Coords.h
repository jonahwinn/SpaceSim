#pragma once
#include "stdincludes.h"

class Coordinates //Custom class to base coordinates system on. Starting 2D but can expand to 3D later. 
{
public:
	//Cartesian
	double x;
	double y;
	//Polar
	double mag;
	double theta;

	//Constructors
	Coordinates();
	Coordinates(double xpos, double ypos);

	//Operator overloads
	Coordinates operator + (const Coordinates&) const;
	Coordinates operator += (const Coordinates&);
	Coordinates operator - (const Coordinates&) const;
	Coordinates operator -= (const Coordinates&);
	Coordinates operator * (const Coordinates&) const;
	Coordinates operator * (const double)const;
	Coordinates operator / (const double)const;
	//Coordinates operator / (const Coordinates&) const;

	//function members
	void updatePolar();
	void updateCartesian();
};


