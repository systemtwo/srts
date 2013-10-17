#ifndef DRONE_SHIP_H
#define DRONE_SHIP_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentNavigation.h"

class DroneShip : public Ship {
	public:
		DroneShip(double x, double y, int team);

		void update(double dt);
		void draw(sf::RenderWindow& window);
		
		sf::Vector2f getPosition();
		std::string getName();
		int getTeam();

		void setSelected(bool selected);
		void setMoveLocation(double x, double y);

	private:
		ComponentNavigation _navigation;
		ComponentHealth _health;

		bool _selected;
		int _team;

		const double SPEED = 100.0;
		const double TURNING_SPEED = 3.14;
};

#endif //DRONE_SHIP_H
