#include "TextureCache.h"

bool TextureCache::add(const std::string& _name, const std::string & _filename)
{
	sf::Texture tmpTexture;
	tmpTexture.loadFromFile(_filename);

	for (const auto& texture : textures)
	{
		if (texture.first == _name)
		{
			std::cerr << "Texture manager couldn't add texture with this same name: " +
				_name << std::endl;
			return  false;
		}
	}

	textures[_name] = tmpTexture;

	for (const auto& path : paths)
	{
		if (path == _filename)
		{
			std::cerr << "Texture manager couldn't add this same texture: " +
				_filename << std::endl;
			return false;
		}
	}
	paths.push_back(_filename);

	return true;
}

sf::Texture & TextureCache::get(const std::string & name)
{
	if (textures.find(name) == textures.end())
	{
		std::cerr << name << " texture doesn't exist!" << std::endl;
		return sf::Texture();
	}
	else
		return textures[name];
}

void TextureCache::loadTextures()
{
	add("player", "data/textures/player.png");
	add("wall", "data/textures/wall.png");
	add("box", "data/textures/box.png");
	add("finishPoint", "data/textures/finishPoint.png");
}
