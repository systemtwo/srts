#ifndef SHIP_BOMBER_H
#define SHIP_BOMBER_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentTargetting.h"
#include "ComponentCollision.h"
#include "World.h"

#include "ComponentNavigationNormal.h"
#include "ComponentWeaponBomb.h"

#include "TextureManager.h"

class ShipBomber : public Ship {
	public:
		ShipBomber(double x, double y, int team)
			: Ship("Bomber", team, new ComponentNavigationNormal(x, y, 25.0, PI), new ComponentTargetting(x, y, 200.0), 
			       new ComponentHealth(200), new ComponentWeaponBomb(x, y, 0, team), new ComponentCollision(10, x, y))
			{

	
			_health->setSize(sf::Vector2f(20, 5));
			if (team != 1 && team != 2) 
				std::cout << "Team problem: I'm on team: " << team << std::endl;
			
		}

		void update(double dt, World* world) {}
		void draw(sf::RenderWindow& window) {
			//Draw Ship
			sf::RectangleShape sprite(sf::Vector2f(12, 12));
			sf::CircleShape select(10);
			select.setFillColor(sf::Color::Transparent);
			switch (_team) {
				case 1:
					sprite.setTexture(TextureManager::getTexture("bomber1.png"));
					if (_selected) {
						select.setOutlineColor(sf::Color::Red);
						select.setOutlineThickness(1);
					}
					break;
				case 2:
					sprite.setTexture(TextureManager::getTexture("bomber2.png"));
					break;
				default:
					std::cout << "Panic! No team! (Actually, its: " << _team << ")" << std::endl;
					break;

			}
			select.setPosition(_navigation->getPosition());
			select.setOrigin(sf::Vector2f(11, 11));

			sprite.setPosition(_navigation->getPosition());
			//sprite.setSize(sf::Vector2f(10, 10));
			sprite.setOrigin(sf::Vector2f(5,5));
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
			_health->draw(window, _navigation->getPosition().x - 10, _navigation->getPosition().y - 15);
		}
		
	private:
		const double SPEED = 100.0;
		const double TURNING_SPEED = 3.14;

};

#endif //SHIP_BOMBER_H
