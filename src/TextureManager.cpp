#include "TextureManager.h"

std::map<std::string, sf::Texture* >TextureManager::_textures;

sf::Texture* TextureManager::getTexture(std::string filename, sf::IntRect rect) {
	auto iter = _textures.find(filename);
	if (iter == _textures.end()) {
		sf::Texture* tex(new sf::Texture());
		if (tex->loadFromFile("res/" + filename, rect)) {
			_textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
			return tex;
		}
	} else {
		return iter->second;
	}
}
