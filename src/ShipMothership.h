#ifndef SHIP_MOTHERSHIP_H
#define SHIP_MOTHERSHIP_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentTargetting.h"
#include "ComponentCollision.h"
#include "World.h"

#include "ComponentNavigationNormal.h"
#include "ComponentWeaponNone.h"

#include "TextureManager.h"

class ShipMothership : public Ship {
	public:
		ShipMothership(double x, double y, int team)
			: Ship("Mothership", team, new ComponentNavigationNormal(x, y, 5.0, PI), new ComponentTargetting(x, y, 0.0), 
			       new ComponentHealth(400), new ComponentWeaponNone(x, y, 0, team), new ComponentCollision(16, x, y))
			{

	
			_health->setSize(sf::Vector2f(40, 5));
			if (team != 1 && team != 2) 
				std::cout << "Team problem: I'm on team: " << team << std::endl;
			
		}

		void update(double dt, World* world) {}
		void draw(sf::RenderWindow& window) {
			//Draw Ship
			sf::RectangleShape sprite(sf::Vector2f(32,32));
			sf::CircleShape select(20);
			select.setFillColor(sf::Color::Transparent);
			switch (_team) {
				case 1:
					sprite.setTexture(TextureManager::getTexture("mothership1.png"));
					if (_selected) {
						select.setOutlineColor(sf::Color::Red);
						select.setOutlineThickness(2);
					} else {
						//sprite.setFillColor(sf::Color::Yellow);
					}
					break;
				case 2:
					sprite.setTexture(TextureManager::getTexture("mothership2.png"));
					break;
				default:
					std::cout << "Panic! No team! (Actually, its: " << _team << ")" << std::endl;
					break;

			}

			select.setPosition(_navigation->getPosition());
			select.setOrigin(sf::Vector2f(20, 20));

			sprite.setPosition(_navigation->getPosition());
			sprite.setOrigin(sf::Vector2f(16, 16));
			sprite.setRotation(GeomUtil::radToDeg(_navigation->getAngle()) - 180);

			window.draw(sprite);
			window.draw(select);

			//Draw target location marker
			if (_selected) {
				sf::RectangleShape tmarker;
				tmarker.setFillColor(sf::Color::Cyan);
				tmarker.setPosition(_navigation->getTarget());
				tmarker.setSize(sf::Vector2f(2, 2));
				window.draw(tmarker);
			}

			//Draw Healthbar
			_health->draw(window, _navigation->getPosition().x - 20, _navigation->getPosition().y - 25);
		}
};

#endif //SHIP_MOTHERSHIP_H
