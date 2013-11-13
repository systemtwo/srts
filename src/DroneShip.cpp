#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"

#include "DroneShip.h"
#include "GeomUtil.h"
#include "ComponentNavigationNormal.h"
#include "ComponentWeaponLaser.h"

DroneShip::DroneShip(double x, double y, int team) 
	: Ship("Drone", team, new ComponentNavigationNormal(x, y, 100.0, PI), new ComponentTargetting(x, y, 100.0), 
	       new ComponentHealth(60), new ComponentWeaponLaser(x, y, 0, team), new ComponentCollision(10, x, y))
	{
	
	_health->setSize(sf::Vector2f(20, 5));
	if (team != 1 && team != 2) 
		std::cout << "Team problem: I'm on team: " << team << std::endl;
	
}

void DroneShip::update(double dt, World* world) {
}

void DroneShip::draw(sf::RenderWindow& window) {
	//Draw Ship
	sf::RectangleShape sprite(sf::Vector2f(8, 8));
	sf::CircleShape select(8);
	select.setFillColor(sf::Color::Transparent);
	switch (_team) {
		case 1:
			sprite.setTexture(TextureManager::getTexture("fighter1.png"));
			if (_selected) {
				select.setOutlineColor(sf::Color::Red);
				select.setOutlineThickness(1);
			}
			break;
		case 2:
			sprite.setTexture(TextureManager::getTexture("fighter2.png"));
			break;
		default:
			std::cout << "Panic! No team! (Actually, its: " << _team << ")" << std::endl;
			break;

	}
	//Sanity check
	if (_navigation->getPosition().x < 0 ||
	    _navigation->getPosition().y < 0 ||
	    _navigation->getPosition().x > 1600 ||
	    _navigation->getPosition().y > 1200) {
		std::cout << "Rect out of bounds: " << _navigation->getPosition().x << ", " << _navigation->getPosition().y << std::endl;
	}
	select.setPosition(_navigation->getPosition());
	select.setOrigin(sf::Vector2f(8, 8));

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

