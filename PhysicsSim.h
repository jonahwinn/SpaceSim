#pragma once
#include "stdincludes.h"
#include "Coords.h"

namespace physicsSim
{
	const double GCONSTANT = 6.67430e-11; 

	class PhysicsObject //Class to define a physical object within the simulation
	{
		double mass;			// in kg
		Coordinates position;		// in m
		Coordinates velocity;		// in m/s
		Coordinates accelleration;	// in m/s^2
		Coordinates netForce;		// in N
		Coordinates impulseForce;	// in N
		std::vector<PhysicsObject*> localBodies; //nearby objects to calculate g force with. 

		Coordinates calcG();
		void updateNetForce();

	public:
		std::string name;

		//Constructors
		PhysicsObject();
		PhysicsObject(std::string name, double m, Coordinates p, Coordinates v); //Initialise physics object with mass m, position p and velocity v.
		//PhysicsObject(std::string preset); //Allows the user to add a real life planet via name, i.e. PhysicsObject(Earth). #May want to implement this in child classes later. 

		//Setters & Getters
		double getMass();
		Coordinates getVelocity();
		Coordinates getAcceleration();
		std::string getDescription();

		//Utility Functions
		Coordinates calcNextPosition(double tDelta);
		void applyImpulseForce(Coordinates f);
	};

	class SolarSystem		//Main engine and object factory class
	{
		int simulationSpeed;	//speed of the simulation in ticks per second.
		double tDelta;				//scaler for time between simulation frames.
		std::vector<PhysicsObject> worldObjects; //array that contains all objects to simulate- could convert to vector later. 
		Coordinates worldBounds; //bounds of the simulation.

		void calcTimeDelta();

	public:
		//Constructors
		SolarSystem();
		//SolarSystem(std::string preset);	//Could potentially use to initialise world with a real solar system config.

		//Class functions
		void nextTick();
		void addPhysObj(PhysicsObject spaceBody);
		void addPhysObj(std::string name, double mass, Coordinates position, Coordinates velocity); //add object using parameters
		void removeObject(PhysicsObject obj);	//remove using object reference
		void removeObject(std::string name);	//remove using name of object
		void setSpeed(int simSpeed);
	};
}