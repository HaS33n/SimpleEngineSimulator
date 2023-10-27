#include "../include/SimManager.h"
SimManager::SimManager(sf::RenderWindow& window) : window(window), density(1.2f), configFile("car.ini") {
	window.setVerticalSyncEnabled(true);
	timeFactor = 0.01f; //100x zwolnienie czasu

	configFile.read(config); //niezbyt wydajne, ale mam to w dupie B)
	simulatedCar = new Car(config);
}

void SimManager::runSimulation() {
	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					handleMouse(sf::Mouse::getPosition(window));
				break;
			case sf::Event::KeyPressed:
				handleKeyboard(event.key.code);
				break;
			default:
				break;
			}

		}
		//---------------------------------------------------------------------------------------------
		updateSim(calculateDeltaTime());
		


		updateWindow();
	}
}

void SimManager::handleMouse(sf::Vector2i mousepos) {
	std::cout << mousepos.x << " " << mousepos.y << std::endl;
		
}

void SimManager::handleKeyboard(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Escape) 
		window.close();
		
}

void SimManager::updateWindow() {
	window.clear(sf::Color::Black);
	window.display();
}

void SimManager::updateSim(const sf::Time& dTime)
{
			
}

