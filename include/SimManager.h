#pragma once
#include "ResourceManager.h"
#include "CarParts.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class SimManager
{
public:
    SimManager(sf::RenderWindow& window);
    ~SimManager() { delete simulatedCar; }
    void runSimulation();

private:
    void updateWindow();
    void updateSim(const sf::Time& dTime);
    sf::Time calculateDeltaTime(){ return mainClock.restart() * timeFactor; }
    void handleMouse(sf::Vector2i mousepos);
    void handleKeyboard(sf::Keyboard::Key key);


    float timeFactor;
    sf::RenderWindow& window;
    ResourceManager RM;
    sf::Event event;
    sf::Clock mainClock;
    mINI::INIFile configFile;
    mINI::INIStructure config;
    Car* simulatedCar;

    const float density;

};