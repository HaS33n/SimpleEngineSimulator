#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class ResourceManager
{
public:
	
	ResourceManager();
	sf::Texture& loadTexture(const std::string& filename);
	sf::Font& loadFont(const std::string& filename);
	sf::SoundBuffer& loadSoundBuffer(const std::string& filename);

private:
	
	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, sf::Font> m_fonts;
	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers; 
};

