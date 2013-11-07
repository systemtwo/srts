#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager {
	public:
		TextureManager();

		static sf::Texture* getTexture(std::string filename, sf::IntRect = sf::IntRect());

	private:
		static std::map<std::string, sf::Texture*> _textures;
};

#endif //TEXTURE_MANAGER_H
