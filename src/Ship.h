#ifndef SHIP_H
#define SHIP_H

#include <string>

#include <SFML/System.hpp>

class Ship {
	public:
		virtual void update (double dt) {}
		virtual void draw(sf::RenderWindow& window) {}
		virtual sf::Vector2f getPosition() { return sf::Vector2f(0,0); };
		virtual std::string getName() { return ""; };

		virtual void setSelected(bool selected) { };
		virtual void setMoveLocation(double x, double y) {};
};

#endif //SHIP_H
