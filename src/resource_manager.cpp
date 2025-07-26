#include "resource_manager.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

std::map<std::string, std::unique_ptr<sf::Texture>> TextureManager::textures;

void TextureManager::loadTexture(const std::string &name, const std::string &filePath){
    auto texture = std::make_unique<sf::Texture>();
    if(!texture->loadFromFile(filePath)){
        throw std::runtime_error("Failed to load Texture " + filePath);
    }
    textures[name] = std::move(texture);
}

sf::Texture &TextureManager::getTexture(const std::string &name){
    auto it = textures.find(name);
    if(it == textures.end()){
        throw std::runtime_error("Texture not found : " + name);
    }
    return *(it->second);
}