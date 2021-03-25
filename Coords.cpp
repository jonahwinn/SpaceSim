#include "Coords.h"

//Coordinates class implementation

Coordinates::Coordinates() : x(0), y(0), mag(0), theta(0) {}
Coordinates::Coordinates(double xpos, double ypos)
{
	x = xpos;
	y = ypos;
	updatePolar(); //sets polar coords based on x and y;
}
Coordinates Coordinates::operator+(const Coordinates& rhs)const
{
	Coordinates result((x + rhs.x), (y + rhs.y));
	result.updatePolar();
	return result;
}
Coordinates Coordinates::operator += (const Coordinates& rhs)
{
	this->x = (this->x + rhs.x);
	this->y = (this->y + rhs.y);
	this->updatePolar();
	return *this;
}
Coordinates Coordinates::operator-(const Coordinates& rhs)const
{
	Coordinates result((x - rhs.x), (y - rhs.y));
	result.updatePolar();
	return result;
}
Coordinates Coordinates::operator -= (const Coordinates& rhs)
{
	this->x = (this->x - rhs.x);
	this->y = (this->y - rhs.y);
	this->updatePolar();
	return *this;
}
//Multiplying two coordinates together
Coordinates Coordinates::operator * (const Coordinates& rhs) const
{
	Coordinates result((x * rhs.x), (y * rhs.y));
	result.updatePolar();
	return result;
}
//Multiplying a coordinate by a scalar
Coordinates Coordinates::operator * (const double rhs)const
{
	Coordinates result(x * rhs, y * rhs);
	result.updatePolar();
	return result;
}
Coordinates Coordinates::operator / (const double rhs)const
{
	Coordinates result(x / rhs, y / rhs);
	result.updatePolar();
	return result;
}
void Coordinates::updatePolar()
{
	mag = sqrt(pow(x, 2) + pow(y, 2));
	theta = atan(y / x);
}
void Coordinates::updateCartesian()
{
	x = mag * cos(theta);
	y = mag * sin(theta);
}