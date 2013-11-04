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
#include "ComponentWeaponBomb.h"

class ShipMothership : public Ship {
	public:
		ShipMothership(double x, double y, int team)
			: Ship("Mothership", team, new ComponentNavigationNormal(x, y, 5.0, PI), new ComponentTargetting(x, y, 0.0), 
			       new ComponentHealth(400), new ComponentWeaponBomb(x, y, 0, team), new ComponentCollision(16, x, y))
			{

	
			_health->setSize(sf::Vector2f(40, 5));
			if (team != 1 && team != 2) 
				std::cout << "Team problem: I'm on team: " << team << std::endl;
			
		}

		void update(double dt, World* world) {}
		void draw(sf::RenderWindow& window) {
			//Draw Ship
			sf::CircleShape sprite(16);
			switch (_team) {
				case 1:
					if (!_selected)
						sprite.setFillColor(sf::Color::Red);
					else 
						sprite.setFillColor(sf::Color::Yellow);
					break;
				case 2:
					sprite.setFillColor(sf::Color::Magenta);
					break;
				default:
					std::cout << "Panic! No team! (Actually, its: " << _team << ")" << std::endl;
					break;

			}

			sprite.setPosition(_navigation->getPosition());
			sprite.setOrigin(sf::Vector2f(16, 16));
			sprite.setRotation(GeomUtil::radToDeg(_navigation->getAngle()));
			window.draw(sprite);

			//Draw target location marker
			if (_selected) {
				sf::RectangleShape tmarker;
				tmarker.setFillColor(sf::Color::Cyan);
				tmarker.setPosition(_navigation->getTarget());
				tmarker.setSize(sf::Vector2f(2, 2));
				window.draw(tmarker);
			}

			//Draw Healthbar
			_health->draw(window, _navigation->getPosition().x - 10, _navigation->getPosition().y - 15);
		}
};

#endif //SHIP_MOTHERSHIP_H
