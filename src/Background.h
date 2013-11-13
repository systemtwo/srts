#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "TextureManager.h"

class Background {
	public:
		Background(double width, double height) {
			for (int i = 0; i < 100; i++) {
				sf::Sprite s;
				s.setTexture(*TextureManager::getTexture("star1.png"));
				s.setPosition(rand() % (int)width, rand() % (int)height);
				_stars.push_back(s);
			}
		}

		void draw(sf::RenderWindow& window) {
			for (auto star : _stars) {
				window.draw(star);
			}
		}

		void processMovement(double x, double y) {
			//Make sure we get reference so we can modify the sprite
			for (sf::Sprite& star : _stars) {
				sf::Vector2f pos = star.getPosition();
				pos.x += x/2.0;
				pos.y += y/2.0;
				star.setPosition(pos);
			}
		}

	private:
		std::vector<sf::Sprite> _stars;
};

#endif
