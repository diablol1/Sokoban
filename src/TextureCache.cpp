#include "TextureCache.h"

bool TextureCache::add(const std::string& _name, const std::string & _filename)
{
	sf::Texture tmpTexture;
	tmpTexture.loadFromFile(_filename);

	for (const auto& texture : textures)
	{
		if (texture.first == _name)
		{
			std::cerr << "Texture manager couldn't add texture with this same name: " <<
				_name << std::endl;
			return  false;
		}
	}

	textures[_name] = tmpTexture;

	for (const auto& path : paths)
	{
		if (path == _filename)
		{
			std::cerr << "Texture manager couldn't add this same texture: " <<
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
	add("wall", "data/textures/wall.png");
	add("box", "data/textures/box.png");
	add("redBox", "data/textures/redBox.png");
	add("finishPoint", "data/textures/finishPoint.png");
	add("none", "data/textures/none.png");

	add("playerLeft", "data/textures/player/playerLeft.png");
	add("playerRight", "data/textures/player/playerRight.png");
	add("playerUp", "data/textures/player/playerUp.png");
	add("playerDown", "data/textures/player/playerDown.png");
}
