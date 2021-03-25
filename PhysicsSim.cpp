//Implementation of Physics Object class//
#include "PhysicsSim.h"

using namespace std;
using namespace physicsSim;

//Physics Object Class implementation
//Private functions
Coordinates PhysicsObject::calcG()
{
	Coordinates gforceVector;	//temporary vector for current G force calculation
	Coordinates netForce;		//Net force on the current body.
	for(PhysicsObject *orbitalBody : localBodies) 
	{
		gforceVector = position - orbitalBody->position;
		gforceVector.mag = GCONSTANT * ((mass * orbitalBody->mass) / pow(gforceVector.mag, 2));	//Newton's law of universal gravitation.
		gforceVector.updateCartesian(); //gets the force vector in cartesian coords based on the above magnitude and existing direction (towards the centre of the orbital body).
		netForce += gforceVector;
	}
	return netForce;
}
void PhysicsObject::updateNetForce() 
{
	netForce = calcG() + impulseForce;
	impulseForce = Coordinates(0, 0);
}
//Constructors
PhysicsObject::PhysicsObject() : mass(5.972e24), position(1.488e9,0), velocity(0,460), accelleration(0,0), netForce(0,0) {} // initialises physics object with default values, corresponding to the Earth's properties.
PhysicsObject::PhysicsObject(std::string n, double m, Coordinates p, Coordinates v)
{
	name = n;
	mass = m;
	position = p;
	velocity = v;
	accelleration = Coordinates(0,0);
	netForce = Coordinates(0,0);
}
//Public Functions
Coordinates PhysicsObject::calcNextPosition(double tDelta) 
{
	updateNetForce();
	accelleration = netForce / mass;
	velocity += accelleration * tDelta;
	position = position + velocity * tDelta;
	return position;
}
void PhysicsObject::applyImpulseForce(Coordinates f)
{
	impulseForce = f;
}

//Solar System implemenation
SolarSystem::SolarSystem():simulationSpeed(1), tDelta(1), worldBounds(6e9,6e9) {}
//Public Functions
void SolarSystem::nextTick() 
{ //Will need to change later on when doing calculations in multiple threads.
	for (PhysicsObject currObject : worldObjects) 
	{
		currObject.calcNextPosition(tDelta);
		//could switch this out to have a thread per object.
	}
	//Add in draw function here later to draw out a frame. 
}
void SolarSystem::addPhysObj(PhysicsObject spaceBody) 
{
	worldObjects.push_back(spaceBody);
}
void SolarSystem::addPhysObj(std::string name, double mass, Coordinates position, Coordinates velocity) 
{
	worldObjects.push_back(PhysicsObject(name, mass, position, velocity));
}
void SolarSystem::removeObject(PhysicsObject spaceBody)
{
	worldObjects.erase(remove_if(worldObjects.begin(), worldObjects.end(), [spaceBody](const PhysicsObject& obj) {return obj.name == spaceBody.name; }), worldObjects.end());
}
void SolarSystem::removeObject(std::string name) 
{
	worldObjects.erase(remove_if(worldObjects.begin(), worldObjects.end(), [&name](const PhysicsObject& obj) {return obj.name == name;}), worldObjects.end());
}
void SolarSystem::setSpeed(int simSpeed) 
{
	simulationSpeed = simSpeed;
}
