#include "../include/ResourceManager.h"

ResourceManager::ResourceManager() {

}

sf::Texture& ResourceManager::loadTexture(const std::string& filename) {

    // is loaded?
    auto it = m_textures.find(filename);
    if (it != m_textures.end())
        return it->second;

    // load and store
    sf::Texture texture;
    texture.setSmooth(true);
    if (texture.loadFromFile("resources/textures/" + filename + ".png")) {
        std::cout << "loaded texture: " << filename << std::endl;
        return m_textures.emplace(filename, std::move(texture)).first->second;
    }
        
    else
        throw std::runtime_error("Failed to load texture: " + filename);

}

sf::Font& ResourceManager::loadFont(const std::string& filename) {
    // is loaded?
    auto it = m_fonts.find(filename);
    if (it != m_fonts.end())
        return it->second;

    // load and store
    sf::Font font;
    if (font.loadFromFile("resources/fonts/" + filename + ".ttf")) {
        std::cout << "loaded font: " << filename << std::endl;
        return m_fonts.emplace(filename, std::move(font)).first->second;
    }
        
    else
        throw std::runtime_error("Failed to load font: " + filename);

}

sf::SoundBuffer& ResourceManager::loadSoundBuffer(const std::string& filename) {

    // is loaded?
    auto it = m_soundBuffers.find(filename);
    if (it != m_soundBuffers.end())
        return it->second;

    // load and store
    sf::SoundBuffer soundBuffer;
    if (soundBuffer.loadFromFile("resources/audio/" + filename + ".wav"))
        return m_soundBuffers.emplace(filename, std::move(soundBuffer)).first->second;
    else
        throw std::runtime_error("Failed to load sound buffer: " + filename);

}