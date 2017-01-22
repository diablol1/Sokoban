#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>


class TextureCache
{
public:
	TextureCache() {
		loadTextures();
	}
	bool add(const std::string& name, const std::string& filename);

	sf::Texture& get(const std::string& name);

private:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> paths;

	void loadTextures();
};