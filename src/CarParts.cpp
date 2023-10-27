#include "../include/CarParts.h"

Engine::Engine(mINI::INIStructure& data) {
	throttle = 0;
	deltaEnergy = 0;
	if (data["engine"]["EngineLayout"] == "I")
		Layout = EngineLayout::I;
	else if (data["engine"]["EngineLayout"] == "V")
		Layout = EngineLayout::V;
	name = data["engine"]["Name"];
	quantityOfCylinders = stoi(data["engine"]["Cylinders"]);
	maxRPM = stoi(data["engine"]["MaxRPM"]);
	idleRPM = stoi(data["engine"]["IdleRPM"]);
	float displacement = stof(data["engine"]["Displacement"]);
	compressionRatio = stof(data["engine"]["CompressionRatio"]);

	float BDCvolume = displacement / quantityOfCylinders;
	float TDCvolume = BDCvolume / compressionRatio;

	crankAndFlyMass = stof(data["engine"]["CrankshaftMass"]) + stof(data["engine"]["FlywheelMass"]);
	currentRPM = idleRPM;

	Cylinder* c;
	for (int i = 0; i < quantityOfCylinders; i++) {
		c = new Cylinder(TDCvolume,BDCvolume,this);
		cylinders.push_back(std::move(*c)); //to chyba nie jest memory leak
	}

	std::string firingOrder = data["engine"]["FiringOrder"];

	for (int i = 0; i < quantityOfCylinders; i++) {
		cylinders[atoi(&firingOrder[i*2]) - 1].setAngle(360 - i*120);
	}
	
}

Gearbox::Gearbox(mINI::INIStructure& data) {
	int i = 1;
	for (;;){
		if (data["gearbox"].has("@" + std::to_string(i))) {
			gearRatios.push_back(stof(data["gearbox"]["@" + std::to_string(i)]));
			i++;
		}
		else
			break;
	}

	finalGearRatio = stof(data["gearbox"]["@Final"]);

	if (data["gearbox"]["Drivetrain"] == "FWD")
		driveType = Drivetrain::FWD;
	else if (data["gearbox"]["Drivetrain"] == "RWD")
		driveType = Drivetrain::RWD;
	else if (data["gearbox"]["Drivetrain"] == "AWD")
		driveType = Drivetrain::AWD;
	else if (data["gearbox"]["Drivetrain"] == "_4WD")
		driveType = Drivetrain::_4WD;
}

Car::Car(mINI::INIStructure& data) {
	name = data["general"]["Name"];
	dragCoeff = stof(data["general"]["DragCoefficient"]);
	headSurface = stof(data["general"]["HeadSurface"]);
	weight = stoi(data["general"]["Weight"]);


	Eng = new Engine(data);
	Gbox = new Gearbox(data);
}

void Cylinder::setAngle(short int a)
{	
	if (a == 720) {
		currentAngle = 0;
		return;
	}

	else if (a < 0) {
		setAngle(720 + a); //moge sobie pozwolic na taka rekurencje
		return;
	}

	else if (a > 720) { //tutaj bedziemy tez updatowaæ punkty termodynamiczne
		setAngle(a - 720);
		return;
	}

	currentAngle = a;
}

/*
void Cylinder::intake(float& throttle)
{
	//obliczyc liczbe moli zassana do cylindra
	double airmol = 22.4 * BDCvolume * throttle;
	//double airmass = airmol * 29; //gramy
	//double petrolmass = airmol * 29 / 14.9;
	double petrolmol = airmol * 29 / 14.9 / 114;
	mol = airmol + petrolmol;
	//obliczyc wykonana prace
	double work = 101300 * (BDCvolume - TDCvolume)*0.001;
	eng->modifyEnergy(work);
}

void Cylinder::compression()
{
	float P2 = (101300 * pow((BDCvolume * 0.001), 1.4f)) / (pow(TDCvolume, 1.4));
	double work = ((101300 * BDCvolume) - P2 * TDCvolume) / 0.4;
	p2 = P2;
	eng->modifyEnergy(work);
}
*/