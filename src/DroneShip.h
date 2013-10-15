#ifndef DRONE_SHIP_H
#define DRONE_SHIP_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"

class DroneShip : public Ship {
	public:
		DroneShip(double, double);

		void update(double dt);
		void draw(sf::RenderWindow& window);
		
		sf::Vector2f getPosition();
		std::string getName();

		void setSelected(bool selected);
		void setMoveLocation(double x, double y);

	private:
		double _x;
		double _y;
		double _targetX;
		double _targetY;
		bool _selected;

		const int SPEED = 10;
};

#endif //DRONE_SHIP_H
