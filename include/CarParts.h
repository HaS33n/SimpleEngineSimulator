#pragma once
#include <iostream>

#include <vector>
#include "ini.h" //nie dodane do projektu

enum class EngineLayout {I,V};
enum class Drivetrain { FWD, RWD, AWD, _4WD };
class Engine;

class CarPart 
{
public:

private:

};

class Cylinder
{
public:
	Cylinder(float TDC, float BDC, Engine* ptr) { currentAngle = 0; mol = 0; TDCvolume = TDC; BDCvolume = BDC; eng = ptr; }
	void setAngle(short int a);
	void addAngle(unsigned short int a) { setAngle(currentAngle + a); }

private:
	//wewnetrzne metody do obliczen termodynamicznych
	void intake(float& throttle);
	void compression();
	void powerStroke();
	void exhaust();

	unsigned short int currentAngle; //0-720
	float mol, TDCvolume, BDCvolume; //nie wiem jak nazwaæ mole po angielsku XD
	
	Engine* eng;
};

class Engine : public CarPart 
{
public:
	Engine(mINI::INIStructure& data);
	void setThrottle(float& value) { if (value >= 0 && value <= 1) { throttle = value; } }
	const float getThrottle() { return throttle; }
	

private:
	std::string name;
	EngineLayout Layout;
	unsigned short int quantityOfCylinders, maxRPM, idleRPM, currentRPM;
	float compressionRatio, crankAndFlyMass; //lol
	long double deltaEnergy;
	float throttle; //0(zamkniete) - 1(full otwarta)

	std::vector<Cylinder> cylinders;
};

class Gearbox : public CarPart 
{
public:
	Gearbox(mINI::INIStructure& data);

private:
	Drivetrain driveType;
	std::vector<float> gearRatios;
	float finalGearRatio;
};

class Car
{
public:
	Car(mINI::INIStructure& data);
	~Car() { delete Eng; delete Gbox; }
	
	//gets
	const Engine* getEngine() { return Eng; }
	const Gearbox* getGearbox() { return Gbox; }
	

	//sets
	

private:
	std::string name;


	Engine* Eng;
	Gearbox* Gbox;
	float dragCoeff, headSurface;
	unsigned short int weight;
};
